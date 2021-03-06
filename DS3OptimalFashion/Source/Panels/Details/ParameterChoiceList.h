#pragma once

#include <wx/wx.h>
#include <ArmorPiece.hpp>

class ParameterChoiceList final : public wxChoice
{
public:
	ParameterChoiceList(wxWindow* parent, const bool limitToUnconstrained=false);

	void SetParameter(const optifa::ArmorPiece::Param param);
	auto GetParameter() const -> optifa::ArmorPiece::Param;
};
