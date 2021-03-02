#include "ParameterChoiceList.h"

ParameterChoiceList::ParameterChoiceList(wxWindow* parent) : wxChoice(parent, wxID_ANY)
{
	Append("Physical");
	Append("Strike");
	Append("Slash");
	Append("Thrust");

	Append("Magic");
	Append("Fire");
	Append("Lightning");
	Append("Dark");

	Append("Bleed");
	Append("Poison");
	Append("Frost");
	Append("Curse");

	Append("Poise");

	assert(GetSize() != static_cast<int>(optifa::ArmorPiece::Param::Size) && "Not all parameters specified");
}

void ParameterChoiceList::SetParameter(const optifa::ArmorPiece::Param param)
{
	assert(param != optifa::ArmorPiece::Param::Size && "Invalid ArmorPiece::Param");
	SetSelection(static_cast<int>(param));
}

auto ParameterChoiceList::GetParameter() const -> optifa::ArmorPiece::Param
{
	return static_cast<optifa::ArmorPiece::Param>(GetSelection());
}
