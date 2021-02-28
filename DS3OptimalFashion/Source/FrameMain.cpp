#include "FrameMain.h"

#include <ArmorPieceFilterPanel.h>
#include <ArmorSetPreviewPanel.h>
#include <CurrentParameters.h>
#include <ArmorFinder.h>

FrameMain::FrameMain() : wxFrame(nullptr, wxID_ANY, "DS3OptimalFashion")
{
	auto* sizerLists = new wxBoxSizer(wxHORIZONTAL);
	auto* sizerInterface = new wxBoxSizer(wxVERTICAL);
	auto* sizerMain = new wxBoxSizer(wxHORIZONTAL);

	auto* panelWhitelist = new ArmorPieceFilterPanel(this, true);
	auto* panelBlacklist = new ArmorPieceFilterPanel(this, false);

	sizerLists->Add(panelWhitelist, 1, wxEXPAND | wxRIGHT, 3);
	sizerLists->Add(panelBlacklist, 1, wxEXPAND, 3);

	auto* panelSetSelector = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(850, 50));
	auto* panelCurrentParams = new CurrentParameters(this);
	auto* panelFinder = new ArmorFinder(this);

	sizerInterface->Add(panelSetSelector, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(panelCurrentParams, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(panelFinder, 0, wxEXPAND | wxBOTTOM, 3);
	sizerInterface->Add(sizerLists, 5, wxEXPAND);

	auto* panelPreview = new ArmorSetPreviewPanel(this);

	sizerMain->Add(panelPreview, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 3);
	sizerMain->Add(sizerInterface, 3, wxEXPAND | wxALL, 3);

	this->SetSizerAndFit(sizerMain);
}
