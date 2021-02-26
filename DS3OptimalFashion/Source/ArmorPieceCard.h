#pragma once

#include <wx/wx.h>

class ArmorPieceIcon final : public wxPanel
{
	wxImage image;
	bool highlighted{false};

public:
	ArmorPieceIcon(wxWindow* parent);

	void SetIcon(const std::string& file);
	void SetHighlight(const bool highlight=true);

private:
	void Render(wxDC& dc);
};

class ArmorPieceCard final : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	ArmorPieceIcon* icon{nullptr};
	wxTextCtrl* label{nullptr};

public:
	ArmorPieceCard(wxWindow* parent);

	void SetPiece(const std::string& name);

private:
	void OnStartHover(wxMouseEvent& event);
	void OnExitHover(wxMouseEvent& event);
};

