#pragma once

#include <ArmorPiece.hpp>
#include <map>

namespace optifa
{
	class Database final
	{

		using Groups = std::map<ArmorPiece::Type, ArmorPiece::Vector>;

#pragma warning(push)
#pragma warning(disable: 4305)  // disable truncation from double to _Ty
		const Groups db{
			{
				ArmorPiece::Type::Head,
				{
					#include "Data/head.txt"
				}
			},
			{
				ArmorPiece::Type::Chest,
				{
					#include "Data/chest.txt"
				}
			},
			{
				ArmorPiece::Type::Hands,
				{
					#include "Data/hands.txt"
				}
			},
			{
				ArmorPiece::Type::Legs,
				{
					#include "Data/legs.txt"
				}
			}
		};
#pragma warning(pop)

	public:
		Database() = default;

		auto Fetch(const ArmorPiece::NameList& whitelist={}, const ArmorPiece::NameList& blacklist={}) const -> Groups;

	private:
		auto FetchType(const ArmorPiece::Type, const ArmorPiece::NameList& whitelist, const ArmorPiece::NameList& blacklist) const -> ArmorPiece::Vector;
	};
}