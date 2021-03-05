#include "ArmorSetSelectorPanel.h"

#include <ArmorFinder.h>
#include <AppMain.h>
#include <Utils/ParameterBroker.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <sstream>

namespace
{
	auto Convert(std::map<optifa::ArmorPiece::Param, float> constraints)
	{
		optifa::ArmorPiece::MinParams params;

		for (auto& pair : constraints)
			params.emplace_back(std::move(pair));

		return params;
	}
}

class ArmorSetSelectorPanel::ArmorUpdater final
	: ParameterBroker::UpdateSubscriber
{
	mutable std::mutex m;

	ArmorSetSelectorPanel* selector{nullptr};
	std::atomic<bool> scheduled{false};

	float maxWeight{}, delta{};
	optifa::ArmorPiece::Param toMaximize{};
	optifa::ArmorPiece::MinParams constraints{};
	optifa::ArmorPiece::NameList whitelist{}, blacklist{};

public:
	ArmorUpdater(ArmorSetSelectorPanel* selector) : selector(selector)
	{
	}

	void Start()
	{
		std::thread t{&ArmorUpdater::ThreadLoop, this, this};
		t.detach();
	}

	void OnParametersUpdate(const float maxWeight, const optifa::ArmorPiece::Param toMaximize, const float delta) override
	{
		std::scoped_lock<std::mutex> l(m);

		this->maxWeight = maxWeight;
		this->toMaximize = toMaximize;
		this->delta = delta;
		this->scheduled = true;
	}

	void OnConstraintsUpdate(const std::map<optifa::ArmorPiece::Param, float>& constraints) override
	{
		std::scoped_lock<std::mutex> l(m);

		this->constraints = Convert(constraints);
		this->scheduled = true;
	}

	void OnWhitelistUpdate(const optifa::ArmorPiece::NameList& whitelist) override
	{
		std::scoped_lock<std::mutex> l(m);

		this->whitelist = whitelist;
		this->scheduled = true;
	}

	void OnBlacklistUpdate(const optifa::ArmorPiece::NameList& blacklist) override
	{
		std::scoped_lock<std::mutex> l(m);

		this->blacklist = blacklist;
		this->scheduled = true;
	}

private:
	void ThreadLoop(ArmorUpdater* p)
	{
		using namespace std::chrono_literals;

		while (true)
		{
			if (p->scheduled)
			{
				p->UpdateArmor();
				p->scheduled = false;
			}

			std::this_thread::sleep_for(500ms);
		}
	}

	void UpdateArmor()
	{
		auto sets = optifa::FindOptimal(wxGetApp().GetArmorData(), maxWeight, toMaximize, delta, constraints, whitelist, blacklist);
		selector->SetSets(std::move(sets));
	}
};

ArmorSetSelectorPanel::ArmorSetSelectorPanel(wxWindow* parent, wxSize size, ArmorSetPreviewPanel* preview, ParametersDisplayPanel* paramsDisplay)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, std::move(size))
	, armorUpdater(std::make_unique<ArmorUpdater>(this))
	, preview(preview)
	, paramsDisplay(paramsDisplay)
	, status(new wxStaticText(this, wxID_ANY, wxEmptyString))
	, setChoice(new wxChoice(this, wxID_ANY))
{
	armorUpdater->Start();

	status->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	setChoice->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT));
	setChoice->Bind(wxEVT_CHOICE, &ArmorSetSelectorPanel::SetSelection, this);

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(status, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);
	sizer->Add(setChoice, 1, wxEXPAND | wxALL, 10);

	this->SetSizer(sizer);

	SetSelection(-1);
}

void ArmorSetSelectorPanel::SetSets(optifa::ArmorSet::Vector sets)
{
	this->sets = std::move(sets);

	int i = 0;
	setChoice->Clear();
	for (const auto& set : this->sets)
	{
		std::ostringstream oss;
		oss << (++i) << "] " << set->head.name << " --- " << set->chest.name << " --- " << set->hands.name << " --- " << set->legs.name;
		setChoice->Append(oss.str());
	}

	SetSelection(this->sets.empty() ? -1 : 0);
}

void ArmorSetSelectorPanel::SetSelection(wxCommandEvent& e)
{
	const auto index = static_cast<wxChoice*>(e.GetEventObject())->GetSelection();
	SetSelection(index);
}

void ArmorSetSelectorPanel::SetSelection(const int index)
{
	if (index >= 0 && index < sets.size())
	{
		std::ostringstream oss;
		oss << "Found (" << sets.size() << "):";
		status->SetLabel(oss.str());
		GetSizer()->Layout();

		setChoice->SetSelection(index);

		preview->SetHead(sets[index]->head.name);
		preview->SetChest(sets[index]->chest.name);
		preview->SetHands(sets[index]->hands.name);
		preview->SetLegs(sets[index]->legs.name);

		UpdateParamsDisplay(index);
	}
	else
	{
		status->SetLabel(wxT("No armor sets found."));
		GetSizer()->Layout();

		preview->SetHead("Naked Head");
		preview->SetChest("Naked Chest");
		preview->SetHands("Naked Hands");
		preview->SetLegs("Naked Legs");
	}
}

void ArmorSetSelectorPanel::UpdateParamsDisplay(const int index)
{
	using P = optifa::ArmorPiece::Param;
	const auto& set = *sets[index];

	paramsDisplay->SetArmorSetParameter(P::Physical, set.Get(P::Physical), 3);
	paramsDisplay->SetArmorSetParameter(P::Thrust, set.Get(P::Thrust), 3);
	paramsDisplay->SetArmorSetParameter(P::Strike, set.Get(P::Strike), 3);
	paramsDisplay->SetArmorSetParameter(P::Slash, set.Get(P::Slash), 3);
	paramsDisplay->SetArmorSetParameter(P::Magic, set.Get(P::Magic), 3);
	paramsDisplay->SetArmorSetParameter(P::Fire, set.Get(P::Fire), 3);
	paramsDisplay->SetArmorSetParameter(P::Lightning, set.Get(P::Lightning), 3);
	paramsDisplay->SetArmorSetParameter(P::Dark, set.Get(P::Dark), 3);
	paramsDisplay->SetArmorSetParameter(P::Bleed, set.Get(P::Bleed), 0);
	paramsDisplay->SetArmorSetParameter(P::Poison, set.Get(P::Poison), 0);
	paramsDisplay->SetArmorSetParameter(P::Frost, set.Get(P::Frost), 0);
	paramsDisplay->SetArmorSetParameter(P::Curse, set.Get(P::Curse), 0);

	auto poise = set.Get(P::Poise);
	auto weight = set.Get(P::Weight);

	paramsDisplay->SetArmorSetParameter(P::Poise, poise, 2);
	paramsDisplay->SetArmorSetParameter(P::Weight, weight, 1);
	paramsDisplay->SetArmorSetRatio(poise / weight, 2);
}
