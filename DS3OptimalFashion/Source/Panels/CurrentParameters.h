#pragma once

#include <ArmorPiece.hpp>
#include <Panels/Details/GroupPanel.hpp>
#include <Panels/Details/ParameterField.h>

class CurrentParameters final : public TitlePanel
{
	using Param = optifa::ArmorPiece::Param;

	class FieldArray
	{
		std::array<ParameterField*, static_cast<size_t>(Param::Size)> arr;

	public:
		void Set(Param at, ParameterField*);
		auto Get(Param at) -> ParameterField*;
	};

	FieldArray fields{};
	ParameterField* ratio{nullptr};

public:
	CurrentParameters(wxWindow* parent);

	void SetArmorSetParameter(const Param, const float value, const int precision);
	void SetArmorSetRatio(const float value, const int precision);
};
