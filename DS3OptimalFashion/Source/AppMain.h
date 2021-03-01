#pragma once

#include <Frames/FrameMain.h>
#include <Utils/CardPurpose.hpp>
#include <Database.h>
#include <wx/wx.h>
#include <map>
#include <array>

class ListUpdateSubscriber;

class AppMain final : public wxApp
{
	FrameMain* frameMain{nullptr};

	class ImageCache
	{
		struct ImageData
		{
			wxImage image;
			std::array<wxBitmap, static_cast<size_t>(CardPurpose::Size)> bitmaps;
		};

		std::map<std::string, ImageData> cache;

	public:
		ImageCache() = default;

		auto Selection(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto Mark(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto MarkDark(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto Get(const std::string& name, const int size, const CardPurpose purpose) -> const wxBitmap&;
	};

	using ImageCachePtr = std::unique_ptr<ImageCache>;
	ImageCachePtr imageCache;

	const optifa::Database armorData;
	optifa::ArmorPiece::NameList whitelist, blacklist;
	std::vector<ListUpdateSubscriber*> listUpdateSubs;

public:
	AppMain() = default;

	bool OnInit() override;

	auto GetImageCache() const -> const ImageCachePtr&;
	auto GetArmorData() const -> const optifa::Database&;

	void AddToWhitelist(std::string name);
	void AddToBlacklist(std::string name);

	void RemoveFromWhitelist(const std::string& name);
	void RemoveFromBlacklist(const std::string& name);

	bool IsWhitelisted(const std::string& name) const;
	bool IsBlacklisted(const std::string& name) const;

	void SubscribeToListChanges(ListUpdateSubscriber*);
	void UnsubscribeFromListChanges(ListUpdateSubscriber*);

private:
	void BroadcastWhitelistUpdate() const;
	void BroadcastBlacklistUpdate() const;
};

DECLARE_APP(AppMain)

class ListUpdateSubscriber
{
protected:
	ListUpdateSubscriber()
	{
		// using smart pointers on wxwidgets objects can be problematic, so no weak_ptrs
		wxGetApp().SubscribeToListChanges(this);
	}

	~ListUpdateSubscriber()
	{
		wxGetApp().UnsubscribeFromListChanges(this);
	}

private:
	virtual void OnUpdateWhitelist(const optifa::ArmorPiece::NameList&) = 0;
	virtual void OnUpdateBlacklist(const optifa::ArmorPiece::NameList&) = 0;

	friend AppMain;
};