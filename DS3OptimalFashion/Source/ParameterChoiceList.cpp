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

	SetSelection(0);
}
