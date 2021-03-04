#include "ArmorFinder.h"

#include <Database.h>
#include <cassert>

constexpr char cr = '\n';

namespace
{
#pragma warning(push)
#pragma warning(disable: 4102)  // disable unreferenced label warning in IterateSets<false, false>
	template <bool HasAdditiveParamLimits, bool HasDiminishingParamLimits>
	auto IterateSets(
		const optifa::Database::Groups& groups, const float availableLoad, const optifa::ArmorPiece::Param toMaximize, float minDifference,
		const optifa::ArmorPiece::MinParams& minValuesAdditive, const optifa::ArmorPiece::MinParams& minValuesDiminishing)
	{
		assert(minDifference >= 0.F);

		const auto& head = groups.at(optifa::ArmorPiece::Type::Head);
		const auto& chest = groups.at(optifa::ArmorPiece::Type::Chest);
		const auto& hands = groups.at(optifa::ArmorPiece::Type::Hands);
		const auto& legs = groups.at(optifa::ArmorPiece::Type::Legs);

		assert(!head.empty() && !chest.empty() && !hands.empty() && !legs.empty());

		const auto calcParam = SuffersFromDiminishingReturns(toMaximize) ? optifa::CalculateDiminishing<false> : optifa::CalculateAdditive;
		auto bestParam = calcParam(head[0], chest[0], hands[0], legs[0], toMaximize);

		// in case of params with diminishing returns, include the value modifiers stripped from CalculateDiminishing<false>
		minDifference = SuffersFromDiminishingReturns(toMaximize) ? minDifference * 1'000'000 : minDifference;

		optifa::ArmorSet::Vector sets;

		for (const auto& he : head)
		for (const auto& ch : chest)
		for (const auto& ha : hands)
		for (const auto& le : legs)
		{
			auto param = calcParam(he, ch, ha, le, toMaximize);

			if constexpr (HasAdditiveParamLimits)
			{
				for (const auto& [param, minValue] : minValuesAdditive)
					if (optifa::CalculateAdditive(he, ch, ha, le, param) < minValue)
						goto next_set;
			}

			if constexpr (HasDiminishingParamLimits)
			{
				for (const auto& [param, minValue] : minValuesDiminishing)
					if (optifa::CalculateDiminishing<false>(he, ch, ha, le, param) < minValue)
						goto next_set;
			}

			if (param >= bestParam - minDifference && CalculateAdditive(he, ch, ha, le, optifa::ArmorPiece::Param::Weight) <= availableLoad)
			{
				if (param > bestParam) bestParam = param;
				sets.emplace_back(he, ch, ha, le);
			}

			next_set:;
		}

		optifa::ArmorSet::Vector topSets;

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
	auto FindOptimal(const Database& db, const float availableLoad, const ArmorPiece::Param toMaximize, float minDifference,
		const ArmorPiece::MinParams& minValues, ArmorPiece::NameList whitelist, ArmorPiece::NameList blacklist) -> ArmorSet::Vector
	{
		if (minDifference < 0.F) minDifference = 0.F;

		const auto groups = db.Fetch(whitelist, blacklist);

		if (!groups.at(ArmorPiece::Type::Head).size() ||
			!groups.at(ArmorPiece::Type::Chest).size() ||
			!groups.at(ArmorPiece::Type::Hands).size() ||
			!groups.at(ArmorPiece::Type::Legs).size())
			return {};

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
