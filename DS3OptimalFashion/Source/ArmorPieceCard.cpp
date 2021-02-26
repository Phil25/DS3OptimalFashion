#include "ArmorPieceCard.h"
#include <wx/wfstream.h>
#include <wx/bitmap.h>
#include <sstream>

ArmorPieceIcon::ArmorPieceIcon(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, image("./DS3OptimalFashion_Images/Alva Armor.png", wxBITMAP_TYPE_PNG)
{
	Bind(wxEVT_PAINT, [&](wxPaintEvent&) { this->Render(wxPaintDC{this}); });
	Bind(wxEVT_SIZE, [&](wxSizeEvent& e) { this->Refresh(); e.Skip(); });
}

void ArmorPieceIcon::SetIcon(const std::string& file)
{
	image.LoadFile(file, wxBITMAP_TYPE_PNG);
	Refresh();
}

void ArmorPieceIcon::Render(wxDC& dc)
{
	const auto size = dc.GetSize();
	const int length = wxMin(size.GetWidth(), size.GetHeight());

	if (highlighted)
	{
		const double radius = 3.0;
		dc.SetPen(wxPen(wxColor(128,128,64), radius));
		dc.DrawRoundedRectangle(radius, radius, length - radius * 2, length - radius * 2, 10.0);
	}

	const auto bitmap = wxBitmap{image.Scale(length, length)};
	dc.DrawBitmap(bitmap, 0, 0, false);
}

void ArmorPieceIcon::SetHighlight(const bool highlight)
{
	highlighted = highlight;
	Refresh();
}

ArmorPieceCard::ArmorPieceCard(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, icon(new ArmorPieceIcon(this))
	, label(new wxTextCtrl(this, wxID_ANY, wxT("Naked"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxTE_READONLY | wxBORDER_NONE))
{
	icon->Bind(wxEVT_ENTER_WINDOW, &ArmorPieceCard::OnStartHover, this);
	icon->Bind(wxEVT_LEAVE_WINDOW, &ArmorPieceCard::OnExitHover, this);
	icon->SetCursor(wxCursor(wxCURSOR_HAND));

	label->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

	sizer->Add(icon, 6, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	sizer->Add(label, 1, wxEXPAND);

	this->SetSizerAndFit(sizer);
}

void ArmorPieceCard::SetPiece(const std::string& name)
{
	label->SetValue(name);

	std::ostringstream oss;
	oss << "./DS3OptimalFashion_Images/" << name << ".png";
	icon->SetIcon(oss.str());
}

void ArmorPieceCard::OnStartHover(wxMouseEvent& event)
{
	icon->SetHighlight(true);
}

void ArmorPieceCard::OnExitHover(wxMouseEvent& event)
{
	icon->SetHighlight(false);
}
