#pragma once

#include <ArmorPiece.hpp>

namespace optifa
{
	inline float CalculateAdditive(const ArmorPiece& head, const ArmorPiece& chest, const ArmorPiece& hands, const ArmorPiece& legs, const ArmorPiece::Param p) noexcept
	{
		return head.Get(p) + chest.Get(p) + hands.Get(p) + legs.Get(p);
	}

	template <bool Exact=true>
	inline float CalculateDiminishing(const ArmorPiece& head, const ArmorPiece& chest, const ArmorPiece& hands, const ArmorPiece& legs, const ArmorPiece::Param p) noexcept
	{
		const auto a = head.Get(p), b = chest.Get(p), c = hands.Get(p), d = legs.Get(p);
		if constexpr (Exact)
		{
			// simplified (1 - (1 - a/100) * (1 - b/100) * (1 - c/100) * (1 - d/100)) * 100;
			return (1 - (a - 100) * (b - 100) * (c - 100) * (d - 100) / 1'00'00'00'00) * 100;
		}
		else
		{
			// stripped of modifiers, for comparison purposes
			return 1 - (a - 100) * (b - 100) * (c - 100) * (d - 100);
		}
	}

	constexpr float ToComparableValue(const float val) noexcept
	{
		// take an end value, and turn it into value comparable with CalculateDiminishing<false>()
		return (val / 100 - 1) * 1'00'00'00'00;
	}

	constexpr bool SuffersFromDiminishingReturns(const ArmorPiece::Param param) noexcept
	{
		/*
			Physical, Strike, Slash, Thrust,
			Magic, Fire, Lightning, Dark,
			Bleed, Poison, Frost, Curse,
			Poise, Weight,
			Size
		*/
		return (1 << static_cast<uint32_t>(param)) & 0b0'01'0000'1111'1111;
	}
}
