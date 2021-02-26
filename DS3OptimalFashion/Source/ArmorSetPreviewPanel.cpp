#include "ArmorSetPreviewPanel.h"

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, head(new ArmorPieceCard(this))
	, chest(new ArmorPieceCard(this))
	, hands(new ArmorPieceCard(this))
	, legs(new ArmorPieceCard(this))
{
	head->SetPiece("Iron Helm");
	chest->SetPiece("Faraam Armor");
	hands->SetPiece("Ruin Sentinel Gauntlets");
	legs->SetPiece("Exile Leggings");

	sizer->Add(head, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(chest, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(hands, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(legs, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);

	this->SetSizerAndFit(sizer);
}
