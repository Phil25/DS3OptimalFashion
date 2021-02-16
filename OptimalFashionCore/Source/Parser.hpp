#pragma once

#include <ArmorPiece.hpp>
#include <set>

namespace optifa
{
	class Parser final
	{
		const ArmorPiece::NameList globalWhitelist, globalBlacklist;

	public:
		Parser(ArmorPiece::NameList whitelist={}, ArmorPiece::NameList blacklist={});

		auto ParseArmorGroups() const -> ArmorGroups;

	private:
		auto ParseGroup(const char* type) const -> ArmorPiece::Vector;
	};
}