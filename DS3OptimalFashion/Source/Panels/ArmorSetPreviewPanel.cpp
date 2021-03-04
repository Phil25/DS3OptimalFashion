#include "ArmorSetPreviewPanel.h"

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, head(new ArmorPieceCard<CardPurpose::Preview>(this))
	, chest(new ArmorPieceCard<CardPurpose::Preview>(this))
	, hands(new ArmorPieceCard<CardPurpose::Preview>(this))
	, legs(new ArmorPieceCard<CardPurpose::Preview>(this))
{
	head->SetArmorPiece("Naked Head");
	chest->SetArmorPiece("Naked Chest");
	hands->SetArmorPiece("Naked Hands");
	legs->SetArmorPiece("Naked Legs");

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(head, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(chest, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(hands, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(legs, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);

	this->SetSizerAndFit(sizer);
}

void ArmorSetPreviewPanel::SetHead(std::string name)
{
	head->SetArmorPiece(std::move(name));
}

void ArmorSetPreviewPanel::SetChest(std::string name)
{
	chest->SetArmorPiece(std::move(name));
}

void ArmorSetPreviewPanel::SetHands(std::string name)
{
	hands->SetArmorPiece(std::move(name));
}

void ArmorSetPreviewPanel::SetLegs(std::string name)
{
	legs->SetArmorPiece(std::move(name));
}
