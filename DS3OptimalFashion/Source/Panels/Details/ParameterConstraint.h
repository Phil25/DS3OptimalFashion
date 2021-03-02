#pragma once

#include <Panels/Details/ListPanel.hpp>
#include <Panels/Details/ParameterChoiceList.h>
#include <wx/spinctrl.h>

class ParameterConstraint final : public wxPanel
{
	using OwningListPanel = ListPanel<ParameterConstraint>;

	wxSpinCtrlDouble* value{nullptr};
	ParameterChoiceList* choiceList{nullptr};
	optifa::ArmorPiece::Param lastParam{optifa::ArmorPiece::Param::Physical};

public:
	ParameterConstraint(OwningListPanel* parent);

	void SetParameter(const optifa::ArmorPiece::Param);
	auto GetParameter() -> optifa::ArmorPiece::Param;

	auto GetParameterValue() -> float;

private:
	void ValueChange(wxCommandEvent&);
	void ConstraintChange(wxCommandEvent&);
	void Remove(wxCommandEvent&);
};
