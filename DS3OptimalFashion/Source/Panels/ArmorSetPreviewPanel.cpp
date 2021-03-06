#include "ArmorSetPreviewPanel.h"

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, head(new ArmorPieceCard<CardPurpose::Preview>(this))
	, chest(new ArmorPieceCard<CardPurpose::Preview>(this))
	, hands(new ArmorPieceCard<CardPurpose::Preview>(this))
	, handsr(new ArmorPieceCard<CardPurpose::Preview>(this, true))
	, legs(new ArmorPieceCard<CardPurpose::Preview>(this))
{
	head->SetArmorPiece("Naked Head");
	chest->SetArmorPiece("Naked Chest");
	hands->SetArmorPiece("Naked Hands");
	handsr->SetArmorPiece("Naked Hands");
	legs->SetArmorPiece("Naked Legs");

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* section1 = new wxBoxSizer(wxVERTICAL);
	auto* section2 = new wxBoxSizer(wxVERTICAL);
	auto* section3 = new wxBoxSizer(wxVERTICAL);

	section1->AddStretchSpacer(2);
	section1->Add(hands, 1, wxEXPAND);
	section1->AddStretchSpacer(1);

	section2->Add(head, 1, wxEXPAND);
	section2->Add(chest, 1, wxEXPAND);
	section2->Add(legs, 1, wxEXPAND);

	section3->AddStretchSpacer(2);
	section3->Add(handsr, 1, wxEXPAND);
	section3->AddStretchSpacer(1);

	sizer->Add(section1, 1, wxEXPAND);
	sizer->Add(section2, 2, wxEXPAND);
	sizer->Add(section3, 1, wxEXPAND);

	SetSizerAndFit(sizer);
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
	hands->SetArmorPiece(name);
	handsr->SetArmorPiece(std::move(name));
}

void ArmorSetPreviewPanel::SetLegs(std::string name)
{
	legs->SetArmorPiece(std::move(name));
}
