#pragma once

#include <FrameMain.h>
#include <wx/wx.h>

class AppMain final : public wxApp
{
	FrameMain* frameMain{nullptr};

public:
	AppMain() = default;

	bool OnInit() override;
};