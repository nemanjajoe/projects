///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/wrapsizer.h>
#include <wx/frame.h>
#include <wx/numdlg.h>
#include <wx/wx.h>
#include <vector>
#include <ctime>
#include <string>
#include <wx/datetime.h>
#include "HWPuSDK.h"
#include <wx/msgdlg.h>
#include <string.h>
#include <windows.h>
///////////////////////////////////////////////////////////////////////////

enum {
	TIMER_UPDATE_ID,
	ALARM_DURARION_ID,
	ALARM_INTERVAL_ID,
	SET_PEOPLE_NUM_ID,
	BUTTON_CLICKED_ID = wxID_OK,
	CONNECT_CAMERA_ID,
	DISCONNECT_CAMERA_ID,
	TIMER_ALARM_ID
};

typedef struct{
	ULONG people_in;
	ULONG people_out;
	ULONG alarm_duration;
	ULONG alarm_interval;
} data_t;



///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{

#pragma region GUI

protected:
	wxMenuBar* m_menu_bar;
	wxMenu* m_menu;
	wxPanel* m_panel_left;
	wxPanel* m_panel_left_left;
	wxStaticText* m_staticText3;
	wxStaticText* m_staticText4;
	wxStaticText* m_staticText5;
	wxPanel* m_panel_left_median;
	wxStaticText* m_people_num;
	wxStaticText* m_exist_people;
	wxStaticText* m_available_people;
	wxPanel* m_panel_left_right;
	wxStaticText* m_staticText9;
	wxStaticText* m_staticText10;
	wxStaticText* m_staticText11;
	wxPanel* m_panel_right;
	wxPanel* m_panel_right_up;
	wxPanel* m_panel_years;
	wxStaticText* m_years;
	wxStaticText* m_hours;
	wxPanel* m_panel10;
	wxStaticText* m_staticText14;
	wxStaticText* m_staticText15;
	wxPanel* m_panel_months;
	wxStaticText* m_months;
	wxStaticText* m_minutes;
	wxPanel* m_panel12;
	wxStaticText* m_staticText18;
	wxStaticText* m_staticText19;
	wxPanel* m_panel_days;
	wxStaticText* m_days;
	wxStaticText* m_seconds;
	wxPanel* m_panel14;
	wxStaticText* m_staticText22;
	wxStaticText* m_staticText23;
	wxPanel* m_panel_right_down;
	wxPanel* m_panel17;
	wxPanel* m_panel18;
	wxStaticText* m_rooms;

	wxFlexGridSizer* left_container;

public:
	   
	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainFrame();
#pragma endregion 

private: //members varaibles
	wxTimer m_timer;
	wxTimer m_alarm_timer;
	ULONG m_today_time;
	data_t m_data;
	long m_userID;
	bool FLAG_IS_CAMERA_ON = false;
	bool FLAG_IS_PEOPLE_FULL = false;
	std::vector<wxStaticText*> people_text;
	std::vector<wxStaticText*> time_text;
public: //functions
	bool InitSDK();
	bool DeviceLogin();
	bool DeviceLogout();
	bool ClearSDK();
	bool GetHunmanCountTable();
	bool StartSnap();
	bool StopSnap();
	void AnalysisMetaDataTarget(PU_META_DATA* pstMetaTargetData);


	void OnUpdateWindow(wxTimerEvent& event);
	void OnAlarmBeepSound(wxTimerEvent& event);
	void OnResizeWindow(wxSizeEvent& event);
	void OnSetPeopleNum(wxCommandEvent& event);
	void OnAlarmDuration(wxCommandEvent& event);
	void OnAlarmInterval(wxCommandEvent& event);
	void OnConnectCamera(wxCommandEvent& event);
	void OnDisconnectCamera(wxCommandEvent& event);

	// auxiliary functions
	DECLARE_EVENT_TABLE();
};
