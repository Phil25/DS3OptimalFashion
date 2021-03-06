#pragma once

#include <wx/wx.h>
#include <Utils/CardPurpose.hpp>

template <CardPurpose Purpose>
class ArmorPieceIcon;

template <CardPurpose Purpose>
class ArmorPieceCard final : public wxPanel
{
	std::string name{"Naked Chest"};

	wxBoxSizer* sizer{nullptr};
	ArmorPieceIcon<Purpose>* icon{nullptr};
	wxTextCtrl* label{nullptr};

public:
	ArmorPieceCard(wxWindow* parent, const bool flip=false);
	void SetArmorPiece(std::string name);
	auto GetArmorPiece() const -> const std::string&;

private:
	void OnStartHover(wxMouseEvent& event);
	void OnExitHover(wxMouseEvent& event);
	void OnLeftClick(wxMouseEvent& event);
	void OnMiddleClick(wxMouseEvent& event);
	void OnRightClick(wxMouseEvent& event);
};
