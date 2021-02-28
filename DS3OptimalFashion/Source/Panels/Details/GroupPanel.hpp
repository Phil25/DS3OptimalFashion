#pragma once

#include <Panels/Details/TitlePanel.h>
#include <array>

class GroupPanel final : public TitlePanel
{
	wxBoxSizer* sizer{nullptr};

public:
	GroupPanel(wxWindow* parent, const char* text, const wxOrientation orientation=wxVERTICAL)
		: TitlePanel(parent, wxDefaultSize, text, 10)
		, sizer(new wxBoxSizer(orientation))
	{
	}

	template <typename ItemClass, bool Center=true, typename... Args>
	auto AddItem(Args&&... args) -> ItemClass*
	{
		auto* item = new ItemClass(GetContent(), std::forward<Args>(args)...);

		if constexpr (Center)
		{
			sizer->Add(item, 1, wxALIGN_CENTER);
		}
		else
		{
			sizer->Add(item, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
		}

		GetContent()->SetSizerAndFit(sizer);

		return item;
	}
};
