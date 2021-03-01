#pragma once

enum class CardPurpose
{
	Preview,   // card is displayed in the preview panel
	Filter,    // card is displayed in the whitelist/blacklist filters
	Whitelist, // card is displayed in the whitelist item selector
	Blacklist, // card is displayed in the blacklist item selector
	Size
};
