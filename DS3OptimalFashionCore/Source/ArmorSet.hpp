#pragma once

#include <ArmorPiece.hpp>
#include <Utils.hpp>

namespace optifa
{
	struct ArmorSet final
	{
		using Vector = std::vector<ArmorSet>;

		const ArmorPiece head, chest, hands, legs;

		ArmorSet(ArmorPiece head, ArmorPiece chest, ArmorPiece hands, ArmorPiece legs) noexcept
			: head(std::move(head)), chest(std::move(chest)), hands(std::move(hands)), legs(std::move(legs))
		{
		}

		template <ArmorPiece::Param Param>
		inline float Get() const noexcept
		{
			if constexpr (SuffersFromDiminishingReturns(Param))
				return CalculateDiminishing(head, chest, hands, legs, Param);
			else
				return CalculateAdditive(head, chest, hands, legs, Param);
		}
	};
}
