#pragma once

#include <Utils/ArmorPieceCard.h>

class ArmorSetPreviewPanel final : public wxPanel
{
	ArmorPieceCard<CardPurpose::Preview>* head{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* chest{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* hands{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* legs{nullptr};

public:
	ArmorSetPreviewPanel(wxWindow* parent);

	void SetHead(std::string);
	void SetChest(std::string);
	void SetHands(std::string);
	void SetLegs(std::string);
};
