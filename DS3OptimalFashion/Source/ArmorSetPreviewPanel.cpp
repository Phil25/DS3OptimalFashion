#include "ArmorSetPreviewPanel.h"

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, head(new ArmorPieceCard(this))
	, chest(new ArmorPieceCard(this))
	, hands(new ArmorPieceCard(this))
	, legs(new ArmorPieceCard(this))
{
	sizer->Add(head, 0, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(chest, 0, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(hands, 0, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(legs, 0, wxEXPAND | wxBOTTOM | wxTOP, 10);

	this->SetSizerAndFit(sizer);
}
