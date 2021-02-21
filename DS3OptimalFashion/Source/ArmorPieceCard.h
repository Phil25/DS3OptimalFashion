#pragma once

#include <wx/wx.h>

class ArmorPieceCard final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	wxPanel* icon{nullptr}; // dummy wxPanel for now
	wxTextCtrl* label{nullptr};

public:
	ArmorPieceCard(wxWindow* parent);

private:
	void OnStartHover(wxMouseEvent& event);
	void OnExitHover(wxMouseEvent& event);
};

