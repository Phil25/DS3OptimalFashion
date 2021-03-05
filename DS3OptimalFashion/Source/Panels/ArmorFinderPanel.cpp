#include "ArmorFinderPanel.h"

#include <AppMain.h>
#include <Panels/Details/GroupPanel.hpp>
#include <Panels/Details/ParameterConstraint.h>
#include <Panels/Details/ParameterField.h>

ArmorFinderPanel::ArmorFinderPanel(wxWindow* parent) : TitlePanel(parent, wxSize(800, 200), "Armor Finder")
{
	using FloatEdit = ParameterFieldEditable<wxSpinCtrlDouble>;
	using ParamEdit = ParameterFieldEditable<ParameterChoiceList>;

	auto* stats = new GroupPanel(GetContent(), "Build Stats");

	auto* currentLoad = stats->AddItem<FloatEdit>("Current Load");
	currentLoad->GetControl()->Bind(wxEVT_SPINCTRLDOUBLE, &ArmorFinderPanel::CurrentLoadUpdate, this);
	currentLoad->GetControl()->SetRange(0, 500);

	auto* fullLoad = stats->AddItem<FloatEdit>("Full Load");
	fullLoad->GetControl()->Bind(wxEVT_SPINCTRLDOUBLE, &ArmorFinderPanel::FullLoadUpdate, this);
	fullLoad->GetControl()->SetRange(0, 500);

	auto* percentage = stats->AddItem<FloatEdit>("Percentage");
	percentage->GetControl()->Bind(wxEVT_SPINCTRLDOUBLE, &ArmorFinderPanel::PercentageUpdate, this);
	percentage->GetControl()->SetValue(70.);
	percentage->GetControl()->SetRange(0, 100);

	auto* maximization = new GroupPanel(GetContent(), "Parameter to Maximize");

	auto* maximize = maximization->AddItem<ParamEdit>("Maximize");
	maximize->GetControl()->Bind(wxEVT_CHOICE, &ArmorFinderPanel::MaximizeParamUpdate, this);
	maximize->GetControl()->SetParameter(optifa::ArmorPiece::Param::Physical);

	auto* maxDelta = maximization->AddItem<FloatEdit>("Max Delta");
	maxDelta->GetControl()->Bind(wxEVT_SPINCTRLDOUBLE, &ArmorFinderPanel::MaxDeltaUpdate, this);
	maxDelta->GetControl()->SetRange(0, 0.5);

	auto* constraints = new GroupPanel(GetContent(), "Minimal Parameter Constraints");
	auto* constraintList = constraints->AddItem<ListPanel<ParameterConstraint>, false>();
	constraintList->AddListItem();
	constraintList->SetLimit(static_cast<uint32_t>(optifa::ArmorPiece::Param::Weight)); // exclude weight

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(stats, 1, wxEXPAND);
	sizer->Add(maximization, 1, wxEXPAND);
	sizer->Add(constraints, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}

void ArmorFinderPanel::CurrentLoadUpdate(wxSpinDoubleEvent& e)
{
	auto val = static_cast<wxSpinCtrlDouble*>(e.GetEventObject())->GetValue();
	assert(val >= 0 && "CurrentLoadUpdate: invalid value");
	wxGetApp().GetParams().SetCurrentLoad(val);
}

void ArmorFinderPanel::FullLoadUpdate(wxSpinDoubleEvent& e)
{
	auto val = static_cast<wxSpinCtrlDouble*>(e.GetEventObject())->GetValue();
	assert(val >= 0 && "FullLoadUpdate: invalid value");
	wxGetApp().GetParams().SetFullLoad(val);
}

void ArmorFinderPanel::PercentageUpdate(wxSpinDoubleEvent& e)
{
	auto val = static_cast<wxSpinCtrlDouble*>(e.GetEventObject())->GetValue();
	assert(0 <= val && val <= 100 && "PercentageUpdate: invalid value");
	wxGetApp().GetParams().SetPercentage(val);
}

void ArmorFinderPanel::MaximizeParamUpdate(wxCommandEvent& e)
{
	auto val = static_cast<ParameterChoiceList*>(e.GetEventObject())->GetParameter();
	wxGetApp().GetParams().SetParameter(val);
}

void ArmorFinderPanel::MaxDeltaUpdate(wxSpinDoubleEvent& e)
{
	auto val = static_cast<wxSpinCtrlDouble*>(e.GetEventObject())->GetValue();
	wxGetApp().GetParams().SetDelta(val);
}
