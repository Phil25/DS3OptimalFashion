#include "ArmorFinder.h"

ArmorFinder::ArmorFinder(wxWindow* parent) : TitlePanel(parent, wxSize(800, 200), "Armor Finder")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* options = new GroupPanel(GetContent(), "Options");
	options->NewEditableParamField<wxSpinCtrlDouble>("Current Load");
	options->NewEditableParamField<wxSpinCtrlDouble>("Max Load");
	options->NewEditableParamField<wxSpinCtrlDouble>("Percentage")->SetValue(70.);
	options->NewEditableParamField<ParameterChoiceList>("Maximize");
	options->NewEditableParamField<wxSpinCtrlDouble>("Delta");

	auto* constraints = new GridPanel(GetContent(), "Minimal Parameter Constraints");

	constraints->NewEditableParamField<wxSpinCtrlDouble>(0, "Physical");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(0, "Strike");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(0, "Slash");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(0, "Thrust");

	constraints->NewEditableParamField<wxSpinCtrlDouble>(1, "Magic");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(1, "Fire");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(1, "Lightning");
	constraints->NewEditableParamField<wxSpinCtrlDouble>(1, "Dark");

	constraints->NewEditableParamField<wxSpinCtrl>(2, "Bleed");
	constraints->NewEditableParamField<wxSpinCtrl>(2, "Poison");
	constraints->NewEditableParamField<wxSpinCtrl>(2, "Frost");
	constraints->NewEditableParamField<wxSpinCtrl>(2, "Curse");

	constraints->NewEditableParamField<wxSpinCtrlDouble>(3, "Poise");

	sizer->Add(options, 1, wxEXPAND);
	sizer->Add(constraints, 3, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}
