#include "ArmorFinder.h"

#include <ParameterConstraint.h>

ArmorFinder::ArmorFinder(wxWindow* parent) : TitlePanel(parent, wxSize(800, 200), "Armor Finder")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* stats = new GroupPanel(GetContent(), "Build Stats");
	stats->AddItem<ParameterFieldEditable<wxSpinCtrlDouble>>("Current Load");
	stats->AddItem<ParameterFieldEditable<wxSpinCtrlDouble>>("Full Load");
	stats->AddItem<ParameterFieldEditable<wxSpinCtrlDouble>>("Percentage")->SetValue(70.);

	auto* maximization = new GroupPanel(GetContent(), "Parameter to Maximize");
	maximization->AddItem<ParameterFieldEditable<ParameterChoiceList>>("Maximize");
	maximization->AddItem<ParameterFieldEditable<wxSpinCtrlDouble>>("Max Delta");

	auto* constraints = new GroupPanel(GetContent(), "Minimal Parameter Constraints");
	constraints->AddItem<ListPanel<ParameterConstraint>, false>()->AddListItem()->SetParameter(12);

	sizer->Add(stats, 1, wxEXPAND);
	sizer->Add(maximization, 1, wxEXPAND);
	sizer->Add(constraints, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
