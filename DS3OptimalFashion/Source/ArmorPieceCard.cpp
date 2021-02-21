#include "ArmorPieceCard.h"

ArmorPieceCard::ArmorPieceCard(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, icon(new wxPanel(this, wxID_ANY))
	, label(new wxTextCtrl(this, wxID_ANY, wxT("Iron Dragonslayer Gauntlets"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxTE_READONLY | wxBORDER_NONE))
{
	icon->SetBackgroundColour(wxColor(100, 50, 200));
	icon->Bind(wxEVT_ENTER_WINDOW, &ArmorPieceCard::OnStartHover, this);
	icon->Bind(wxEVT_LEAVE_WINDOW, &ArmorPieceCard::OnExitHover, this);
	icon->SetCursor(wxCursor(wxCURSOR_HAND));

	label->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

	sizer->Add(icon, 6, wxEXPAND | wxALL, 5);
	sizer->Add(label, 1, wxEXPAND);

	this->SetSizerAndFit(sizer);
}

void ArmorPieceCard::OnStartHover(wxMouseEvent& event)
{
	icon->SetBackgroundColour(wxColor(120, 60, 240));
	icon->Refresh();
	event.Skip();
}

void ArmorPieceCard::OnExitHover(wxMouseEvent& event)
{
	icon->SetBackgroundColour(wxColor(100, 50, 200));
	icon->Refresh();
	event.Skip();
}
