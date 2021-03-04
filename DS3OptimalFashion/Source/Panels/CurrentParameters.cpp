#include "CurrentParameters.h"

#include <Panels/Details/ParameterField.h>

void CurrentParameters::FieldArray::Set(Param at, ParameterField* f)
{
	assert(at != Param::Size && "Invalid parameter");
	arr[static_cast<size_t>(at)] = f;
}

auto CurrentParameters::FieldArray::Get(Param at) -> ParameterField*
{
	assert(at != Param::Size && "Invalid parameter");
	return arr[static_cast<size_t>(at)];
}

CurrentParameters::CurrentParameters(wxWindow* parent)
	: TitlePanel(parent, wxSize(800, 200), "Selected Armor")
{
	auto* sizer = new wxBoxSizer(wxHORIZONTAL);

	auto* absPhysical = new GroupPanel(GetContent(), "Physical Absorption");
	fields.Set(Param::Physical, absPhysical->AddItem<ParameterField>("Physical"));
	fields.Set(Param::Strike, absPhysical->AddItem<ParameterField>("Strike"));
	fields.Set(Param::Slash, absPhysical->AddItem<ParameterField>("Slash"));
	fields.Set(Param::Thrust, absPhysical->AddItem<ParameterField>("Thrust"));

	auto* absElemental = new GroupPanel(GetContent(), "Elemental Absorption");
	fields.Set(Param::Magic, absElemental->AddItem<ParameterField>("Magic"));
	fields.Set(Param::Fire, absElemental->AddItem<ParameterField>("Fire"));
	fields.Set(Param::Lightning, absElemental->AddItem<ParameterField>("Lightning"));
	fields.Set(Param::Dark, absElemental->AddItem<ParameterField>("Dark"));

	auto* resistances = new GroupPanel(GetContent(), "Resistances");
	fields.Set(Param::Bleed, resistances->AddItem<ParameterField>("Bleed"));
	fields.Set(Param::Poison, resistances->AddItem<ParameterField>("Poison"));
	fields.Set(Param::Frost, resistances->AddItem<ParameterField>("Frost"));
	fields.Set(Param::Curse, resistances->AddItem<ParameterField>("Curse"));

	auto* misc = new GroupPanel(GetContent(), "Miscellaneous");
	fields.Set(Param::Poise, misc->AddItem<ParameterField>("Poise"));
	fields.Set(Param::Weight, misc->AddItem<ParameterField>("Weight"));
	ratio = misc->AddItem<ParameterField>("Ratio");

	sizer->Add(absPhysical, 1, wxEXPAND);
	sizer->Add(absElemental, 1, wxEXPAND);
	sizer->Add(resistances, 1, wxEXPAND);
	sizer->Add(misc, 1, wxEXPAND);

	GetContent()->SetSizerAndFit(sizer);
}

void CurrentParameters::SetArmorSetParameter(const Param param, const float value, const int precision)
{
	assert(param != Param::Size && "Invalid parameter");
	fields.Get(param)->SetArmorSetParameter(value, precision);
}

void CurrentParameters::SetArmorSetRatio(const float value, const int precision)
{
	ratio->SetArmorSetParameter(value, precision);
}
