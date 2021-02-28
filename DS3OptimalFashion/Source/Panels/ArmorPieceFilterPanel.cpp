#include "ArmorPieceFilterPanel.h"

#include <Utils/ArmorPieceCard.h>
#include <Frames/DialogArmorBrowser.h>

namespace
{
	class FilteredArmorPieces final : public wxScrolledWindow
	{
	public:
		FilteredArmorPieces(wxWindow* parent) : wxScrolledWindow(parent)
		{
			auto* grid = new wxGridSizer(3);

			/*
			for (int i = 0; i < 10; ++i)
			{
				auto* p = new ArmorPieceCard<CardPurpose::Filter>(this);
				p->SetPiece("Iron Dragonslayer Gauntlets");
				p->SetMinSize(wxSize(130, 130));
				grid->Add(p, 1, wxEXPAND);
			}
			*/

			this->SetScrollRate(5, 5);
			this->SetSizerAndFit(grid);
		}
	};
}

ArmorPieceFilterPanel::ArmorPieceFilterPanel(wxWindow* parent, const bool isWhitelist)
	: TitlePanel(parent, wxDefaultSize, isWhitelist ? "Whitelist" : "Blacklist")
	, isWhitelist(isWhitelist)
{
	auto* sizer = new wxBoxSizer(wxVERTICAL);

	auto* adder = new wxButton(GetContent(), wxID_ANY, wxT("Add Armor Piece"));
	adder->Bind(wxEVT_BUTTON,
		[&](wxCommandEvent&)
		{ 
			auto dialog = DialogArmorBrowser(this, this->isWhitelist);
			dialog.ShowModal();
		});

	auto* grid = new FilteredArmorPieces(GetContent());

	sizer->Add(adder, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
	sizer->Add(grid, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
