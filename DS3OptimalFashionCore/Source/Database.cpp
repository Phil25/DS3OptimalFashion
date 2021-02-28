#include "Database.h"

namespace optifa
{
	auto Database::Fetch(const ArmorPiece::NameList& whitelist, const ArmorPiece::NameList& blacklist) const -> Groups
	{
		using T = ArmorPiece::Type;

		return {
			{T::Head, FetchType(T::Head, whitelist, blacklist)},
			{T::Chest, FetchType(T::Chest, whitelist, blacklist)},
			{T::Hands, FetchType(T::Hands, whitelist, blacklist)},
			{T::Legs, FetchType(T::Legs, whitelist, blacklist)},
		};
	}

	auto Database::FetchType(const ArmorPiece::Type type, const ArmorPiece::NameList& globalWhitelist, const ArmorPiece::NameList& globalBlacklist) const -> ArmorPiece::Vector
	{
		ArmorPiece::NameList whitelist, blacklist;

		// calculate which whitelist and blacklist items are relevant for this type
		for (const auto& piece : db.at(type))
		{
			if (globalWhitelist.count(piece.name)) whitelist.insert(piece.name);
			if (globalBlacklist.count(piece.name)) blacklist.insert(piece.name);
		}

		// use everything in case no filters specified
		if (!whitelist.size() && !blacklist.size())
		{
			return db.at(type);
		}

		ArmorPiece::Vector pieces;

		for (const auto& piece : db.at(type))
		{
			if (blacklist.count(piece.name)) continue;
			if (!whitelist.empty() && !whitelist.count(piece.name)) continue;
			pieces.emplace_back(piece);
		}

		return pieces;
	}
}
