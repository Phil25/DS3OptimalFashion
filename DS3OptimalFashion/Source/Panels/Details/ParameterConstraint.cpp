#include "ParameterConstraint.h"

#include <AppMain.h>

ParameterConstraint::ParameterConstraint(OwningListPanel* parent)
	: wxPanel(parent)
	, value(new wxSpinCtrlDouble(this))
	, choiceList(new ParameterChoiceList(this))
{
	value->Bind(wxEVT_SPINCTRLDOUBLE, &ParameterConstraint::ValueChange, this);
	value->SetDigits(2);
	value->SetIncrement(0.1);

	lastParam = FindUnconstrainedParameter();
	choiceList->SetParameter(lastParam);
	choiceList->Bind(wxEVT_CHOICE,&ParameterConstraint::ConstraintChange, this);

	auto* remover = new wxButton(this, wxID_ANY, wxT("X"));
	remover->SetMinSize(wxSize(24, 24));
	remover->SetBackgroundColour(wxColor(255, 200, 200));
	remover->Bind(wxEVT_BUTTON, &ParameterConstraint::Remove, this);

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(choiceList, 3, wxALL, 2);
	sizer->Add(value, 3, wxALL, 2);
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
	auto newParam = choiceList->GetParameter();

	if (auto* other = FindConstraintWithParam(newParam); other)
	{
		SwapWithAnotherConstraint(other);
		// values are swapped too -- nothing needs updating
	}
	else
	{
		wxGetApp().GetParams().RemoveConstraint(lastParam, true);
		wxGetApp().GetParams().SetConstraint(newParam, value->GetValue());
	}

	lastParam = newParam;
}

void ParameterConstraint::Remove(wxCommandEvent&)
{
	wxGetApp().GetParams().RemoveConstraint(choiceList->GetParameter());
	static_cast<OwningListPanel*>(GetParent())->RemoveListItem(this);
}

auto ParameterConstraint::FindConstraintWithParam(const optifa::ArmorPiece::Param param) const -> ParameterConstraint*
{
	auto* list = static_cast<OwningListPanel*>(GetParent());
	for (size_t i = 0; i < list->GetListItemCount(); ++i)
	{
		auto* c = list->GetItemAtIndex(i);
		if (c->choiceList->GetParameter() == param && c != this)
			return c; // there should be only one other constraint with this param set (if any)
	}

	return nullptr;
}

void ParameterConstraint::SwapWithAnotherConstraint(ParameterConstraint* other)
{
	auto otherParam = other->choiceList->GetParameter();
	auto otherValue = other->value->GetValue();

	other->lastParam = this->lastParam;
	other->choiceList->SetParameter(this->lastParam);
	other->value->SetValue(this->value->GetValue());

	this->lastParam = otherParam;
	this->choiceList->SetParameter(otherParam);
	this->value->SetValue(otherValue);
}

auto ParameterConstraint::FindUnconstrainedParameter() const -> optifa::ArmorPiece::Param
{
	if (FindConstraintWithParam(lastParam) == nullptr)
		return lastParam; // current one is already free (init scenario)

	int paramInt = -1;
	while (++paramInt < static_cast<int>(optifa::ArmorPiece::Param::Size))
	{
		auto param = static_cast<optifa::ArmorPiece::Param>(paramInt);

		if (auto* other = FindConstraintWithParam(param); other == nullptr)
			return param;
	}

	assert(false && "Owning list should be limited to number of params");
	return optifa::ArmorPiece::Param{};
}
