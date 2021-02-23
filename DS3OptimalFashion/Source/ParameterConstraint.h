#pragma once

#include <ListPanel.hpp>
#include <ParameterChoiceList.h>
#include <wx/spinctrl.h>

class ParameterConstraint final : public wxPanel
{
	using OwningListPanel = ListPanel<ParameterConstraint>;

	wxSpinCtrlDouble* value{nullptr};
	ParameterChoiceList* choiceList{nullptr};

public:
	ParameterConstraint(OwningListPanel* parent);

	void SetParameter(int selection);  // TODO: make this the param enum from Core
	auto GetParameter() -> int;  // TODO: make this the param enum from Core

	auto GetParameterValue() -> float;

private:
	void Remove(wxCommandEvent&);
};
