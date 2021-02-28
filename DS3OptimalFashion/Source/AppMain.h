#pragma once

#include <Frames/FrameMain.h>
#include <Utils/CardPurpose.hpp>
#include <wx/wx.h>
#include <map>
#include <array>

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
		auto Get(const std::string& name, const int size, const CardPurpose purpose) -> const wxBitmap&;
	};

	using ImageCachePtr = std::unique_ptr<ImageCache>;
	ImageCachePtr imageCache;

public:
	AppMain() = default;

	bool OnInit() override;

	auto GetImageCache() const -> const ImageCachePtr&;
};

DECLARE_APP(AppMain)