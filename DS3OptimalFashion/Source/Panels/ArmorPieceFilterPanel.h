#pragma once

#include <Panels/Details/TitlePanel.h>

class ArmorPieceFilterPanel final : public TitlePanel
{
	const bool isWhitelist;

public:
	ArmorPieceFilterPanel(wxWindow* parent, const bool isWhitelist=true);
};