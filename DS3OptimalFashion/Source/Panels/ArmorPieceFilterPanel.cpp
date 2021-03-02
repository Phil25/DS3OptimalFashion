#include "ArmorPieceFilterPanel.h"

#include <Utils/ArmorPieceCard.h>
#include <Frames/DialogArmorBrowser.h>
#include <AppMain.h>

namespace
{
	template <bool IsWhitelist>
	class FilteredArmorPieces final
		: public wxScrolledWindow
		, public ParameterBroker::UpdateSubscriber
	{
		wxGridSizer* grid;

	public:
		FilteredArmorPieces(wxWindow* parent)
			: wxScrolledWindow(parent)
			, grid(new wxGridSizer(3))
		{
			this->SetScrollRate(5, 5);
			this->SetSizerAndFit(grid);
		}

		void UpdateArmorPieces(const optifa::ArmorPiece::NameList& list)
		{
			grid->Clear(true);

			for (const auto& name : list)
			{
				auto* p = new ArmorPieceCard<CardPurpose::Filter>(this);

				p->SetArmorPiece(name);
				p->SetMinSize(wxSize(130, 130));

				grid->Add(p);
			}

			grid->Layout();
			GetParent()->GetSizer()->Layout();
		}

	private:
		void OnWhitelistUpdate(const optifa::ArmorPiece::NameList& whitelist) override
		{
			if constexpr (IsWhitelist)
				UpdateArmorPieces(whitelist);
		}

		void OnBlacklistUpdate(const optifa::ArmorPiece::NameList& blacklist) override
		{
			if constexpr (!IsWhitelist)
				UpdateArmorPieces(blacklist);
		}
	};
}

ArmorPieceFilterPanel::ArmorPieceFilterPanel(wxWindow* parent, const bool isWhitelist)
	: TitlePanel(parent, wxDefaultSize, isWhitelist ? "Whitelist" : "Blacklist")
	, isWhitelist(isWhitelist)
{
	auto* sizer = new wxBoxSizer(wxVERTICAL);

	auto* adder = new wxButton(GetContent(), wxID_ANY, wxT("Add Armor Piece"));
	adder->Bind(wxEVT_BUTTON, &ArmorPieceFilterPanel::ShowModal, this);
	sizer->Add(adder, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);

	if (isWhitelist)
	{
		auto* grid = new FilteredArmorPieces<true>(GetContent());
		sizer->Add(grid, 1, wxEXPAND);
	}
	else
	{
		auto* grid = new FilteredArmorPieces<false>(GetContent());
		sizer->Add(grid, 1, wxEXPAND);
	}

	GetContent()->SetSizerAndFit(sizer);
}

void ArmorPieceFilterPanel::ShowModal(wxCommandEvent&)
{
	DialogArmorBrowser{this, isWhitelist}.ShowModal();
}
