#pragma once

#include <ArmorPiece.hpp>
#include <Utils.hpp>
#include <memory>

namespace optifa
{
	struct ArmorSet final
	{
		using Vector = std::vector<std::shared_ptr<ArmorSet>>;

		const ArmorPiece head, chest, hands, legs;

		ArmorSet(ArmorPiece head, ArmorPiece chest, ArmorPiece hands, ArmorPiece legs) noexcept
			: head(std::move(head)), chest(std::move(chest)), hands(std::move(hands)), legs(std::move(legs))
		{
		}

		inline float Get(const ArmorPiece::Param param) const noexcept
		{
			if (SuffersFromDiminishingReturns(param))
				return CalculateDiminishing(head, chest, hands, legs, param);
			else
				return CalculateAdditive(head, chest, hands, legs, param);
		}
	};
}
