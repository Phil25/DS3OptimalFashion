#include "AppMain.h"

#include <sstream>

wxIMPLEMENT_APP(AppMain);

namespace
{
	constexpr auto Convert(const CardPurpose purpose) -> wxImageResizeQuality
	{
		return purpose == CardPurpose::Preview ? wxIMAGE_QUALITY_NORMAL : wxIMAGE_QUALITY_BILINEAR;
	}
}

auto AppMain::ImageCache::Selection(const int size, const CardPurpose purpose) -> const wxBitmap&
{
	return Get("Selection", size, purpose);
}

auto AppMain::ImageCache::Mark(const int size, const CardPurpose purpose) -> const wxBitmap&
{
	return Get("SelectionMarked", size, purpose);
}

auto AppMain::ImageCache::MarkDark(const int size, const CardPurpose purpose) -> const wxBitmap&
{
	return Get("SelectionMarkedDark", size, purpose);
}

auto AppMain::ImageCache::Get(const std::string& name, const int size, const CardPurpose purpose) -> const wxBitmap&
{

	auto& cache = cacheMap[name][static_cast<size_t>(purpose)];

	if (!cache.loaded)
	{
		std::ostringstream oss;
		oss << "./DS3OptimalFashion_Images/" << name << (purpose == CardPurpose::Preview ? ".png" : "_128.png");

		cache.image.LoadFile(oss.str(), wxBITMAP_TYPE_PNG);
		cache.loaded = true;
	}

	if (cache.bitmap.GetWidth() != size)
	{
		cache.bitmap = wxBitmap{cache.image.Scale(size, size, Convert(purpose))};
	}

	assert(cache.bitmap.GetHeight() == size && "Images should be 1:1");
	return cache.bitmap;
}

bool AppMain::OnInit()
{
	wxInitAllImageHandlers();
	imageCache = std::make_unique<ImageCache>();

	frameMain = new FrameMain();
	frameMain->Show();
	return true;
}

auto AppMain::GetImageCache() const -> const ImageCachePtr&
{
	return imageCache;
}

auto AppMain::GetArmorData() const -> const optifa::Database&
{
	return armorData;
}

void AppMain::AddToWhitelist(std::string name)
{
	RemoveFromBlacklist(name);
	whitelist.emplace(std::move(name));
	BroadcastWhitelistUpdate();
}

void AppMain::AddToBlacklist(std::string name)
{
	RemoveFromWhitelist(name);
	blacklist.emplace(std::move(name));
	BroadcastBlacklistUpdate();
}

void AppMain::RemoveFromWhitelist(const std::string& name)
{
	whitelist.erase(name);
	BroadcastWhitelistUpdate();
}

void AppMain::RemoveFromBlacklist(const std::string& name)
{
	blacklist.erase(name);
	BroadcastBlacklistUpdate();
}

bool AppMain::IsWhitelisted(const std::string& name) const
{
	return whitelist.count(name);
}

bool AppMain::IsBlacklisted(const std::string& name) const
{
	return blacklist.count(name);
}

void AppMain::SubscribeToListChanges(ListUpdateSubscriber* sub)
{
	listUpdateSubs.push_back(sub);
}

void AppMain::UnsubscribeFromListChanges(ListUpdateSubscriber* sub)
{
	listUpdateSubs.erase(std::remove(listUpdateSubs.begin(), listUpdateSubs.end(), sub), listUpdateSubs.end());
}

void AppMain::BroadcastWhitelistUpdate() const
{
	for (auto* sub : listUpdateSubs)
		sub->OnUpdateWhitelist(whitelist);
}

void AppMain::BroadcastBlacklistUpdate() const
{
	for (auto* sub : listUpdateSubs)
		sub->OnUpdateBlacklist(blacklist);
}
