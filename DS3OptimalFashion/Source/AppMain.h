#pragma once

#include <Frames/FrameMain.h>
#include <Utils/CardPurpose.hpp>
#include <Utils/ParameterBroker.h>
#include <Database.h>
#include <wx/wx.h>
#include <map>
#include <array>
#include <memory>

class AppMain final : public wxApp
{
	class ImageCache final
	{
		struct ImageData
		{
			bool loaded{false};
			wxImage image;
			std::array<wxBitmap, 2> bitmaps;
		};

		using ImageDataArray = std::array<ImageData, static_cast<size_t>(CardPurpose::Size)>;

		const wxString imagePath;
		std::map<std::string, ImageDataArray> cacheMap;

	public:
		ImageCache(wxString imagePath);

		auto Selection(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto Mark(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto MarkDark(const int size, const CardPurpose purpose) -> const wxBitmap&;
		auto Get(const std::string& name, const int size, const CardPurpose purpose, const bool flip=false) -> const wxBitmap&;
	};

	using ImageCachePtr = std::unique_ptr<ImageCache>;
	ImageCachePtr imageCache;

	FrameMain* frameMain{nullptr};

	const optifa::Database armorData;
	ParameterBroker parameterBroker;

public:
	AppMain();

	bool OnInit() override;

	auto GetImageCache() const -> const ImageCachePtr&;
	auto GetArmorData() const -> const optifa::Database&;
	auto GetParams() -> ParameterBroker&;
};

DECLARE_APP(AppMain)
