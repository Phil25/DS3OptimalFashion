#pragma once

#include <Utils/ArmorPieceCard.h>

class ArmorSetPreviewPanel final : public wxPanel
{
	class ArmorUpdater;
	std::unique_ptr<ArmorUpdater> armorUpdater;

	ArmorPieceCard<CardPurpose::Preview>* head{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* chest{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* hands{nullptr};
	ArmorPieceCard<CardPurpose::Preview>* legs{nullptr};

public:
	ArmorSetPreviewPanel(wxWindow* parent);
};
