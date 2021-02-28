#pragma once

#include <wx/wx.h>

class DialogArmorBrowser final : public wxDialog
{
public:
	DialogArmorBrowser(wxWindow* parent, const bool isWhitelist=true);
};