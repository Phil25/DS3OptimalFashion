#include "ArmorSetSelectorPanel.h"

#include <ArmorFinder.h>
#include <AppMain.h>
#include <Utils/ParameterBroker.h>
#include <thread>
#include <mutex>
#include <atomic>

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

ArmorSetSelectorPanel::ArmorSetSelectorPanel(wxWindow* parent, wxSize size, ArmorSetPreviewPanel* preview, CurrentParameters* paramsDisplay)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, std::move(size))
	, armorUpdater(std::make_unique<ArmorUpdater>(this))
	, preview(preview)
	, paramsDisplay(paramsDisplay)
{
	armorUpdater->Start();
}

void ArmorSetSelectorPanel::SetSets(optifa::ArmorSet::Vector sets)
{
	this->sets = std::move(sets);
	SetSelection(this->sets.empty() ? -1 : 0);
}

void ArmorSetSelectorPanel::SetSelection(const int setIndex)
{
	if (setIndex >= 0 && setIndex < sets.size())
	{
		preview->SetHead(sets[setIndex].head.name);
		preview->SetChest(sets[setIndex].chest.name);
		preview->SetHands(sets[setIndex].hands.name);
		preview->SetLegs(sets[setIndex].legs.name);

		UpdateParamsDisplay(setIndex);
	}
	else
	{
		preview->SetHead("Naked Head");
		preview->SetChest("Naked Chest");
		preview->SetHands("Naked Hands");
		preview->SetLegs("Naked Legs");
	}
}

void ArmorSetSelectorPanel::UpdateParamsDisplay(const int setIndex)
{
	using P = optifa::ArmorPiece::Param;

	auto& set = sets[setIndex];

	paramsDisplay->SetArmorSetParameter(P::Physical, set.Get<P::Physical>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Thrust, set.Get<P::Thrust>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Strike, set.Get<P::Strike>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Slash, set.Get<P::Slash>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Magic, set.Get<P::Magic>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Fire, set.Get<P::Fire>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Lightning, set.Get<P::Lightning>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Dark, set.Get<P::Dark>(), 3);
	paramsDisplay->SetArmorSetParameter(P::Bleed, set.Get<P::Bleed>(), 0);
	paramsDisplay->SetArmorSetParameter(P::Poison, set.Get<P::Poison>(), 0);
	paramsDisplay->SetArmorSetParameter(P::Frost, set.Get<P::Frost>(), 0);
	paramsDisplay->SetArmorSetParameter(P::Curse, set.Get<P::Curse>(), 0);

	auto poise = set.Get<P::Poise>();
	auto weight = set.Get<P::Weight>();

	paramsDisplay->SetArmorSetParameter(P::Poise, poise, 2);
	paramsDisplay->SetArmorSetParameter(P::Weight, weight, 1);
	paramsDisplay->SetArmorSetRatio(poise / weight, 2);
}
