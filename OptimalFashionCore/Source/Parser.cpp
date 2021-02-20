#include "Parser.hpp"
#pragma warning(push, 0)
#include <csv.h>
#pragma warning(pop)
#include <iostream>

namespace optifa
{
	Parser::Parser(ArmorPiece::NameList whitelist, ArmorPiece::NameList blacklist)
		: globalWhitelist(whitelist), globalBlacklist(blacklist)
	{
	}

	auto Parser::ParseArmorGroups() const -> ArmorGroups
	{
		return {
			ParseGroup("Data/head.csv"),
			ParseGroup("Data/chest.csv"),
			ParseGroup("Data/hands.csv"),
			ParseGroup("Data/legs.csv"),
		};
	}

	auto Parser::ParseGroup(const char* type) const -> ArmorPiece::Vector
	{
		ArmorPiece::Vector allPieces;
		ArmorPiece::NameList whitelist, blacklist;

		std::string name;
		ArmorPiece::ParamArray p;

		try
		{
			io::CSVReader<static_cast<size_t>(ArmorPiece::Param::Size) + 1> in(type);

			// first pass to parse csv and determine which group do white/blacklisted items belong to
			while (in.read_row(name, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]))
			{
				if (globalWhitelist.count(name)) whitelist.insert(name);
				if (globalBlacklist.count(name)) blacklist.insert(name);
				allPieces.emplace_back(std::make_unique<ArmorPiece>(name, p));
			}
		}
		catch (const io::error::can_not_open_file&)
		{
			std::cerr << "File not found: " << type << '\n';
			return {};
		}

		// second pass to filter items in/out
		ArmorPiece::Vector pieces;
		for (auto& piece : allPieces)
		{
			if (blacklist.count(piece->name)) continue;
			if (!whitelist.empty() && !whitelist.count(piece->name)) continue;
			pieces.emplace_back(std::move(piece));
		}

		return pieces;
	}
}
