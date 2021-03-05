#pragma once

#include <ArmorSet.hpp>
#include <wx/wx.h>
#include <Panels/ArmorSetPreviewPanel.h>
#include <Panels/ParametersDisplayPanel.h>

class ArmorSetSelectorPanel : public wxPanel
{
	class ArmorUpdater;
	std::unique_ptr<ArmorUpdater> armorUpdater;

	ArmorSetPreviewPanel* preview{nullptr};
	ParametersDisplayPanel* paramsDisplay{nullptr};

	optifa::ArmorSet::Vector sets;

	wxStaticText* status{nullptr};
	wxChoice* setChoice{nullptr};

public:
	ArmorSetSelectorPanel(wxWindow* parent, wxSize size, ArmorSetPreviewPanel* preview, ParametersDisplayPanel* paramsDisplay);

	void SetSets(optifa::ArmorSet::Vector sets);

private:
	void SetSelection(wxCommandEvent&);
	void SetSelection(const int index);
	void UpdateParamsDisplay(const int index);
};
