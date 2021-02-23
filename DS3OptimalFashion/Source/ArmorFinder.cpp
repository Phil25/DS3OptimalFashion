#include "ArmorFinder.h"

#include <ParameterConstraint.h>

ArmorFinder::ArmorFinder(wxWindow* parent) : TitlePanel(parent, wxSize(800, 200), "Armor Finder")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* stats = new GroupPanel(GetContent(), "Build Stats");
	stats->NewEditableParamField<wxSpinCtrlDouble>("Current Load");
	stats->NewEditableParamField<wxSpinCtrlDouble>("Full Load");
	stats->NewEditableParamField<wxSpinCtrlDouble>("Percentage")->SetValue(70.);

	auto* maximization = new GroupPanel(GetContent(), "Parameter to Maximize");
	maximization->NewEditableParamField<ParameterChoiceList>("Maximize");
	maximization->NewEditableParamField<wxSpinCtrlDouble>("Max Delta");

	auto* constraints = new GroupPanel(GetContent(), "Minimal Parameter Constraints");
	auto* listPanel = constraints->AddItem<ListPanel<ParameterConstraint>>();
	listPanel->AddListItem()->SetParameter(12);

	sizer->Add(stats, 1, wxEXPAND);
	sizer->Add(maximization, 1, wxEXPAND);
	sizer->Add(constraints, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
