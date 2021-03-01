#include "ArmorSetPreviewPanel.h"

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, head(new ArmorPieceCard<CardPurpose::Preview>(this))
	, chest(new ArmorPieceCard<CardPurpose::Preview>(this))
	, hands(new ArmorPieceCard<CardPurpose::Preview>(this))
	, legs(new ArmorPieceCard<CardPurpose::Preview>(this))
{
	head->SetArmorPiece("Iron Helm");
	chest->SetArmorPiece("Faraam Armor");
	hands->SetArmorPiece("Ruin Sentinel Gauntlets");
	legs->SetArmorPiece("Exile Leggings");

	sizer->Add(head, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(chest, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(hands, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(legs, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);

	this->SetSizerAndFit(sizer);
}
