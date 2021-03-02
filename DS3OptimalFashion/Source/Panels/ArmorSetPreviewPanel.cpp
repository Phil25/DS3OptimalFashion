#include "ArmorSetPreviewPanel.h"

#include <AppMain.h>
#include <ArmorFinder.h>
#include <Utils/ParameterBroker.h>

// TODO: move this to ArmorSelector panel, it will update Preview and CurrentParams itself
class ArmorSetPreviewPanel::ArmorUpdater final
	: ParameterBroker::UpdateSubscriber
{
	ArmorSetPreviewPanel* preview;

	// TODO: move this cache to a separate thread
	float maxWeight{}, delta{};
	optifa::ArmorPiece::Param toMaximize{};
	std::map<optifa::ArmorPiece::Param, float> constraints;
	optifa::ArmorPiece::NameList whitelist, blacklist;

public:
	ArmorUpdater(ArmorSetPreviewPanel* preview)
		: preview(preview)
	{
	}

	void OnParametersUpdate(const float maxWeight, const optifa::ArmorPiece::Param toMaximize, const float delta) override
	{
		this->maxWeight = maxWeight;
		this->toMaximize = toMaximize;
		this->delta = delta;
		UpdateArmor();
	}

	void OnConstraintsUpdate(const std::map<optifa::ArmorPiece::Param, float>& constraints) override
	{
		this->constraints = constraints;
		UpdateArmor();
	}

	void OnWhitelistUpdate(const optifa::ArmorPiece::NameList& whitelist) override
	{
		this->whitelist = whitelist;
		UpdateArmor();
	}

	void OnBlacklistUpdate(const optifa::ArmorPiece::NameList& blacklist) override
	{
		this->blacklist = blacklist;
		UpdateArmor();
	}

private:
	void UpdateArmor()
	{
		optifa::ArmorPiece::MinParams params;
		for (const auto& [constraint, value] : constraints)
			params.emplace_back(constraint, value);

		auto sets = optifa::FindOptimal(wxGetApp().GetArmorData(), maxWeight, toMaximize, delta, params, whitelist, blacklist);
		if (sets.empty()) return;

		auto& set = sets[0];
		preview->head->SetArmorPiece(set.head.name);
		preview->chest->SetArmorPiece(set.chest.name);
		preview->hands->SetArmorPiece(set.hands.name);
		preview->legs->SetArmorPiece(set.legs.name);
	}
};

ArmorSetPreviewPanel::ArmorSetPreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, armorUpdater(std::make_unique<ArmorUpdater>(this))
	, head(new ArmorPieceCard<CardPurpose::Preview>(this))
	, chest(new ArmorPieceCard<CardPurpose::Preview>(this))
	, hands(new ArmorPieceCard<CardPurpose::Preview>(this))
	, legs(new ArmorPieceCard<CardPurpose::Preview>(this))
{
	head->SetArmorPiece("Naked Head");
	chest->SetArmorPiece("Naked Chest");
	hands->SetArmorPiece("Naked Hands");
	legs->SetArmorPiece("Naked Legs");

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(head, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(chest, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(hands, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);
	sizer->Add(legs, 1, wxEXPAND | wxBOTTOM | wxTOP, 10);

	this->SetSizerAndFit(sizer);
}
