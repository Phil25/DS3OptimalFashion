#include <iostream>
#include <ArmorFinder.hpp>

/// <summary>
/// Barebones interface for using the library (one you have to compile yourself).
/// Adjust `availableLoad` and `toMaximize` appropriately. Optionally specify:
/// * minimal difference from most optimal param value, for more than one result,
/// * minimal values for each parameter,
/// * whitelist of armor pieces,
/// * blacklist of armor pieces.
/// 
/// Example:
/// FindOptimal(36.F, P::Physical, 0.1, {{P::Fire, 25.F}, {P::Poise, 39.72F}}, {"Iron Helm", "Catarina Helm"}, {"Exile Leggings", "Catarina Armor"}))
/// The above finds armor under 36 weight, maximizes the physical absorption
/// but additionally returns armor sets with higher or equal 0.1 difference from the most optimal,
/// it also makes sure fire defense is above 25, poise is above 39.72,
/// and for actual pieces it considers only Iron Helm or Catarina Helm for head,
/// while excluding Exile Leggins and Catarina Armor for their respective slots.
/// </summary>

constexpr char cr = '\n';
using P = optifa::ArmorPiece::Param;

inline void PrintArmorSet(const optifa::ArmorSet& set)
{
	std::cout << set.head.name << ", " << set.chest.name << ", " << set.hands.name << ", " << set.legs.name << cr;

	std::cout << "Physical: " << set.Get<P::Physical>() << " (";
	std::cout << "St: " << set.Get<P::Strike>() << ", ";
	std::cout << "Sl: " << set.Get<P::Slash>() << ", ";
	std::cout << "Th: " << set.Get<P::Thrust>() << ')' << cr;

	std::cout << "Magic: " << set.Get<P::Magic>() << ", ";
	std::cout << "Fire: " << set.Get<P::Fire>() << ", ";
	std::cout << "Lightning: " << set.Get<P::Lightning>() << ", ";
	std::cout << "Dark: " << set.Get<P::Dark>() << cr;

	std::cout << "Bleed: " << set.Get<P::Bleed>() << ", ";
	std::cout << "Poison: " << set.Get<P::Poison>() << ", ";
	std::cout << "Frost: " << set.Get<P::Frost>() << ", ";
	std::cout << "Curse: " << set.Get<P::Curse>() << cr;

	std::cout << "Poise: " << set.Get<P::Poise>() << ", ";
	std::cout << "Weight: " << set.Get<P::Weight>() << cr;
}

int main()
{
	const auto availableLoad = 26.7F;
	const auto toMaximize = P::Physical;
	const auto minDifference = 0.1F;

	const auto sets = optifa::FindOptimal(availableLoad, toMaximize, minDifference);

	int i = 0;
	for (const auto& set : sets)
	{
		std::cout << "===== Set #" << ++i << cr;
		PrintArmorSet(set);
		std::cout << cr;
	}

	std::cout << "Found " << sets.size() << " set(s)." << cr;

	return 0;
}