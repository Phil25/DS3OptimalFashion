#include "ParameterField.h"

#include <sstream>
#include <iomanip>

namespace
{
	inline float RoundToNAfterComma(const float val, int precision=3) noexcept
	{
		const int mult = 10 * precision;
		return std::round(val * mult) / mult;
	}
}

ParameterField::ParameterField(wxWindow* parent, const char* name)
	: wxPanel(parent, wxID_ANY)
	, sizer(new wxBoxSizer(wxHORIZONTAL))
	, label(new wxStaticText(this, wxID_ANY, name))
	, value(new wxStaticText(this, wxID_ANY, "-"))
{
	label->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	value->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN));
	value->SetMinSize(wxSize(50, 20));

	sizer->Add(label, 1, wxLEFT | wxRIGHT, 5);
	sizer->Add(value, 1, wxLEFT | wxRIGHT, 5);

	this->SetSizerAndFit(sizer);
}

void ParameterField::SetArmorSetParameter(const float val, int precision)
{
	std::ostringstream oss;
	oss << std::setprecision(precision) << std::fixed << val;
	value->SetLabel(oss.str());
}
