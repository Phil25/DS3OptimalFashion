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

	ArmorSetSelectorPanel* selector;
	std::atomic<bool> scheduled{false};

	float maxWeight{}, delta{};
	optifa::ArmorPiece::Param toMaximize{};
	optifa::ArmorPiece::MinParams constraints{};
	optifa::ArmorPiece::NameList whitelist, blacklist;

public:
	ArmorUpdater(ArmorSetSelectorPanel* selector)
		: selector(selector)
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
		if (sets.empty()) return;

		auto& set = sets[0];
		selector->preview->SetHead(set.head.name);
		selector->preview->SetChest(set.chest.name);
		selector->preview->SetHands(set.hands.name);
		selector->preview->SetLegs(set.legs.name);
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
