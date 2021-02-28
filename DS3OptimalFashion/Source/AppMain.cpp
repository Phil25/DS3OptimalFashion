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

auto AppMain::ImageCache::Get(const std::string& name, const int size, const CardPurpose purpose) -> const wxBitmap&
{
	auto it = cache.find(name);
	if (it == cache.end())
	{
		std::ostringstream oss;
		oss << "./DS3OptimalFashion_Images/" << name << (purpose == CardPurpose::Preview ? ".png" : "_128.png");

		auto data = ImageCache::ImageData{wxImage{oss.str(), wxBITMAP_TYPE_PNG}, {}};
		const auto& [newIt, success] = cache.emplace(name, std::move(data));

		assert(newIt != cache.end() && success && "Adding image failed");
		it = newIt;
	}

	auto& bitmap = it->second.bitmaps[static_cast<size_t>(purpose)];

	if (bitmap.GetWidth() != size)
	{
		bitmap = wxBitmap{it->second.image.Scale(size, size, Convert(purpose))};
	}

	assert(bitmap.GetHeight() == size && "Images should be 1:1");
	return bitmap;
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
