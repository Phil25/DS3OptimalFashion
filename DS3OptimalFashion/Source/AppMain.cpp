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

auto AppMain::ImageCache::Get(const std::string& name, const int size, const CardPurpose purpose, const bool flip) -> const wxBitmap&
{
	auto& cache = cacheMap[name][static_cast<size_t>(purpose)];

	if (!cache.loaded)
	{
		std::ostringstream oss;
		oss << "./DS3OptimalFashion_Images/" << name << (purpose == CardPurpose::Preview ? ".png" : "_128.png");

		cache.image.LoadFile(oss.str(), wxBITMAP_TYPE_PNG);
		cache.loaded = true;
	}

	if (cache.bitmaps[flip].GetWidth() != size)
	{
		auto image = cache.image.Scale(size, size, Convert(purpose));
		if (flip) image = image.Mirror();
		cache.bitmaps[flip] = wxBitmap{std::move(image)};
	}

	assert(cache.bitmaps[flip].GetHeight() == size && "Images should be 1:1");
	return cache.bitmaps[flip];
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

auto AppMain::GetParams() -> ParameterBroker&
{
	return parameterBroker;
}
