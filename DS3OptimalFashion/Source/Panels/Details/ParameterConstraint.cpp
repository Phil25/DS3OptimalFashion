#include "ParameterConstraint.h"

#include <AppMain.h>

ParameterConstraint::ParameterConstraint(OwningListPanel* parent)
	: wxPanel(parent)
	, value(new wxSpinCtrlDouble(this))
	, choiceList(new ParameterChoiceList(this))
{
	value->Bind(wxEVT_SPINCTRLDOUBLE, &ParameterConstraint::ValueChange, this);
	choiceList->Bind(wxEVT_CHOICE, &ParameterConstraint::ConstraintChange, this);
	choiceList->SetParameter(lastParam);

	auto* remover = new wxButton(this, wxID_ANY, wxT("X"));
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	remover->SetMinSize(wxSize(24, 24));
	remover->SetBackgroundColour(wxColor(255, 200, 200));
	remover->Bind(wxEVT_BUTTON, &ParameterConstraint::Remove, this);

	sizer->Add(choiceList, 3, wxALL, 2);
	sizer->Add(value, 2, wxALL, 2);
	sizer->AddStretchSpacer(1);
	sizer->Add(remover, 0, wxALL, 2);

	this->SetSizerAndFit(sizer);
}

void ParameterConstraint::SetParameter(const optifa::ArmorPiece::Param param)
{
	assert(param != optifa::ArmorPiece::Param::Size && "Invalid parameter;");
	choiceList->SetSelection(static_cast<int>(param));
}

auto ParameterConstraint::GetParameter() -> optifa::ArmorPiece::Param
{
	return static_cast<optifa::ArmorPiece::Param>(choiceList->GetSelection());
}

auto ParameterConstraint::GetParameterValue() -> float
{
	return value->GetValue();
}

void ParameterConstraint::ValueChange(wxCommandEvent&)
{
	wxGetApp().GetParams().SetConstraint(lastParam, value->GetValue());
}

void ParameterConstraint::ConstraintChange(wxCommandEvent&)
{
	wxGetApp().GetParams().RemoveConstraint(lastParam);
	lastParam = choiceList->GetParameter();
	wxGetApp().GetParams().SetConstraint(lastParam, value->GetValue());
}

void ParameterConstraint::Remove(wxCommandEvent&)
{
	wxGetApp().GetParams().RemoveConstraint(choiceList->GetParameter());
	static_cast<OwningListPanel*>(GetParent())->RemoveListItem(this);
}
