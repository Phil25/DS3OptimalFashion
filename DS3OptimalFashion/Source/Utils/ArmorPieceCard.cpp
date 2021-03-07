#include "ArmorPieceCard.h"

#include <AppMain.h>
#include <wx/clipbrd.h>
#include <sstream>

namespace
{
	enum class MenuOption
	{
		AddToWhitelist, AddToBlacklist,
		Details, CopyNameToClipboard, SearchOnGoogle,
		Size
	};

	auto GetGoogleURL(std::string name)
	{
		std::replace(name.begin(), name.end(), ' ', '+');
		std::ostringstream oss;
		oss << "https://www.google.com/search?q=Dark+Souls+III+" << name;
		return oss.str();
	}

	void CopyToClipBoard(const std::string& text)
	{
		if (wxTheClipboard->Open())
		{
			wxTheClipboard->SetData(new wxTextDataObject(text));
			wxTheClipboard->Close();
		}
	}
}

template <CardPurpose Purpose>
class ArmorPieceIcon final : public wxPanel
{
	ArmorPieceCard<Purpose>* parent{nullptr};
	bool highlighted{false}, marked{false};
	const bool flip;

public:
	ArmorPieceIcon(ArmorPieceCard<Purpose>* parent, const bool flip=false)
		: wxPanel(parent, wxID_ANY)
		, parent(parent)
		, flip(flip)
	{
		Bind(wxEVT_PAINT, [&](wxPaintEvent&) { this->Render(); });

		if constexpr (Purpose != CardPurpose::Whitelist && Purpose != CardPurpose::Blacklist)
		{
			// armor browser cannot be resized, no need to bind that
			Bind(wxEVT_SIZE, [&](wxSizeEvent& e) { this->Refresh(); });
		}
	}

