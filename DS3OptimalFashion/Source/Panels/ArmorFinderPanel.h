#pragma once

#include <Panels/Details/TitlePanel.h>
#include <wx/spinctrl.h>

class ArmorFinderPanel final : public TitlePanel
{
public:
	ArmorFinderPanel(wxWindow* parent);

private:
	void CurrentLoadUpdate(wxSpinDoubleEvent&);
	void FullLoadUpdate(wxSpinDoubleEvent&);
	void PercentageUpdate(wxSpinDoubleEvent&);

	void MaximizeParamUpdate(wxCommandEvent&);
	void MaxDeltaUpdate(wxSpinDoubleEvent&);
};