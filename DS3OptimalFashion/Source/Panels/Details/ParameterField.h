#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>

// TODO: try to rework into a single, more generic class

class ParameterField final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	wxStaticText* label{nullptr};
	wxStaticText* value{nullptr};

public:
	ParameterField(wxWindow* parent, const char* name);

	void SetArmorSetParameter(const float val, int precision);
};

template <typename Control>
class ParameterFieldEditable final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	wxStaticText* label{nullptr};
	Control* value{nullptr};

public:
	ParameterFieldEditable(wxWindow* parent, const char* name)
		: wxPanel(parent, wxID_ANY)
		, sizer(new wxBoxSizer(wxHORIZONTAL))
		, label(new wxStaticText(this, wxID_ANY, name))
		, value(new Control(this))
	{
		label->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
		value->SetMaxSize(wxSize(80, 80));

		if constexpr (std::is_same_v<Control, wxSpinCtrlDouble>)
		{
			value->SetDigits(2);
			value->SetIncrement(0.1);
		}

		sizer->Add(label, 3, wxCENTER | wxLEFT, 5);
		sizer->Add(value, 2, wxCENTER | wxRIGHT, 5);

		this->SetSizerAndFit(sizer);
	}

	auto GetControl()
	{
		return value;
	}
};
