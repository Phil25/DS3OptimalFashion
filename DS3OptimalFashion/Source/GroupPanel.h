#pragma once

#include <TitlePanel.h>
#include <ParameterField.h>
#include <array>

class GroupPanel final : public TitlePanel
{
	wxBoxSizer* sizer{nullptr};

public:
	GroupPanel(wxWindow* parent, const char* text, const wxOrientation orientation=wxVERTICAL);

	auto NewParamField(const char* name) -> ParameterField*;

	template <typename Control>
	auto NewEditableParamField(const char* name) -> ParameterFieldEditable<Control>*
	{
		auto* paramField = new ParameterFieldEditable<Control>(GetContent(), name);
		sizer->Add(paramField, 1, wxALIGN_CENTER);

		GetContent()->SetSizerAndFit(sizer);

		return paramField;
	}
};

class GridPanel final : public TitlePanel
{
	wxBoxSizer* mainSizer{nullptr};
	std::array<wxBoxSizer*, 4> sizers;
	std::array<wxPanel*, 4> panels;

public:
	GridPanel(wxWindow* parent, const char* text);

	auto NewParamField(int col, const char* name) -> ParameterField*;

	template <typename Control>
	auto NewEditableParamField(int col, const char* name) -> ParameterFieldEditable<Control>*
	{
		assert(0 <= col && col < 4);

		auto* paramField = new ParameterFieldEditable<Control>(panels[col], name);
		sizers[col]->Add(paramField, 1, wxALIGN_CENTER);

		panels[col]->SetSizerAndFit(sizers[col]);

		return paramField;
	}
};
