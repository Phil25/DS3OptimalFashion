#pragma once

#include <ArmorSet.hpp>

namespace optifa
{
	auto FindOptimal(const float availableLoad, const ArmorPiece::Param toMaximize, float minDifference=0.F,
		const ArmorPiece::MinParams& minValues={}, ArmorPiece::NameList whitelist={}, ArmorPiece::NameList blacklist={}) -> std::vector<ArmorSet>;
}
