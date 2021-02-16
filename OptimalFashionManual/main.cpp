#include <iostream>
#include <ArmorFinder.hpp>

/// <summary>
/// Barebones interface for using the library (one you have to compile yourself).
/// Adjust `availableLoad` and `toMaximize` appropriately. Optionally specify:
/// * minimal values for each parameter,
/// * whitelist of armor pieces,
/// * blacklist of armor pieces.
/// 
/// Example:
/// FindOptimal(36.F, P::Physical, {{P::Fire, 25.F}, {P::Poise, 39.72F}}, {"Iron Helm", "Catarina Helm"}, {"Exile Leggings", "Catarina Armor"}))
/// The above finds armor under 36 weight, maximizes the physical absorption, makes sure fire defense is above 25, poise is above 39.72,
/// and considers only Iron Helm or Catarina Helm for head, while excluding Exile Leggins and Catarina Armor.
/// </summary>

constexpr char cr = '\n';

int main()
{
    using P = optifa::ArmorPiece::Param;

	float availableLoad = 32.18F;
	auto toMaximize = P::Poise;

	if (auto set = optifa::FindOptimal(availableLoad, toMaximize))
	{
		std::cout << set->head.name << ", " << set->chest.name << ", " << set->hands.name << ", " << set->legs.name << cr;

		std::cout << "Physical: " << set->Get<P::Physical>() << " (";
		std::cout << "St: " << set->Get<P::Strike>() << ", ";
		std::cout << "Sl: " << set->Get<P::Slash>() << ", ";
		std::cout << "Th: " << set->Get<P::Thrust>() << ')' << cr;

		std::cout << "Magic: " << set->Get<P::Magic>() << ", ";
		std::cout << "Fire: " << set->Get<P::Fire>() << ", ";
		std::cout << "Lightning: " << set->Get<P::Lightning>() << ", ";
		std::cout << "Dark: " << set->Get<P::Dark>() << cr;

		std::cout << "Bleed: " << set->Get<P::Bleed>() << ", ";
		std::cout << "Poison: " << set->Get<P::Poison>() << ", ";
		std::cout << "Frost: " << set->Get<P::Frost>() << ", ";
		std::cout << "Curse: " << set->Get<P::Curse>() << cr;

		std::cout << "Poise: " << set->Get<P::Poise>() << ", ";
		std::cout << "Weight: " << set->Get<P::Weight>() << cr;
	}
	else
	{
		std::cout << "No sets found." << cr;
	}

	return 0;
}