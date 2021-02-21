#pragma once

#include <ArmorPieceCard.h>

class ArmorSetPreviewPanel final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};

	ArmorPieceCard* head{nullptr};
	ArmorPieceCard* chest{nullptr};
	ArmorPieceCard* hands{nullptr};
	ArmorPieceCard* legs{nullptr};

public:
	ArmorSetPreviewPanel(wxWindow* parent);
};
