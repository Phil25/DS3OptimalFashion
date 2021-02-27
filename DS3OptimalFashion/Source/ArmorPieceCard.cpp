#include "ArmorPieceCard.h"
#include <wx/wfstream.h>
#include <wx/bitmap.h>
#include <sstream>

ArmorPieceIcon::ArmorPieceIcon(wxWindow* parent, const bool miniature)
	: wxPanel(parent, wxID_ANY)
	, image("./DS3OptimalFashion_Images/Alva Armor.png", wxBITMAP_TYPE_PNG)
	, miniature(miniature)
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

	if (highlighted && !miniature)
	{
		const double radius = 3.0;

		dc.SetPen(wxPen(wxColor(128,128,64), radius));
		dc.DrawRoundedRectangle(radius, radius, length - radius * 2, length - radius * 2, 10.0);
	}

	const auto bitmap = wxBitmap{image.Scale(length, length, resizeQuality)};
	dc.DrawBitmap(bitmap, 0, 0, false);

	if (highlighted && miniature)
	{
		const double offset = 15.0;
		const double farEnd = length - offset * 2;

		dc.SetPen(wxPen(wxColor(200,64,64), 5.0));
		dc.DrawLine(wxPoint(offset, offset), wxPoint(farEnd, farEnd));
		dc.DrawLine(wxPoint(offset, farEnd), wxPoint(farEnd, offset));
	}
}

void ArmorPieceIcon::SetHighlight(const bool highlight)
{
	highlighted = highlight;
	Refresh();
}

ArmorPieceCard::ArmorPieceCard(wxWindow* parent, const bool miniature)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, icon(new ArmorPieceIcon(this, miniature))
	, label(new wxTextCtrl(this, wxID_ANY, wxT("Naked"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxTE_READONLY | wxBORDER_NONE))
	, miniature(miniature)
{
	icon->Bind(wxEVT_ENTER_WINDOW, &ArmorPieceCard::OnStartHover, this);
	icon->Bind(wxEVT_LEAVE_WINDOW, &ArmorPieceCard::OnExitHover, this);
	icon->SetCursor(wxCursor(wxCURSOR_HAND));

	label->SetFont(miniature
		? wxFont(7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD)
		: wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

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
