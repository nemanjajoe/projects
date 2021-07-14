#include "gui.h"
#include <Windows.h>


class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

bool MyApp::OnInit() {
	MainFrame* frame = new MainFrame(nullptr, wxID_ANY);
	HWND hd = GetDesktopWindow(); 
	RECT rect;
	GetClientRect(hd, &rect);
	int client_width = (rect.right - rect.left);
	int client_height = (rect.bottom - rect.top);
	frame->SetSize(wxSize(client_width, client_height));
	frame->Show();

	return true;
}

wxIMPLEMENT_APP(MyApp);