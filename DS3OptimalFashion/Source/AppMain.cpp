#include "AppMain.h"

wxIMPLEMENT_APP(AppMain);

bool AppMain::OnInit()
{
	frameMain = new FrameMain();
	frameMain->Show();
	return true;
}
