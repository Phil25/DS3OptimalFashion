#include "DialogArmorBrowser.h"

#include <Utils/ArmorPieceCard.h>
#include <AppMain.h>
#include <sstream>

namespace
{
	constexpr int ITEM_LIMIT = 20;

	inline bool Contains(const std::string& str, const std::string& sub)
	{
		return str.end() != std::search(
			str.begin(), str.end(), sub.begin(), sub.end(),
			[](char c1, char c2) { return std::toupper(c1) == c2; }
		);
	}

	inline void MatchName(const std::string& filter, const optifa::ArmorPiece::Vector& in, std::vector<std::string>& out)
	{
		for (const auto& piece : in)
			if (Contains(piece.name, filter))
				out.push_back(piece.name);
	}

	class ArmorFilters final : public wxWindow
	{
		wxTextCtrl* filterBox{nullptr};

		struct {
			wxRadioButton* all{nullptr};
			wxRadioButton* head{nullptr};
			wxRadioButton* chest{nullptr};
			wxRadioButton* hands{nullptr};
			wxRadioButton* legs{nullptr};
		} radio;

	public:
		ArmorFilters(DialogArmorBrowser* parent)
			: wxWindow(parent, wxID_ANY)
			, filterBox(new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER))
			, radio{
				new wxRadioButton(this, wxID_ANY, wxT("All"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP),
				new wxRadioButton(this, wxID_ANY, wxT("Head"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Chest"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Hands"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Legs"), wxDefaultPosition, wxDefaultSize)
			}
		{
			filterBox->SetHint(wxT("Filter..."));
			filterBox->SetFocus();
			filterBox->Bind(wxEVT_TEXT, [&](wxCommandEvent&) { this->UpdateFilter(); });

			radio.all->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->UpdateFilter(); });
			radio.head->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->UpdateFilter(); });
			radio.chest->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->UpdateFilter(); });
			radio.hands->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->UpdateFilter(); });
			radio.legs->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->UpdateFilter(); });

			radio.all->SetValue(true);

			auto* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(filterBox, 6, wxALIGN_CENTER_VERTICAL);
			sizer->AddStretchSpacer(1);
			sizer->Add(radio.all, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.head, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.chest, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.hands, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.legs, 1, wxALIGN_CENTER_VERTICAL);

			this->SetSizerAndFit(sizer);
		}

	private:
		void UpdateFilter()
		{
			using T = optifa::ArmorPiece::Type;

			auto flags = radio.all->GetValue() ? 0b1111 : 0b0000;
			flags |= radio.head->GetValue() << static_cast<int>(T::Head);
			flags |= radio.chest->GetValue() << static_cast<int>(T::Chest);
			flags |= radio.hands->GetValue() << static_cast<int>(T::Hands);
			flags |= radio.legs->GetValue() << static_cast<int>(T::Legs);

			auto filter = filterBox->GetValue().ToStdString();
			static_cast<DialogArmorBrowser*>(GetParent())->UpdateFilter(std::move(filter), flags);
		}
	};
}

class DialogArmorBrowser::FilteredArmorPieces final : public wxPanel
{
	const bool isWhitelist;
	wxGridSizer* grid{nullptr};

public:
	FilteredArmorPieces(wxWindow* parent, const bool isWhitelist=true)
		: wxPanel(parent)
		, isWhitelist(isWhitelist)
		, grid(new wxGridSizer(5))
	{
		this->SetSizerAndFit(grid);
	}

	void UpdateArmorPieces(const std::vector<std::string>& pieces)
	{
		grid->Clear(true);

		int count = 0;
		for (const auto& piece : pieces)
		{
			if (++count > ITEM_LIMIT) break;

			if (isWhitelist)
			{
				auto* p = new ArmorPieceCard<CardPurpose::Whitelist>(this);
				p->SetArmorPiece(piece);
				p->SetMinSize(wxSize(130, 130));
				grid->Add(p, 1);
			}
			else
			{
				auto* p = new ArmorPieceCard<CardPurpose::Blacklist>(this);
				p->SetArmorPiece(piece);
				p->SetMinSize(wxSize(130, 130));
				grid->Add(p, 1);
			}
		}

		grid->Layout();

		// prevent stretching out rows when the item count is small
		if (grid->GetEffectiveRowsCount() < 4)
			grid->SetRows(4);
	}
};

DialogArmorBrowser::DialogArmorBrowser(wxWindow* parent, const bool isWhitelist)
	: wxDialog(parent, wxID_ANY, "Armor Piece Browser")
	, browser(new FilteredArmorPieces(this, isWhitelist))
	, status(new wxStaticText(this, wxID_ANY, wxT("Filter needs to be at least 2 characters long."), wxDefaultPosition, wxDefaultSize, wxTE_CENTER))
{
	browser->SetMinSize(wxSize(800, 550));
	status->SetBackgroundColour(wxColor(180, 180, 220));

	auto text = new wxStaticText(this, wxID_ANY, isWhitelist
		? wxT("Select armor pieces for the whitelist")
		: wxT("Select armor pieces for the blacklist"));

	auto* filters = new ArmorFilters(this);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(text, 0, wxEXPAND | wxALL, 5);
	sizer->Add(filters, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
	sizer->Add(browser, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sizer->Add(status, 0, wxEXPAND | wxALL, 5);
	sizer->Add(CreateButtonSizer(wxCLOSE), 0, wxALIGN_RIGHT | wxALL, 5);

	SetSizerAndFit(sizer);
}

void DialogArmorBrowser::UpdateFilter(std::string filter, int flags)
{
	using T = optifa::ArmorPiece::Type;

	if (filter.length() < 2)
	{
		browser->UpdateArmorPieces({});

		status->SetLabelText("Filter needs to be at least 2 characters long.");
		status->Show();

		GetSizer()->Layout();

		return;
	}

	std::transform(filter.begin(), filter.end(), filter.begin(), std::toupper);

	std::vector<std::string> vec;

	for (const auto type : {T::Head, T::Chest, T::Hands, T::Legs})
		if (flags & (1 << static_cast<int>(type)))
			MatchName(filter, wxGetApp().GetArmorData().GetType(type), vec);

	browser->UpdateArmorPieces(std::move(vec));

	if (vec.size() > ITEM_LIMIT)
	{
		std::ostringstream oss;
		oss << "Showing " << ITEM_LIMIT << " elements out of " << vec.size() << ". ";
		oss << "Please narrow down the filter for the rest.";

		status->SetLabelText(oss.str());
		status->Show();
	}
	else status->Hide();

	GetSizer()->Layout();
}
