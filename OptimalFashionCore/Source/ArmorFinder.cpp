#include "ArmorFinder.hpp"
#include "Parser.hpp"

namespace
{

#pragma warning(push)
#pragma warning(disable: 4102)  // disable unreferenced label warning in IterateSets<false, false>
	template <bool HasAdditiveParamLimits, bool HasDiminishingParamLimits>
	auto IterateSets(
		optifa::ArmorGroups& armor, const float availableLoad, const optifa::ArmorPiece::Param toMaximize,
		const optifa::ArmorPiece::MinParams& minValuesAdditive, const optifa::ArmorPiece::MinParams& minValuesDiminishing)
	{
		const auto calcParam = SuffersFromDiminishingReturns(toMaximize) ? optifa::CalculateDiminishing<false> : optifa::CalculateAdditive;

		auto& bestHead = armor.head[0];
		auto& bestChest = armor.chest[0];
		auto& bestHands = armor.hands[0];
		auto& bestLegs = armor.legs[0];
		auto bestParam = calcParam(bestHead, bestChest, bestHands, bestLegs, toMaximize);

		for (const auto& he : armor.head)
		for (const auto& ch : armor.chest)
		for (const auto& ha : armor.hands)
		for (const auto& le : armor.legs)
		{
			auto param = calcParam(he, ch, ha, le, toMaximize);

			if constexpr (HasAdditiveParamLimits)
				for (const auto& [param, minValue] : minValuesAdditive)
					if (optifa::CalculateAdditive(he, ch, ha, le, param) < minValue)
						goto next_set;

			if constexpr (HasDiminishingParamLimits)
				for (const auto& [param, minValue] : minValuesDiminishing)
					if (optifa::CalculateDiminishing<false>(he, ch, ha, le, param) < minValue)
						goto next_set;

			if (param > bestParam && CalculateAdditive(he, ch, ha, le, optifa::ArmorPiece::Param::Weight) <= availableLoad + 0.01)
			{
				bestParam = param;
				bestHead = he;
				bestChest = ch;
				bestHands = ha;
				bestLegs = le;
			}

			next_set:;
		}

		return optifa::ArmorSet{bestHead, bestChest, bestHands, bestLegs};
	}
#pragma warning(pop)
}

namespace optifa
{
    auto FindOptimal(const float availableLoad, const ArmorPiece::Param toMaximize, const ArmorPiece::MinParams& minValues,
		ArmorPiece::NameList whitelist, ArmorPiece::NameList blacklist) -> std::optional<ArmorSet>
    {
		const Parser parser{std::move(whitelist), std::move(blacklist)};
		auto groups = parser.ParseArmorGroups();

		if (!groups.HasElements()) return std::nullopt;

		ArmorPiece::MinParams minValuesAdditive;
		ArmorPiece::MinParams minValuesDiminishing;

		// split into separate containers so different calculation function can be used
		for (const auto& [param, minValue] : minValues)
			if (SuffersFromDiminishingReturns(param))
				minValuesDiminishing.emplace_back(param, ToComparableValue(minValue));
			else
				minValuesAdditive.emplace_back(param, minValue);

		if (!minValuesAdditive.size() && !minValuesDiminishing.size())
			return IterateSets<false, false>(groups, availableLoad, toMaximize, minValuesAdditive, minValuesDiminishing);

		else if (!minValuesAdditive.size() && minValuesDiminishing.size())
			return IterateSets<false, true>(groups, availableLoad, toMaximize, minValuesAdditive, minValuesDiminishing);

		else if (minValuesAdditive.size() && !minValuesDiminishing.size())
			return IterateSets<true, false>(groups, availableLoad, toMaximize, minValuesAdditive, minValuesDiminishing);

		else
			return IterateSets<true, true>(groups, availableLoad, toMaximize, minValuesAdditive, minValuesDiminishing);
    }
}
