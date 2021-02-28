#include "ArmorPieceCard.h"

#include <AppMain.h>
#include <wx/wfstream.h>
#include <wx/bitmap.h>
#include <sstream>

template <CardPurpose Purpose>
class ArmorPieceIcon final : public wxPanel
{
	std::string name;
	bool highlighted{false}, marked{false};

public:
	ArmorPieceIcon(wxWindow* parent)
		: wxPanel(parent, wxID_ANY)
		, name("Naked Chest")
	{
		Bind(wxEVT_PAINT, [&](wxPaintEvent&) { this->Render(wxPaintDC{this}); });

		if constexpr (Purpose != CardPurpose::Browser)
		{
			// armor browser cannot be resized, no need to bind that
			Bind(wxEVT_SIZE, [&](wxSizeEvent& e) { this->Refresh(); });
		}
	}

	void SetIcon(std::string file)
	{
		name = std::move(file);
		Refresh();
	}

	void SetHighlight(const bool val=true)
	{
		highlighted = val;
		Refresh();
	}

	void SetMark(const bool val=true)
	{
		marked = val;
		Refresh();
	}

	bool IsMarked() const
	{
		return marked;
	}

private:
	void Render(wxDC& dc)
	{
		const auto size = dc.GetSize();
		const int length = wxMin(size.GetWidth(), size.GetHeight());

		if constexpr (Purpose == CardPurpose::Preview)
		{
			if (highlighted)
				dc.DrawBitmap(wxGetApp().GetImageCache()->Selection(length, Purpose), 0, 0, false);
		}

		if constexpr (Purpose == CardPurpose::Browser)
		{
			if (marked)
				dc.DrawBitmap(wxGetApp().GetImageCache()->Mark(length, Purpose), 0, 0, false);

			else if (highlighted)
				dc.DrawBitmap(wxGetApp().GetImageCache()->Selection(length, Purpose), 0, 0, false);
		}

		dc.DrawBitmap(wxGetApp().GetImageCache()->Get(name, length, Purpose), 0, 0, false);

		if constexpr (Purpose == CardPurpose::Filter)
		{
			if (highlighted)
			{
				const double offset = 15.0;
				const double farEnd = length - offset * 2;

				dc.SetPen(wxPen (wxColor (200, 64, 64), 5.0));
				dc.DrawLine(wxPoint (offset, offset), wxPoint (farEnd, farEnd));
				dc.DrawLine(wxPoint (offset, farEnd), wxPoint (farEnd, offset));
			}
		}
	}
};

template <CardPurpose Purpose>
ArmorPieceCard<Purpose>::ArmorPieceCard(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, icon(new ArmorPieceIcon<Purpose>(this))
	, label(new wxTextCtrl(this, wxID_ANY, wxT("Naked"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxTE_READONLY | wxBORDER_NONE))
{
	icon->Bind(wxEVT_ENTER_WINDOW, &ArmorPieceCard::OnStartHover, this);
	icon->Bind(wxEVT_LEAVE_WINDOW, &ArmorPieceCard::OnExitHover, this);
	icon->Bind(wxEVT_LEFT_UP, &ArmorPieceCard::OnClick, this);
	icon->SetCursor(wxCursor(wxCURSOR_HAND));

	if constexpr (Purpose == CardPurpose::Preview)
		label->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

	else if constexpr (Purpose == CardPurpose::Filter)
		label->SetFont(wxFont(7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	else if constexpr (Purpose == CardPurpose::Browser)
		label->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

	else static_assert(false, "Incorrect CardPurpose");

	sizer->Add(icon, 6, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	sizer->Add(label, 1, wxEXPAND);

	this->SetSizerAndFit(sizer);
}

template <CardPurpose P>
void ArmorPieceCard<P>::SetPiece(const std::string& name)
{
	label->SetValue(name);
	icon->SetIcon(name);
}

template <CardPurpose P>
void ArmorPieceCard<P>::OnStartHover(wxMouseEvent&)
{
	icon->SetHighlight(true);
}

template <CardPurpose P>
void ArmorPieceCard<P>::OnExitHover(wxMouseEvent&)
{
	icon->SetHighlight(false);
}

template <CardPurpose P>
void ArmorPieceCard<P>::OnClick(wxMouseEvent& event)
{
	icon->SetMark(!icon->IsMarked());
}

template class ArmorPieceCard<CardPurpose::Preview>;
template class ArmorPieceCard<CardPurpose::Filter>;
template class ArmorPieceCard<CardPurpose::Browser>;

template class ArmorPieceIcon<CardPurpose::Preview>;
template class ArmorPieceIcon<CardPurpose::Filter>;
template class ArmorPieceIcon<CardPurpose::Browser>;
