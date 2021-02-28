#include "DialogArmorBrowser.h"

#include <ArmorPieceCard.h>
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

			this->SetScrollRate(15, 15);
			this->SetSizerAndFit(grid);
		}
	};
}

DialogArmorBrowser::DialogArmorBrowser(wxWindow* parent, const bool isWhitelist)
	: wxDialog(parent, wxID_ANY, "Armor Piece Browser")
{
	auto text = new wxStaticText(this, wxID_ANY, isWhitelist
		? wxT("Select armor pieces for the whitelist")
		: wxT("Select armor pieces for the blacklist"));

	auto search = new wxSearchCtrl(this, wxID_ANY);

	auto* browser = new FilteredArmorPieces(this);
	browser->SetMinSize(wxSize(800, 650));

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(text, 0, wxEXPAND | wxALL, 5);
	sizer->Add(search, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
	sizer->Add(browser, 5, wxEXPAND | wxLEFT | wxRIGHT, 5);
	sizer->Add(CreateButtonSizer(wxCLOSE), 0, wxALIGN_RIGHT | wxALL, 5);

	SetSizerAndFit(sizer);
}
