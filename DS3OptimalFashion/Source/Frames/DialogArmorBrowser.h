#pragma once

#include <wx/wx.h>
#include <ArmorPiece.hpp>

class DialogArmorBrowser final : public wxDialog
{
	class FilteredArmorPieces;
	FilteredArmorPieces* browser{nullptr};
	wxStaticText* status{nullptr};

public:
	DialogArmorBrowser(wxWindow* parent, const bool isWhitelist=true);

	void UpdateFilter(std::string filter, int flags);
};