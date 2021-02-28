#include "ParameterConstraint.h"

ParameterConstraint::ParameterConstraint(OwningListPanel* parent)
	: wxPanel(parent)
	, value(new wxSpinCtrlDouble(this))
	, choiceList(new ParameterChoiceList(this))
{
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

void ParameterConstraint::SetParameter(int selection)
{
	choiceList->SetSelection(selection);
}

auto ParameterConstraint::GetParameter() -> int
{
	return choiceList->GetSelection();
}

auto ParameterConstraint::GetParameterValue() -> float
{
	return value->GetValue();
}

void ParameterConstraint::Remove(wxCommandEvent&)
{
	static_cast<OwningListPanel*>(GetParent())->RemoveListItem(this);
}
