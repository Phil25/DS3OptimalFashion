#include "AppMain.h"

wxIMPLEMENT_APP(AppMain);

bool AppMain::OnInit()
{
	wxInitAllImageHandlers();
	frameMain = new FrameMain();
	frameMain->Show();
	return true;
}
