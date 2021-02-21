#include "GroupPanel.h"

GroupPanel::GroupPanel(wxWindow* parent, const char* text, const wxOrientation orientation)
	: TitlePanel(parent, wxDefaultSize, text, 10)
	, sizer(new wxBoxSizer(orientation))
{
}

auto GroupPanel::NewParamField(const char* name) -> ParameterField*
{
	auto* paramField = new ParameterField(GetContent(), name);
	sizer->Add(paramField, 1, wxALIGN_CENTER);

	GetContent()->SetSizerAndFit(sizer);

	return paramField;
}

GridPanel::GridPanel(wxWindow* parent, const char* text)
	: TitlePanel(parent, wxDefaultSize, text, 10)
	, mainSizer{new wxBoxSizer(wxHORIZONTAL)}
	, sizers{new wxBoxSizer(wxVERTICAL), new wxBoxSizer(wxVERTICAL), new wxBoxSizer(wxVERTICAL), new wxBoxSizer(wxVERTICAL)}
	, panels{new wxPanel(GetContent()), new wxPanel(GetContent()), new wxPanel(GetContent()), new wxPanel(GetContent())}
{
	for (int i = 0; i < 4; ++i)
	{
		mainSizer->Add(panels[i], wxEXPAND | wxALL, 50);
		panels[i]->SetSizerAndFit(sizers[i]);
	}

	GetContent()->SetSizerAndFit(mainSizer);
}

auto GridPanel::NewParamField(int col, const char* name) -> ParameterField*
{
	assert(0 < col && col < 4);

	auto* paramField = new ParameterField(panels[col], name);
	sizers[col]->Add(paramField, 1, wxALIGN_CENTER);

	panels[col]->SetSizerAndFit(sizers[col]);

	return paramField;
}
