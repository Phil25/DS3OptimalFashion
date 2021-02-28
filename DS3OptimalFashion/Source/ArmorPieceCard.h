#pragma once

#include <wx/wx.h>
#include <CardPurpose.hpp>

template <CardPurpose Purpose>
class ArmorPieceIcon;

template <CardPurpose Purpose>
class ArmorPieceCard final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	ArmorPieceIcon<Purpose>* icon{nullptr};
	wxTextCtrl* label{nullptr};

public:
	ArmorPieceCard(wxWindow* parent);

	void SetPiece(const std::string& name);

private:
	void OnStartHover(wxMouseEvent& event);
	void OnExitHover(wxMouseEvent& event);
	void OnClick(wxMouseEvent& event);
};
