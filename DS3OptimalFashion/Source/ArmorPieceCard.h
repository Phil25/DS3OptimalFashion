#pragma once

#include <wx/wx.h>

class ArmorPieceIcon final : public wxPanel
{
	wxImage image;
	bool highlighted{false};
	const bool miniature{false};
	const wxImageResizeQuality resizeQuality{miniature ? wxIMAGE_QUALITY_BILINEAR : wxIMAGE_QUALITY_NORMAL};

public:
	ArmorPieceIcon(wxWindow* parent, const bool miniature=false);

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
	const bool miniature{false};

public:
	ArmorPieceCard(wxWindow* parent, const bool miniatue=false);

	void SetPiece(const std::string& name);

private:
	void OnStartHover(wxMouseEvent& event);
	void OnExitHover(wxMouseEvent& event);
};

