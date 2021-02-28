#pragma once

#include <ArmorPieceCard.h>

class ArmorSetPreviewPanel final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};

	ArmorPieceCard<CardPurpose::Preview>* head{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* chest{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* hands{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* legs{nullptr};

public:
	ArmorSetPreviewPanel(wxWindow* parent);
};