	void SetIcon(const std::string& file)
	{
		if constexpr (Purpose == CardPurpose::Whitelist)
			marked = wxGetApp().GetParams().IsWhitelisted(file);

		else if constexpr (Purpose == CardPurpose::Blacklist)
			marked = wxGetApp().GetParams().IsBlacklisted(file);

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
	void Render()
	{
		auto dc = wxPaintDC{this};

		const auto size = dc.GetSize();
		const int length = wxMin(size.GetWidth(), size.GetHeight());

		if constexpr (Purpose == CardPurpose::Preview)
		{
			if (highlighted)
				dc.DrawBitmap(wxGetApp().GetImageCache()->Selection(length, Purpose), 0, 0, false);
		}

		if constexpr (Purpose == CardPurpose::Whitelist || Purpose == CardPurpose::Blacklist)
		{
			if (marked)
			{
				if constexpr (Purpose == CardPurpose::Whitelist)
					dc.DrawBitmap(wxGetApp().GetImageCache()->Mark(length, Purpose), 0, 0, false);
				else
					dc.DrawBitmap(wxGetApp().GetImageCache()->MarkDark(length, Purpose), 0, 0, false);
			}

			else if (highlighted)
				dc.DrawBitmap(wxGetApp().GetImageCache()->Selection(length, Purpose), 0, 0, false);
		}

		dc.DrawBitmap(wxGetApp().GetImageCache()->Get(parent->GetArmorPiece(), length, Purpose, flip), 0, 0, false);

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
ArmorPieceCard<Purpose>::ArmorPieceCard(wxWindow* parent, const bool flip)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxVERTICAL))
	, icon(new ArmorPieceIcon<Purpose>(this, flip))
{
	icon->Bind(wxEVT_ENTER_WINDOW, &ArmorPieceCard::OnStartHover, this);
	icon->Bind(wxEVT_LEAVE_WINDOW, &ArmorPieceCard::OnExitHover, this);
	icon->Bind(wxEVT_LEFT_UP, &ArmorPieceCard::OnLeftClick, this);
	icon->Bind(wxEVT_MIDDLE_UP, &ArmorPieceCard::OnMiddleClick, this);
	icon->Bind(wxEVT_RIGHT_UP, &ArmorPieceCard::OnRightClick, this);
	icon->SetCursor(wxCursor(wxCURSOR_HAND));
	sizer->Add(icon, 6, wxSHAPED | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	if constexpr (Purpose != CardPurpose::Preview)
	{
		label = new wxTextCtrl(this, wxID_ANY, name, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxTE_READONLY | wxBORDER_NONE);

		if constexpr (Purpose == CardPurpose::Filter)
			label->SetFont(wxFont(7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		else if constexpr (Purpose == CardPurpose::Whitelist || Purpose == CardPurpose::Blacklist)
			label->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));

		sizer->Add(label, 1, wxEXPAND);
	}

	this->SetSizerAndFit(sizer);
}

template <CardPurpose P>
void ArmorPieceCard<P>::SetArmorPiece(std::string name)
{
	if constexpr (P != CardPurpose::Preview)
	{
		label->SetValue(name);
	}

	icon->SetIcon(name);
	this->name = std::move(name);
}

template<CardPurpose P>
auto ArmorPieceCard<P>::GetArmorPiece() const -> const std::string&
{
	return name;
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
void ArmorPieceCard<P>::OnLeftClick(wxMouseEvent&)
{
	const bool val = !icon->IsMarked();

	if constexpr (P == CardPurpose::Preview)
	{
		wxGetApp().GetParams().AddToWhitelist(this->name);
	}
	else if constexpr (P == CardPurpose::Filter)
	{
		wxGetApp().GetParams().RemoveFromWhitelist(name);
		wxGetApp().GetParams().RemoveFromBlacklist(name);
	}
	else if constexpr (P == CardPurpose::Whitelist)
	{
		if (val) wxGetApp().GetParams().AddToWhitelist(name);
		else wxGetApp().GetParams().RemoveFromWhitelist(name);

		icon->SetMark(val);
	}
	else if constexpr (P == CardPurpose::Blacklist)
	{
		if (val) wxGetApp().GetParams().AddToBlacklist(name);
		else wxGetApp().GetParams().RemoveFromBlacklist(name);

		icon->SetMark(val);
	}
}

template <CardPurpose P>
void ArmorPieceCard<P>::OnMiddleClick(wxMouseEvent&)
{
	if constexpr (P == CardPurpose::Preview)
	{
		wxGetApp().GetParams().AddToBlacklist(this->name);
	}
}

template <CardPurpose P>
void ArmorPieceCard<P>::OnRightClick(wxMouseEvent&)
{
	if constexpr (P == CardPurpose::Preview)
	{
		auto menu = wxMenu{name};

		menu.Append(static_cast<int>(MenuOption::AddToWhitelist), wxT("Add to whitelist (LMB)"));
		menu.Append(static_cast<int>(MenuOption::AddToBlacklist), wxT("Add to blacklist (MMB)"));

		menu.AppendSeparator();

		//menu.Append(static_cast<int>(MenuOption::Details), wxT("Details"));
		menu.Append(static_cast<int>(MenuOption::CopyNameToClipboard), wxT("Copy name to clipboard"));
		menu.Append(static_cast<int>(MenuOption::SearchOnGoogle), wxT("Search on Google"));

		menu.Bind(wxEVT_COMMAND_MENU_SELECTED,
			[&](wxCommandEvent& e)
			{
				switch (static_cast<MenuOption>(e.GetId()))
				{
				case MenuOption::AddToWhitelist:
					wxGetApp().GetParams().AddToWhitelist(this->name);
					break;

				case MenuOption::AddToBlacklist:
					wxGetApp().GetParams().AddToBlacklist(this->name);
					break;

				case MenuOption::CopyNameToClipboard:
					CopyToClipBoard(this->name);
					break;

				case MenuOption::SearchOnGoogle:
					wxLaunchDefaultBrowser(GetGoogleURL(this->name));
					break;

				default:
					assert(false && "Invalid MenuOption");
					break;
				}
			});

		PopupMenu(&menu);
	}
}

template class ArmorPieceCard<CardPurpose::Preview>;
template class ArmorPieceCard<CardPurpose::Filter>;
template class ArmorPieceCard<CardPurpose::Whitelist>;
template class ArmorPieceCard<CardPurpose::Blacklist>;

template class ArmorPieceIcon<CardPurpose::Preview>;
template class ArmorPieceIcon<CardPurpose::Filter>;
template class ArmorPieceIcon<CardPurpose::Whitelist>;
template class ArmorPieceIcon<CardPurpose::Blacklist>;
