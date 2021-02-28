#include "ParameterField.h"

ParameterField::ParameterField(wxWindow* parent, const char* name)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxHORIZONTAL))
	, label(new wxStaticText(this, wxID_ANY, name))
	, value(new wxStaticText(this, wxID_ANY, "0.0"))
{
	label->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	sizer->Add(label, 5, wxEXPAND | wxCENTER | wxLEFT, 5);
	sizer->Add(value, 1, wxEXPAND | wxCENTER | wxRIGHT, 5);

	this->SetSizerAndFit(sizer);
}