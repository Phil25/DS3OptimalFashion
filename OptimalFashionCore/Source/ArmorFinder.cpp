#include "ArmorFinder.hpp"
#include "Parser.hpp"
#include <cassert>

constexpr char cr = '\n';

namespace
{

#pragma warning(push)
#pragma warning(disable: 4102)  // disable unreferenced label warning in IterateSets<false, false>
	template <bool HasAdditiveParamLimits, bool HasDiminishingParamLimits>
	auto IterateSets(
		optifa::ArmorGroups& armor, const float availableLoad, const optifa::ArmorPiece::Param toMaximize, float minDifference,
		const optifa::ArmorPiece::MinParams& minValuesAdditive, const optifa::ArmorPiece::MinParams& minValuesDiminishing)
	{
		assert(minDifference >= 0.F);
		assert(!armor.head.empty() && !armor.chest.empty() && !armor.hands.empty() && !armor.legs.empty());

		const auto calcParam = SuffersFromDiminishingReturns(toMaximize) ? optifa::CalculateDiminishing<false> : optifa::CalculateAdditive;
		auto bestParam = calcParam(*(armor.head[0]), *(armor.chest[0]), *(armor.hands[0]), *(armor.legs[0]), toMaximize);

		// in case of params with diminishing returns, include the value modifiers stripped from CalculateDiminishing<false>
		minDifference = SuffersFromDiminishingReturns(toMaximize) ? minDifference * 1'000'000 : minDifference;

		std::vector<optifa::ArmorSet> sets;

		for (const auto& he : armor.head)
		for (const auto& ch : armor.chest)
		for (const auto& ha : armor.hands)
		for (const auto& le : armor.legs)
		{
			auto param = calcParam(*he, *ch, *ha, *le, toMaximize);

			if constexpr (HasAdditiveParamLimits)
			{
				for (const auto& [param, minValue] : minValuesAdditive)
					if (optifa::CalculateAdditive(*he, *ch, *ha, *le, param) < minValue)
						goto next_set;
			}

			if constexpr (HasDiminishingParamLimits)
			{
				for (const auto& [param, minValue] : minValuesDiminishing)
					if (optifa::CalculateDiminishing<false>(*he, *ch, *ha, *le, param) < minValue)
						goto next_set;
			}

			if (param >= bestParam - minDifference && CalculateAdditive(*he, *ch, *ha, *le, optifa::ArmorPiece::Param::Weight) <= availableLoad)
			{
				if (param > bestParam) bestParam = param;
				sets.emplace_back(*he, *ch, *ha, *le);
			}

			next_set:;
		}

		std::vector<optifa::ArmorSet> topSets;

		for (const auto& set : sets)
		{
			if (calcParam(set.head, set.chest, set.hands, set.legs, toMaximize) >= bestParam - minDifference)
				topSets.emplace_back(set);
		}

		return topSets;
	}
#pragma warning(pop)
}

namespace optifa
{
	auto FindOptimal(const float availableLoad, const ArmorPiece::Param toMaximize, float minDifference,
		const ArmorPiece::MinParams& minValues, ArmorPiece::NameList whitelist, ArmorPiece::NameList blacklist) -> std::vector<ArmorSet>
	{
		if (minDifference < 0.F) minDifference = 0.F;

		const Parser parser{std::move(whitelist), std::move(blacklist)};
		auto groups = parser.ParseArmorGroups();

		if (!groups.HasElements()) return {};

		ArmorPiece::MinParams minValuesAdditive;
		ArmorPiece::MinParams minValuesDiminishing;

		for (const auto& [param, minValue] : minValues)
			if (SuffersFromDiminishingReturns(param))
				minValuesDiminishing.emplace_back(param, ToComparableValue(minValue));
			else
				minValuesAdditive.emplace_back(param, minValue);

		if (!minValuesAdditive.size() && !minValuesDiminishing.size())
			return IterateSets<false, false>(groups, availableLoad, toMaximize, minDifference, minValuesAdditive, minValuesDiminishing);

		else if (!minValuesAdditive.size() && minValuesDiminishing.size())
			return IterateSets<false, true>(groups, availableLoad, toMaximize, minDifference, minValuesAdditive, minValuesDiminishing);

		else if (minValuesAdditive.size() && !minValuesDiminishing.size())
			return IterateSets<true, false>(groups, availableLoad, toMaximize, minDifference, minValuesAdditive, minValuesDiminishing);

		else
			return IterateSets<true, true>(groups, availableLoad, toMaximize, minDifference, minValuesAdditive, minValuesDiminishing);
    }
}
