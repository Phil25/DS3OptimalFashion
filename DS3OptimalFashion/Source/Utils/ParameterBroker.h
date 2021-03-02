#pragma once

#include <ArmorPiece.hpp>
#include <map>

class ParameterBroker final
{
	using Param = optifa::ArmorPiece::Param;
	using NameList = optifa::ArmorPiece::NameList;
	using Constraints = std::map<Param, float>;

	float currentLoad{}, fullLoad{}, maxWeight{}, percentage{}, delta{};
	Param toMaximize{};
	Constraints constraints{};
	NameList whitelist{}, blacklist{};

public:
	class UpdateSubscriber
	{
	protected:
		UpdateSubscriber();
		~UpdateSubscriber();

	private:
		virtual void OnParametersUpdate(const float maxWeight, const Param toMaximize, const float delta);
		virtual void OnConstraintsUpdate(const Constraints&);
		virtual void OnWhitelistUpdate(const NameList&);
		virtual void OnBlacklistUpdate(const NameList&);

		friend ParameterBroker;
	};

private:
	std::vector<UpdateSubscriber*> updateSubs{};

public:
	ParameterBroker() = default;

	void SetCurrentLoad(const float currentLoad) noexcept;
	void SetFullLoad(const float fullLoad) noexcept;
	void SetPercentage(const float percentage) noexcept;
	void SetParameter(const Param toMaximize) noexcept;
	void SetDelta(const float delta) noexcept;
	void SetConstraint(const Param param, const float value);
	void RemoveConstraint(const Param param);

	void AddToWhitelist(std::string name);
	void AddToBlacklist(std::string name);
	void RemoveFromWhitelist(const std::string& name);
	void RemoveFromBlacklist(const std::string& name);
	bool IsWhitelisted(const std::string& name) const;
	bool IsBlacklisted(const std::string& name) const;

	// using smart pointers on wxwidgets objects can be problematic, so no weak_ptrs
	void SubscribeToChanges(UpdateSubscriber*);
	void UnsubscribeFromChanges(UpdateSubscriber*);

private:
	void BroadcastParametersUpdate() const;
	void BroadcastConstraintsUpdate() const;
	void BroadcastWhitelistUpdate() const;
	void BroadcastBlacklistUpdate() const;
};