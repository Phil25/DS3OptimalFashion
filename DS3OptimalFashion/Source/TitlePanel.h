#pragma once

#include <wx/wx.h>

class TitlePanel : public wxPanel
{
	wxBoxSizer* sizer{nullptr};
	wxStaticText* title{nullptr};
	wxPanel* content{nullptr};

public:
	// TODO: everything will be auto adjusted, don't need size
	TitlePanel(wxWindow* parent, wxSize size, const char* titleText, int sizeText=14);

protected:
	auto GetContent() -> wxPanel*;
};
