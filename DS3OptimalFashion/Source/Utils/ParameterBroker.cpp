#include "ParameterBroker.h"

#include <AppMain.h>
#include <cmath>

namespace
{
	inline float RoundTo1AfterComma(const float val) noexcept
	{
		return std::round(val * 10) / 10;
	}

	inline float CalculateMaxWeight(const float fullLoad, const float percentage, const float currentLoad) noexcept
	{
		return RoundTo1AfterComma(fullLoad * percentage / 100) - currentLoad;
	}
}

ParameterBroker::UpdateSubscriber::UpdateSubscriber()
{
	wxGetApp().GetParams().SubscribeToChanges(this);
}

ParameterBroker::UpdateSubscriber::~UpdateSubscriber()
{
	wxGetApp().GetParams().UnsubscribeFromChanges(this);
}

void ParameterBroker::UpdateSubscriber::OnParametersUpdate(const float, const Param, const float) {}
void ParameterBroker::UpdateSubscriber::OnConstraintsUpdate(const Constraints&) {}
void ParameterBroker::UpdateSubscriber::OnWhitelistUpdate(const NameList&) {}
void ParameterBroker::UpdateSubscriber::OnBlacklistUpdate(const NameList&) {}

void ParameterBroker::SetCurrentLoad(const float currentLoad) noexcept
{
	this->currentLoad = currentLoad;
	maxWeight = CalculateMaxWeight(fullLoad, percentage, currentLoad);
	BroadcastParametersUpdate();
}

void ParameterBroker::SetFullLoad(const float fullLoad) noexcept
{
	this->fullLoad = fullLoad;
	maxWeight = CalculateMaxWeight(fullLoad, percentage, currentLoad);
	BroadcastParametersUpdate();
}

void ParameterBroker::SetPercentage(const float percentage) noexcept
{
	this->percentage = percentage;
	maxWeight = CalculateMaxWeight(fullLoad, percentage, currentLoad);
	BroadcastParametersUpdate();
}

void ParameterBroker::SetParameter(const Param toMaximize) noexcept
{
	this->toMaximize = toMaximize;
	BroadcastParametersUpdate();
}

void ParameterBroker::SetDelta(const float delta) noexcept
{
	this->delta = delta;
	BroadcastParametersUpdate();
}

void ParameterBroker::SetConstraint(const Param param, const float value)
{
	if (value > 0.F)
	{
		constraints[param] = value;
		BroadcastConstraintsUpdate();
	}
	else RemoveConstraint(param);
}

void ParameterBroker::RemoveConstraint(const Param param)
{
	constraints.erase(param);
	BroadcastConstraintsUpdate();
}

void ParameterBroker::AddToWhitelist(std::string name)
{
	RemoveFromBlacklist(name);
	whitelist.emplace(std::move(name));
	BroadcastWhitelistUpdate();
}

void ParameterBroker::AddToBlacklist(std::string name)
{
	RemoveFromWhitelist(name);
	blacklist.emplace(std::move(name));
	BroadcastBlacklistUpdate();
}

void ParameterBroker::RemoveFromWhitelist(const std::string& name)
{
	whitelist.erase(name);
	BroadcastWhitelistUpdate();
}

void ParameterBroker::RemoveFromBlacklist(const std::string& name)
{
	blacklist.erase(name);
	BroadcastBlacklistUpdate();
}

bool ParameterBroker::IsWhitelisted(const std::string& name) const
{
	return whitelist.count(name);
}

bool ParameterBroker::IsBlacklisted(const std::string& name) const
{
	return blacklist.count(name);
}

void ParameterBroker::SubscribeToChanges(UpdateSubscriber* sub)
{
	updateSubs.push_back(sub);
}

void ParameterBroker::UnsubscribeFromChanges(UpdateSubscriber* sub)
{
	updateSubs.erase(std::remove(updateSubs.begin(), updateSubs.end(), sub), updateSubs.end());
}

void ParameterBroker::BroadcastParametersUpdate() const
{
	for (auto* sub : updateSubs)
		sub->OnParametersUpdate(maxWeight, toMaximize, delta);
}

void ParameterBroker::BroadcastConstraintsUpdate() const
{
	for (auto* sub : updateSubs)
		sub->OnConstraintsUpdate(constraints);
}

void ParameterBroker::BroadcastWhitelistUpdate() const
{
	for (auto* sub : updateSubs)
		sub->OnWhitelistUpdate(whitelist);
}

void ParameterBroker::BroadcastBlacklistUpdate() const
{
	for (auto* sub : updateSubs)
		sub->OnBlacklistUpdate(blacklist);
}
