#pragma once

#include <ArmorSet.hpp>
#include <optional>

namespace optifa
{
	auto FindOptimal(const float availableLoad, const ArmorPiece::Param toMaximize, const ArmorPiece::MinParams& minValues={},
		ArmorPiece::NameList whitelist={}, ArmorPiece::NameList blacklist={}) -> std::optional<ArmorSet>;
}
