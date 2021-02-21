#include "CurrentParameters.h"

CurrentParameters::CurrentParameters(wxWindow* parent)
	: TitlePanel(parent, wxSize(800, 200), "Selected Armor")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* absPhysical = new GroupPanel(GetContent(), "Physical Absorption");
	absPhysical->NewParamField("Physical");
	absPhysical->NewParamField("Strike");
	absPhysical->NewParamField("Slash");
	absPhysical->NewParamField("Thrust");

	auto* absElemental = new GroupPanel(GetContent(), "Elemental Absorption");
	absElemental->NewParamField("Magic");
	absElemental->NewParamField("Fire");
	absElemental->NewParamField("Lightning");
	absElemental->NewParamField("Dark");

	auto* resistances = new GroupPanel(GetContent(), "Resistances");
	resistances->NewParamField("Bleed");
	resistances->NewParamField("Poison");
	resistances->NewParamField("Frost");
	resistances->NewParamField("Curse");

	auto* misc = new GroupPanel(GetContent(), "Miscellaneous");
	misc->NewParamField("Poise");
	misc->NewParamField("Weight");
	misc->NewParamField("Ratio");

	sizer->Add(absPhysical, 1, wxEXPAND);
	sizer->Add(absElemental, 1, wxEXPAND);
	sizer->Add(resistances, 1, wxEXPAND);
	sizer->Add(misc, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
