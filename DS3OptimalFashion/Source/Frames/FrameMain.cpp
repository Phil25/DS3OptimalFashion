#include "FrameMain.h"

#include <Panels/ArmorSetSelectorPanel.h>
#include <Panels/ArmorPieceFilterPanel.h>
#include <Panels/ArmorFinderPanel.h>

FrameMain::FrameMain() : wxFrame(nullptr, wxID_ANY, "DS3OptimalFashion")
{
	auto* sizerLists = new wxBoxSizer(wxHORIZONTAL);
	auto* sizerInterface = new wxBoxSizer(wxVERTICAL);
	auto* sizerMain = new wxBoxSizer(wxHORIZONTAL);

	auto* panelWhitelist = new ArmorPieceFilterPanel(this, true);
	auto* panelBlacklist = new ArmorPieceFilterPanel(this, false);

	sizerLists->Add(panelWhitelist, 1, wxEXPAND | wxRIGHT, 3);
	sizerLists->Add(panelBlacklist, 1, wxEXPAND, 3);

	auto* panelPreview = new ArmorSetPreviewPanel(this);
	auto* panelParamsDisplay = new ParametersDisplayPanel(this);
	auto* panelSetSelector = new ArmorSetSelectorPanel(this, wxSize(850, 50), panelPreview, panelParamsDisplay);

	auto* panelFinder = new ArmorFinderPanel(this);

	sizerInterface->Add(panelSetSelector, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(panelParamsDisplay, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(panelFinder, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(sizerLists, 5, wxEXPAND);

	sizerMain->Add(panelPreview, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 3);
	sizerMain->Add(sizerInterface, 3, wxEXPAND | wxALL, 3);

	this->SetSizerAndFit(sizerMain);
}
