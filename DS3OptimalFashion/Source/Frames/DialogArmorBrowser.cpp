#include "DialogArmorBrowser.h"

#include <Utils/ArmorPieceCard.h>
#include <AppMain.h>
#include <wx/srchctrl.h>

namespace
{
	// TODO: reuse from ArmorPieceFilterPanel
	class FilteredArmorPieces final : public wxScrolledWindow
	{
	public:
		FilteredArmorPieces(wxWindow* parent) : wxScrolledWindow(parent)
		{
			auto* grid = new wxGridSizer(5);

			for (const auto& piece : wxGetApp().GetArmorData().GetType(optifa::ArmorPiece::Type::Head))
			{
				auto* p = new ArmorPieceCard<CardPurpose::Browser>(this);
				p->SetPiece(piece.name);
				p->SetMinSize(wxSize(130, 130));
				grid->Add(p, 1);
			}

			this->SetScrollRate(15, 15);
			this->SetSizer(grid);
		}
	};

	class ArmorFilters final : public wxWindow
	{
		wxTextCtrl* filterBox{nullptr};

		struct {
			wxRadioButton* filter{nullptr};
			wxRadioButton* head{nullptr};
			wxRadioButton* chest{nullptr};
			wxRadioButton* hands{nullptr};
			wxRadioButton* legs{nullptr};
		} radio;

	public:
		ArmorFilters(DialogArmorBrowser* parent)
			: wxWindow(parent, wxID_ANY)
			, filterBox(new wxTextCtrl(this, wxID_ANY))
			, radio{
				new wxRadioButton(this, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP),
				new wxRadioButton(this, wxID_ANY, wxT("Head"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Chest"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Hands"), wxDefaultPosition, wxDefaultSize),
				new wxRadioButton(this, wxID_ANY, wxT("Legs"), wxDefaultPosition, wxDefaultSize)
			}
		{
			filterBox->SetHint(wxT("Filter..."));
			filterBox->Bind(wxEVT_SET_FOCUS, [&](wxFocusEvent&) { this->SetNameFilter(); });

			radio.filter->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->SetNameFilter(); });
			radio.head->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->SetArmorFilter(optifa::ArmorPiece::Type::Head); });
			radio.chest->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->SetArmorFilter(optifa::ArmorPiece::Type::Chest); });
			radio.hands->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->SetArmorFilter(optifa::ArmorPiece::Type::Hands); });
			radio.legs->Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent&) { this->SetArmorFilter(optifa::ArmorPiece::Type::Legs); });

			auto* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(filterBox, 6, wxALIGN_CENTER_VERTICAL);
			sizer->AddStretchSpacer(1);
			sizer->Add(radio.filter, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.head, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.chest, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.hands, 1, wxALIGN_CENTER_VERTICAL);
			sizer->Add(radio.legs, 1, wxALIGN_CENTER_VERTICAL);

			this->SetSizerAndFit(sizer);
		}

	private:
		void SetArmorFilter(const optifa::ArmorPiece::Type type)
		{
			filterBox->SetBackgroundColour(wxColor(172, 172, 172));
			filterBox->Refresh();
		}

		void SetNameFilter()
		{
			filterBox->SetBackgroundColour(wxNullColour);
			filterBox->Refresh();
			radio.filter->SetValue(true);
		}
	};
}

DialogArmorBrowser::DialogArmorBrowser(wxWindow* parent, const bool isWhitelist)
	: wxDialog(parent, wxID_ANY, "Armor Piece Browser")
{
	auto text = new wxStaticText(this, wxID_ANY, isWhitelist
		? wxT("Select armor pieces for the whitelist")
		: wxT("Select armor pieces for the blacklist"));

	auto* filters = new ArmorFilters(this);

	auto* browser = new FilteredArmorPieces(this);
	browser->SetMinSize(wxSize(800, 650));

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(text, 0, wxEXPAND | wxALL, 5);
	sizer->Add(filters, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
	sizer->Add(browser, 5, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sizer->Add(CreateButtonSizer(wxCLOSE), 0, wxALIGN_RIGHT | wxALL, 5);

	SetSizerAndFit(sizer);
}
