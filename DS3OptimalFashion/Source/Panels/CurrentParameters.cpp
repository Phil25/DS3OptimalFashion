#include "CurrentParameters.h"

#include <Panels/Details/ParameterField.h>

CurrentParameters::CurrentParameters(wxWindow* parent)
	: TitlePanel(parent, wxSize(800, 200), "Selected Armor")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* absPhysical = new GroupPanel(GetContent(), "Physical Absorption");
	absPhysical->AddItem<ParameterField>("Physical");
	absPhysical->AddItem<ParameterField>("Strike");
	absPhysical->AddItem<ParameterField>("Slash");
	absPhysical->AddItem<ParameterField>("Thrust");

	auto* absElemental = new GroupPanel(GetContent(), "Elemental Absorption");
	absElemental->AddItem<ParameterField>("Magic");
	absElemental->AddItem<ParameterField>("Fire");
	absElemental->AddItem<ParameterField>("Lightning");
	absElemental->AddItem<ParameterField>("Dark");

	auto* resistances = new GroupPanel(GetContent(), "Resistances");
	resistances->AddItem<ParameterField>("Bleed");
	resistances->AddItem<ParameterField>("Poison");
	resistances->AddItem<ParameterField>("Frost");
	resistances->AddItem<ParameterField>("Curse");

	auto* misc = new GroupPanel(GetContent(), "Miscellaneous");
	misc->AddItem<ParameterField>("Poise");
	misc->AddItem<ParameterField>("Weight");
	misc->AddItem<ParameterField>("Ratio");

	sizer->Add(absPhysical, 1, wxEXPAND);
	sizer->Add(absElemental, 1, wxEXPAND);
	sizer->Add(resistances, 1, wxEXPAND);
	sizer->Add(misc, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
