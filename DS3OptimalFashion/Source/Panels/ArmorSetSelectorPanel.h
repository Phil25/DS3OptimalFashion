#pragma once

#include <wx/wx.h>
#include <Panels/ArmorSetPreviewPanel.h>
#include <Panels/CurrentParameters.h>

class ArmorSetSelectorPanel : public wxPanel
{
	class ArmorUpdater;
	std::unique_ptr<ArmorUpdater> armorUpdater;

	ArmorSetPreviewPanel* preview{nullptr};
	CurrentParameters* paramsDisplay{nullptr};

public:
	ArmorSetSelectorPanel(wxWindow* parent, wxSize size, ArmorSetPreviewPanel* preview, CurrentParameters* paramsDisplay);
};
