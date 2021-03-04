#pragma once

#include <ArmorSet.hpp>
#include <wx/wx.h>
#include <Panels/ArmorSetPreviewPanel.h>
#include <Panels/CurrentParameters.h>

class ArmorSetSelectorPanel : public wxPanel
{
	class ArmorUpdater;
	std::unique_ptr<ArmorUpdater> armorUpdater;

	ArmorSetPreviewPanel* preview{nullptr};
	CurrentParameters* paramsDisplay{nullptr};

	optifa::ArmorSet::Vector sets;

public:
	ArmorSetSelectorPanel(wxWindow* parent, wxSize size, ArmorSetPreviewPanel* preview, CurrentParameters* paramsDisplay);

	void SetSets(optifa::ArmorSet::Vector sets);

private:
	void SetSelection(const int setIndex);
	void UpdateParamsDisplay(const int setIndex);
};
