///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"
#include <ctime>
#include <string>
#include <wx/datetime.h>
#include "HWPuSDK.h"
#include <wx/msgdlg.h>
#include <string.h>
#include <windows.h>
///////////////////////////////////////////////////////////////////////////
/////////////////////////// structures /////////////////////////////////////
BOOL Snap = FALSE;
extern int m_UserID;
int No_num = 0;
int m_ulRetRelPlay = 0;//抓拍的句柄
BOOL isFirst = TRUE;
int imgWidth = 0;
int imgHeight = 0;
int channelId = 0;
int objId = 0;
int objType = 0;
int objStatus = 0;
int targetType = 0;
bool isStart = true;
bool hasTarget = false;
// 目标状态
typedef enum ENUM_TGT_STATUS_M
{
	IVS_TGT_STATUS_NONE = 0x00000000, // 无状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_WANDER = 0x00000001, // 徘徊状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_TRIPWIRE = 0x00000002, // 绊线状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_ABANDON = 0x00000004, // 遗留状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_REMOVE = 0x00000008, // 移走状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_INVASION = 0x00000010, // 入侵状态[x00209211@2012-12-18]
	IVS_TGT_STATUS_ENTER = 0x00000020, // 区域进入状态
	IVS_TGT_STATUS_EXIT = 0x00000040, // 区域离开状态
	IVS_TGT_STATUS_FASTMOVE = 0x00000080, // 快速移动状态
}ENUM_TGT_STATUS;
//不同类型的目标检测框
typedef enum _OBJ_FRAME_TYPE_E
{
	OBJ_FRAME_TYPE_NONE = 0x00,     // 未分类
	OBJ_FRAME_TYPE_VEHICLE = 0x01,  // 车
	OBJ_FRAME_TYPE_HUMAN = 0x02,    // 人
	OBJ_FRAME_TYPE_VEH = 0x60,      // 机非人的机动车
	OBJ_FRAME_TYPE_NMV = 0x61,      // 机非人的非机动车
	OBJ_FRAME_TYPE_PED = 0x62,      // 机非人的行人

	OBJ_FRAME_TYPE_ZERO = 0x80,     // 区域显示框类型0:人脸框
	OBJ_FRAME_TYPE_ONE = 0x81,      // 区域显示框类型1:人框
	OBJ_FRAME_TYPE_TWO = 0x82,      // 区域显示框类型2:非机动车框
	OBJ_FRAME_TYPE_THREE = 0x83,    // 区域显示框类型3:机动车框
	OBJ_FRAME_TYPE_FOUR = 0x84,     // 区域显示框类型4:在人脸业务中是人身框、在交通业务中是车牌框
	OBJ_FRAME_TYPE_FIVE = 0x85,     // 区域显示框类型5:停车侦测使用框
	OBJ_FRAME_TYPE_SIX = 0x86,      // 区域显示框类型6:人群密度使用框
	OBJ_FRAME_TYPE_SEVEN = 0x87,    // 区域显示框类型7:排队长度使用框
	OBJ_FRAME_TYPE_EIGHT = 0x88,    // 区域显示框类型8:违停球使用框
	OBJ_FRAME_TYPE_NINE = 0x89,     // 区域显示框类型9:自动跟踪使用框

	OBJ_FRAME_TYPE_OTHER = 0xFF,    // 其他
	OBJ_FRAME_TYPE_MAX,
}ITGT_OBJ_FRAME_TYPE_E;
typedef enum _RULE_TYPE_E//规则类型
{
	TRIPWIRE_RULE = 0,//拌线
	WANDER_RULE,//徘徊
	ABANDON_RULE,//物品遗留
	REMOVE_RULE,//移走
	INVASION_RULE,//入侵
	ENTER_RULE,//区域进入
	EXIT_RULE,//区域离开
	FASTMOVE_RULE,//快速移动
	CARDETECTION_RULE,//停车侦测
	HUMANCOUNT_RULE,//人头计数
	CROWDDENSITY_DETECT_RULE,//人群密度检测
	QUEUE_DETECT_RULE,//排队长度检测
	IBALL_DETECT_RULE,//违停球违停检测
	MSL_AUTO_CALIB_RULE,//枪球联动发动自动标定元数据
	MSL_AUTO_CALIB_RULE_CLEAR,//抢球联动清除自动标定元数据
	RULE_TYPE_MAX
} RULE_TYPE_E;
typedef enum ITGT_TARGET_TYPE //TARGET 目标类型
{
	TARGET_FACE_HUMAN_RECT = 0x00,  // 人脸人体检测框
	TARGET_FACE_DT_PROCESS = 0x01,  // 人脸后处理数据，发送抠图
	TARGET_FACE_RECOGNITION = 0x02,  // 人脸识别
	TARGET_MMC_FACE_PRE_PROCESS = 0x03,  // 多机协同人脸检测到的抠图和算法配置参数 对内使用
	TARGET_MMC_FACE_RECOG = 0x04,  // 多机协同人脸识别 对内使用
	TARGET_IBALL_VEHICLE_DT = 0x05,  // 违章球车辆检测

	TARGET_HUMANBODY = 0x06,  // 机非人业务人体信息
	TARGET_VHD_VEHICLE = 0x07,  // 机非人业务机动车信息
	TARGET_VHD_NOMOTOR = 0x08,  // 机非人非机动车信息

	TARGET_VEHICLE_RECT = 0x09,  // 车检测框
	TARGET_NOMOTOR_RECT = 0x0a,  // 非机动车检测框

	TARGET_HOTMAP = 0x0b,  // 热度图
	TARGET_CROWD_DENSITY = 0x0c,  // 人群密度
	TARGET_QUEUING_LENGTH = 0x0d,  // 排队长度
	TARGET_BEGAVIOR = 0x0e,  // 行为分析
	TARGET_HUMANCOUNT = 0x0f,  // 过线计数
	TARGET_HUMANCOUNT_REAL = 0x07000023,

	TARGET_AUTOTRACK = 0x10,  //自动跟踪
	TARGET_CARDETECTION = 0x11,  //停车侦测

	TARGET_ITS_PROCESS = 0x30,  // ITS
	TARGET_ITS_STATISTICS = 0x31,  // ITS车流量统计
	TARGET_ITS_OBJ_DT = 0x32,  // 交通产品目标检测框

	TARGET_VLPR_PROCESS = 0x33,  // 微卡口
	TARGET_VLPR_STATISTICS = 0x34,  // 微卡口车流量统计

	TARGET_RECT = 0x60,     // 目标框信息，用于实时显示

	TARGET_KEEPALIVE = 0x80,     // 元数据保活
	TARGET_MAX,
}ITGT_TARGET_TYPE_E;

#define LEN_MID 5 
#define LEN_MIN 10  
#define LEN_MAX 15
#define LEN_MAXMAX 20
#define LEN_LMAX 60
#define REALPLAYINFO 8000

static int real_time_people_in = 0, real_time_people_out = 0;
/////////////////////////////////////////////////////////////////////////

void AnalysisMetaDataTarget(PU_META_DATA* pstMetaTargetData)
{
	PU_UserData* pstMetaUserData = pstMetaTargetData->pstMetaUserData;
	if (NULL == pstMetaUserData)
	{ 
		return;
	}


	for (int uIndex = 0; uIndex < pstMetaTargetData->usValidNumber; uIndex++)
	{
		switch (pstMetaUserData[uIndex].eType)
		{
		case HUMAN_COUNT_IN:
		{			
			real_time_people_in += pstMetaUserData[uIndex].unMetaData.IntValue;
			/*wxString msg;
			msg.Printf(wxT("the value is %d"), pstMetaUserData[uIndex].unMetaData.IntValue);
			wxMessageBox(msg);*/
		}
		break;
		case HUMAN_COUNT_OUT:
		{
			real_time_people_out += pstMetaUserData[uIndex].unMetaData.IntValue;
			//wxMessageBox(wxT("OK"));
		}
		break;
		default:
			break;
		}
	}
}
static void	CALLBACK SnapCallbackWithMetaFrameDlg(char* szBuffer, long lsize, void* pdata)
{
	if (NULL == szBuffer || 0 == lsize)
	{
		return;
	}

	PU_META_DATA* pstMetaTargetData = { 0 };
	BOOL bRet = IVS_User_GetMetaData(szBuffer, lsize, TARGET, &pstMetaTargetData);
	if ((bRet == PU_TRUE) && (pstMetaTargetData != NULL))
	{
		//wxMessageBox(wxT("get target meta data succeed!"));
		AnalysisMetaDataTarget(pstMetaTargetData);
		IVS_User_FreeMetaData(&pstMetaTargetData);
	}
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) :
	wxFrame(parent, id, title, pos, size, style),
	m_timer(this, TIMER_UPDATE_ID),
	m_alarm_timer(this, TIMER_ALARM_ID)
{

#pragma region GUI

	this->SetSizeHints(wxSize(800, 600), wxDefaultSize);
	this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));

	m_menu_bar = new wxMenuBar(0);
	m_menu_bar->SetBackgroundColour(wxColor(0,0,0));

	m_menu = new wxMenu();
	wxMenuItem* m_alarm_duration;
	m_alarm_duration = new wxMenuItem(m_menu, ALARM_DURARION_ID, wxString(wxT("设置报警时长")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_alarm_duration);

	wxMenuItem* m_alarm_interval;
	m_alarm_interval = new wxMenuItem(m_menu, ALARM_INTERVAL_ID, wxString(wxT("设置报警间隔")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_alarm_interval);

	wxMenuItem* m_set_people_num;
	m_set_people_num = new wxMenuItem(m_menu, SET_PEOPLE_NUM_ID, wxString(wxT("设置工房定员")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_set_people_num);

	wxMenuItem* m_connect_camera = new wxMenuItem(m_menu, CONNECT_CAMERA_ID, wxString(wxT("连接摄像头")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_connect_camera);

	wxMenuItem* m_disconnect_camera = new wxMenuItem(m_menu, DISCONNECT_CAMERA_ID, wxString(wxT("断开摄像头")), wxEmptyString, wxITEM_NORMAL);
	m_menu->Append(m_disconnect_camera);

	m_menu_bar->Append(m_menu, wxT("菜单"));
	

	this->SetMenuBar(m_menu_bar);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	m_panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	left_container = new wxFlexGridSizer(1, 3, 0, 0);
	left_container->SetFlexibleDirection(wxBOTH);
	left_container->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_panel_left_left = new wxPanel(m_panel_left, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_staticText3 = new wxStaticText(m_panel_left_left, wxID_ANY, wxT("工房定员"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	m_staticText3->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer1->Add(m_staticText3, 0, wxALL, 5);

	m_staticText4 = new wxStaticText(m_panel_left_left, wxID_ANY, wxT("实际人数"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	m_staticText4->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer1->Add(m_staticText4, 0, wxALL, 5);

	m_staticText5 = new wxStaticText(m_panel_left_left, wxID_ANY, wxT("限进人数"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	m_staticText5->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer1->Add(m_staticText5, 0, wxALL, 5);


	m_panel_left_left->SetSizer(bSizer1);
	m_panel_left_left->Layout();
	bSizer1->Fit(m_panel_left_left);
	left_container->Add(m_panel_left_left, 1, wxEXPAND | wxALL, 5);

	m_panel_left_median = new wxPanel(m_panel_left, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	m_people_num = new wxStaticText(m_panel_left_median, wxID_ANY, wxT("42"), wxDefaultPosition, wxDefaultSize, 0);
	m_people_num->Wrap(-1);
	m_people_num->SetForegroundColour(wxColour(0, 255, 0));

	bSizer2->Add(m_people_num, 0, wxALL, 5);

	m_exist_people = new wxStaticText(m_panel_left_median, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0);
	m_exist_people->Wrap(-1);
	m_exist_people->SetForegroundColour(wxColour(0, 255, 0));

	bSizer2->Add(m_exist_people, 0, wxALL, 5);

	m_available_people = new wxStaticText(m_panel_left_median, wxID_ANY, wxT("42"), wxDefaultPosition, wxDefaultSize, 0);
	m_available_people->Wrap(-1);
	m_available_people->SetForegroundColour(wxColour(0, 255, 0));

	bSizer2->Add(m_available_people, 0, wxALL, 5);


	m_panel_left_median->SetSizer(bSizer2);
	m_panel_left_median->Layout();
	bSizer2->Fit(m_panel_left_median);
	left_container->Add(m_panel_left_median, 1, wxEXPAND | wxALL, 5);

	m_panel_left_right = new wxPanel(m_panel_left, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	m_staticText9 = new wxStaticText(m_panel_left_right, wxID_ANY, wxT("人"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText9->Wrap(-1);
	m_staticText9->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer3->Add(m_staticText9, 0, wxALL, 5);

	m_staticText10 = new wxStaticText(m_panel_left_right, wxID_ANY, wxT("人"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	m_staticText10->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer3->Add(m_staticText10, 0, wxALL, 5);

	m_staticText11 = new wxStaticText(m_panel_left_right, wxID_ANY, wxT("人"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText11->Wrap(-1);
	m_staticText11->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer3->Add(m_staticText11, 0, wxALL, 5);


	m_panel_left_right->SetSizer(bSizer3);
	m_panel_left_right->Layout();
	bSizer3->Fit(m_panel_left_right);
	left_container->Add(m_panel_left_right, 1, wxEXPAND | wxALL, 5);


	m_panel_left->SetSizer(left_container);
	m_panel_left->Layout();
	left_container->Fit(m_panel_left);
	fgSizer1->Add(m_panel_left, 1, wxEXPAND | wxALL, 5);

	m_panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer(3, 1, 0, 0);
	fgSizer3->SetFlexibleDirection(wxBOTH);
	fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_panel_right_up = new wxPanel(m_panel_right, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer(1, 6, 0, 0);
	fgSizer4->SetFlexibleDirection(wxBOTH);
	fgSizer4->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_panel_years = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_years = new wxStaticText(m_panel_years, wxID_ANY, wxT("2021"), wxDefaultPosition, wxDefaultSize, 0);
	m_years->Wrap(-1);
	m_years->SetForegroundColour(wxColour(0, 255, 0));

	bSizer4->Add(m_years, 0, wxALL, 5);

	m_hours = new wxStaticText(m_panel_years, wxID_ANY, wxT("18"), wxDefaultPosition, wxDefaultSize, 0);
	m_hours->Wrap(-1);
	m_hours->SetForegroundColour(wxColour(0, 255, 0));

	bSizer4->Add(m_hours, 0, wxALIGN_RIGHT | wxALL, 5);


	m_panel_years->SetSizer(bSizer4);
	m_panel_years->Layout();
	bSizer4->Fit(m_panel_years);
	fgSizer4->Add(m_panel_years, 1, wxEXPAND | wxALL, 5);

	m_panel10 = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_staticText14 = new wxStaticText(m_panel10, wxID_ANY, wxT("年"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText14->Wrap(-1);
	m_staticText14->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer5->Add(m_staticText14, 0, wxALL, 5);

	m_staticText15 = new wxStaticText(m_panel10, wxID_ANY, wxT("时"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText15->Wrap(-1);
	m_staticText15->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer5->Add(m_staticText15, 0, wxALL, 5);


	m_panel10->SetSizer(bSizer5);
	m_panel10->Layout();
	bSizer5->Fit(m_panel10);
	fgSizer4->Add(m_panel10, 1, wxEXPAND | wxALL, 5);

	m_panel_months = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	m_months = new wxStaticText(m_panel_months, wxID_ANY, wxT("7"), wxDefaultPosition, wxDefaultSize, 0);
	m_months->Wrap(-1);
	m_months->SetForegroundColour(wxColour(0, 255, 0));

	bSizer6->Add(m_months, 0, wxALL | wxALIGN_RIGHT, 5);

	m_minutes = new wxStaticText(m_panel_months, wxID_ANY, wxT("6"), wxDefaultPosition, wxDefaultSize, 0);
	m_minutes->Wrap(-1);
	m_minutes->SetForegroundColour(wxColour(0, 255, 0));

	bSizer6->Add(m_minutes, 0, wxALL | wxALIGN_RIGHT, 5);


	m_panel_months->SetSizer(bSizer6);
	m_panel_months->Layout();
	bSizer6->Fit(m_panel_months);
	fgSizer4->Add(m_panel_months, 1, wxEXPAND | wxALL, 5);

	m_panel12 = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	m_staticText18 = new wxStaticText(m_panel12, wxID_ANY, wxT("月"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText18->Wrap(-1);
	m_staticText18->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer7->Add(m_staticText18, 0, wxALL | wxALIGN_RIGHT, 5);

	m_staticText19 = new wxStaticText(m_panel12, wxID_ANY, wxT("分"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText19->Wrap(-1);
	m_staticText19->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer7->Add(m_staticText19, 0, wxALL, 5);


	m_panel12->SetSizer(bSizer7);
	m_panel12->Layout();
	bSizer7->Fit(m_panel12);
	fgSizer4->Add(m_panel12, 1, wxEXPAND | wxALL, 5);

	m_panel_days = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	m_days = new wxStaticText(m_panel_days, wxID_ANY, wxT("12"), wxDefaultPosition, wxDefaultSize, 0);
	m_days->Wrap(-1);
	m_days->SetForegroundColour(wxColour(0, 255, 0));

	bSizer8->Add(m_days, 0, wxALL | wxALIGN_RIGHT, 5);

	m_seconds = new wxStaticText(m_panel_days, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0);
	m_seconds->Wrap(-1);
	m_seconds->SetForegroundColour(wxColour(0, 255, 0));

	bSizer8->Add(m_seconds, 0, wxALL | wxALIGN_RIGHT, 5);


	m_panel_days->SetSizer(bSizer8);
	m_panel_days->Layout();
	bSizer8->Fit(m_panel_days);
	fgSizer4->Add(m_panel_days, 1, wxEXPAND | wxALL, 5);

	m_panel14 = new wxPanel(m_panel_right_up, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	m_staticText22 = new wxStaticText(m_panel14, wxID_ANY, wxT("日"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText22->Wrap(-1);
	m_staticText22->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer9->Add(m_staticText22, 0, wxALL, 5);

	m_staticText23 = new wxStaticText(m_panel14, wxID_ANY, wxT("秒"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText23->Wrap(-1);
	m_staticText23->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	bSizer9->Add(m_staticText23, 0, wxALL, 5);


	m_panel14->SetSizer(bSizer9);
	m_panel14->Layout();
	bSizer9->Fit(m_panel14);
	fgSizer4->Add(m_panel14, 1, wxEXPAND | wxALL, 5);


	m_panel_right_up->SetSizer(fgSizer4);
	m_panel_right_up->Layout();
	fgSizer4->Fit(m_panel_right_up);
	fgSizer3->Add(m_panel_right_up, 1, wxEXPAND | wxALL, 5);

	m_panel_right_down = new wxPanel(m_panel_right, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer5->SetFlexibleDirection(wxBOTH);
	fgSizer5->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_panel17 = new wxPanel(m_panel_right_down, wxID_ANY, wxDefaultPosition, wxSize(-1, 200), wxTAB_TRAVERSAL);
	fgSizer5->Add(m_panel17, 1, wxEXPAND | wxALL, 5);

	m_panel18 = new wxPanel(m_panel_right_down, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxWrapSizer* wSizer1;
	wSizer1 = new wxWrapSizer(wxHORIZONTAL, wxWRAPSIZER_DEFAULT_FLAGS);

	m_rooms = new wxStaticText(m_panel18, wxID_ANY, wxT("301"), wxDefaultPosition, wxDefaultSize, 0);
	m_rooms->Wrap(1);
	m_rooms->SetForegroundColour(wxColour(255, 0, 0));
	m_rooms->SetFont(wxFont(150, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false));
	m_rooms->SetWindowStyle(wxALIGN_RIGHT);
	wSizer1->Add(m_rooms, 0, wxALL | wxALIGN_RIGHT, 5);


	m_panel18->SetSizer(wSizer1);
	m_panel18->Layout();
	wSizer1->Fit(m_panel18);
	fgSizer5->Add(m_panel18, 1, wxEXPAND | wxALL, 5);


	m_panel_right_down->SetSizer(fgSizer5);
	m_panel_right_down->Layout();
	fgSizer5->Fit(m_panel_right_down);
	fgSizer3->Add(m_panel_right_down, 1, wxEXPAND | wxALL, 5);


	m_panel_right->SetSizer(fgSizer3);
	m_panel_right->Layout();
	fgSizer3->Fit(m_panel_right);
	fgSizer1->Add(m_panel_right, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(fgSizer1);
	this->Layout();

	this->Centre(wxBOTH);
#pragma endregion
	
	m_data.people_in = 0;
	m_data.people_out = 0;
	m_data.alarm_duration = 2;
	m_data.alarm_interval = 3;

	m_userID = 0;
	// push all static text on left side  into people_text vector
	people_text.push_back(m_staticText3);
	people_text.push_back(m_staticText4);
	people_text.push_back(m_staticText5);
	people_text.push_back(m_people_num);
	people_text.push_back(m_exist_people);
	people_text.push_back(m_available_people);
	people_text.push_back(m_staticText9);
	people_text.push_back(m_staticText10);
	people_text.push_back(m_staticText11);
	// push all static text on right up into time_text vector
	time_text.push_back(m_years);
	time_text.push_back(m_months); 
	time_text.push_back(m_days);
	time_text.push_back(m_hours);
	time_text.push_back(m_minutes);
	time_text.push_back(m_seconds);
	time_text.push_back(m_staticText14);
	time_text.push_back(m_staticText15);
	time_text.push_back(m_staticText18);
	time_text.push_back(m_staticText19);
	time_text.push_back(m_staticText22);
	time_text.push_back(m_staticText23);

	m_timer.Start(1000);
	m_alarm_timer.Start(2000);
}

MainFrame::~MainFrame()
{
}

// camera manipulation methds
bool MainFrame::InitSDK() {
	bool isInit = IVS_PU_Init(3, NULL, 5050);
	if (!isInit)
	{
		return false;
	}
	return true;
}
bool MainFrame::DeviceLogin() {
	CHAR m_IP[] = "192.168.0.120";
	ULONG strPort = 6060;
	CHAR strUser[] = "admin";
	CHAR strPwd[] = "HuaWei123";

	m_userID = IVS_PU_Login(m_IP, strPort, strUser, strPwd);
	if (PU_FALSE == m_userID)
	{
	/*	long RetErro = IVS_PU_GetLastError();
		wxString msg;
		msg.Printf(wxT("DeviceLogin   提示: 错误码是%d,错误信息是%d"), RetErro, IVS_PU_GetErrorMsg(RetErro));
		wxMessageBox(msg);*/
		return false;
	}

	//  设置断网重连
	if (PU_FALSE == IVS_PU_SetAutoReconnect(1))
	{
		//long RetErro = IVS_PU_GetLastError();
		//wxString msg;
		//msg.Printf(wxT("提示: 错误码是%d,错误信息是%d"), RetErro, IVS_PU_GetErrorMsg(RetErro));
		//wxMessageBox(msg);
		return false;
	}
	return true;
}
bool MainFrame::DeviceLogout(){
	bool b_Ret = IVS_PU_Logout(m_userID);
	if (!b_Ret)
	{
		ULONG RetErro = IVS_PU_GetLastError();
		wxString msg;
		msg.Printf(wxT("DeviceLogout  提示: 错误码是%d,错误信息是%d"), RetErro, IVS_PU_GetErrorMsg(RetErro));
		wxMessageBox(msg);
		return false;
	}
	return true;
}
bool MainFrame::ClearSDK() {
	if (IVS_PU_Cleanup()) {
		return true;
	}
	return false;
}
bool MainFrame::GetHunmanCountTable() {

	PU_HUMANCOUNT_ALG_PARAM_S human_param;
	human_param.enHCEnable = true;
	human_param.enOSDEnable = true;
	human_param.enClearAtZero = true;
	   BOOL bResult = PU_FALSE;
       ULONG ulError = 0;
       PU_HUMANCOUNT_TABLE_S stPara;
       memset(&stPara, 0, sizeof(stPara));
 
       stPara.ulChannelId = 101;
       stPara.enTableType = PU_TABLE_DAY; //日报表
       ULONG t = (ULONG) wxDateTime().GetTimeNow() - m_today_time + 8*3600;   //获取当天开始时间
       for (int i = 0; i < 24; i++) 
       {
		   ULONG skip_time = 3600;
           stPara.astTable[i].ulStartTime = (ULONG)t;
           stPara.astTable[i].ulEndTime = (ULONG)t + skip_time;
           t += skip_time;
       }

	   // clockwise direction people detected
	   stPara.enInDir = PU_TRIPWIRE_CLOCKWISE;//进入方向
       ulError = IVS_PU_GetHumanCountTable(m_userID, &stPara);
       if (PU_TRUE != ulError)
       {
			  return false;
       }
       else
       {
              ULONG n = 0;
			  for (int i = 0; i < 24; i++)
              {
                     if (stPara.astTable[i].HumanNum != 0) {
                           n += stPara.astTable[i].HumanNum;
                     }
              }
			  m_data.people_in = n;

       }

	   // unti-clockwise direction people 
	   stPara.enInDir = PU_TRIPWIRE_ANTICLOCKWISE;//进入方向
	   ulError = IVS_PU_GetHumanCountTable(m_userID, &stPara);
	   if (PU_TRUE != ulError)
	   {
		   return false;
	   }
	   else
	   {
		   ULONG n = 0;
		   for (int i = 0; i < 24; i++)
		   {
			   if (stPara.astTable[i].HumanNum != 0) {
				   n += stPara.astTable[i].HumanNum;
			   }
		   }
		   m_data.people_out = n;
	   }
}
bool MainFrame::StartSnap()
{
	PU_REAL_PLAY_INFO_S stRealPlayInfo;
	memset(&stRealPlayInfo, 0, sizeof(PU_REAL_PLAY_INFO_S));

	stRealPlayInfo.ulChannelId = 101;

	stRealPlayInfo.enProtocolType = PU_PROTOCOL_TYPE_TCP;
	stRealPlayInfo.enStreamType = PU_VIDEO_MAIN_STREAM;
	stRealPlayInfo.bKeepLive = PU_TRUE;
	stRealPlayInfo.enMediaCallbackType = PU_MEDIA_CALLBACK_TYPE_META_FRAME;
	stRealPlayInfo.enMediaCryptoType = PU_MEDIA_CRYPTO_NONE;
	stRealPlayInfo.enVideoType = PU_VIDEO_TYPE_META;
	stRealPlayInfo.szReserved[22] = '1';

	auto m_ulRetRelPlay = IVS_PU_RealPlay(m_userID, &stRealPlayInfo, SnapCallbackWithMetaFrameDlg, NULL);
	if (PU_FALSE == m_ulRetRelPlay)
	{
		auto error_code = IVS_PU_GetLastError();
		wxString msg;
		msg.Printf(wxT("StartSnap failed: error code is %d"), error_code);
		wxMessageBox(msg);
		return false;
	}
	else
	{
		wxMessageBox(wxString(wxT("StartSnap succeed!")));
		return true;
	}
}
bool MainFrame::StopSnap()
{
	BOOL ulRet = IVS_PU_StopRealPlay(m_userID, 0);
	if (PU_FALSE == ulRet)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// event handler methods
void MainFrame::OnUpdateWindow(wxTimerEvent& event) {
	wxDateTime date(wxDateTime::Now());

	auto year = date.GetCurrentYear();
	auto months = date.GetMonth();
	auto days = date.GetDay();
	auto hours = date.GetHour();
	auto minutes = date.GetMinute();
	auto seconds = date.GetSecond();

	m_today_time = hours * 60 * 60 + minutes * 60 + seconds;
	m_years->SetLabelText(wxString(std::to_string(year)));
	m_months->SetLabelText(wxString(std::to_string(months + 1)));
	m_days->SetLabelText(wxString(std::to_string(days)));
	m_hours->SetLabelText(wxString(std::to_string(hours)));
	if (minutes < 10) {
		wxString str = "0";
		str.append(std::to_string(minutes));
		m_seconds->SetLabelText(str);
	}
	else
	{
		m_minutes->SetLabelText(wxString(std::to_string(minutes)));
	}

	if (seconds < 10) {
		wxString sec_str = "0";
		sec_str.append(std::to_string(seconds));
		m_seconds->SetLabelText(sec_str);
	}
	else
	{
		m_seconds->SetLabelText(wxString(std::to_string(seconds)));
	}


	if (FLAG_IS_CAMERA_ON) {
		m_data.people_in = real_time_people_in;
		m_data.people_out = real_time_people_out;
		ULONG people_in = m_data.people_in, people_out = m_data.people_out;
		ULONG existed_people = people_in - people_out;
		long total_people;
		m_people_num->GetLabelText().ToLong(&total_people);

		ULONG available_people = (ULONG) total_people - existed_people;
		if (available_people < 0) available_people = 0;
		m_exist_people->SetLabelText(wxString(std::to_string(existed_people)));
		m_available_people->SetLabelText(wxString(std::to_string(available_people)));
		(long) existed_people > total_people ? FLAG_IS_PEOPLE_FULL = true : FLAG_IS_PEOPLE_FULL = false;
	}
}
void MainFrame::OnAlarmBeepSound(wxTimerEvent& event) {
	if(FLAG_IS_PEOPLE_FULL) Beep(2200, m_data.alarm_duration * 1000);
}
void MainFrame::OnResizeWindow(wxSizeEvent& event) {
	wxSize size = event.GetSize();
	int g_width = size.GetWidth();
	int g_height = size.GetHeight();

	// resize left size fonts
	for (decltype(people_text.size()) i = 0; i < people_text.size(); ++i) {
		wxStaticText& text = *people_text[i];
		wxFont font = wxFont(10 + g_width / 16.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
		text.SetFont(font);
	
		// left side deployment
		if (i < 3) {
			text.SetMinSize(wxSize(g_width * 12 / 25, g_height / 3));
		}
		else {
			text.SetMinSize(wxSize(g_width * 2.5 / 25, g_height / 3));
		}
		text.SetWindowStyle(wxALIGN_CENTER_HORIZONTAL);
	}
	// resize right side fonts
	for (decltype(time_text.size()) i = 0; i < time_text.size(); ++i){
		wxStaticText& text = *time_text[i];
		wxFont font = wxFont(34, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
		text.SetFont(font);
		//text.SetMinSize(wxSize(100, g_height / 12));
		text.SetWindowStyle(wxALIGN_RIGHT);
	}

	event.Skip();
}
void MainFrame::OnSetPeopleNum(wxCommandEvent& event) {
	long value;
	wxNumberEntryDialog dialog(this,
		wxT("设置在岗人数( 默认为42)\n 输入值不得小于0 或 大于999"),
		wxT("输入数字 : "), wxT("在岗人数"), 0, 0, 999);
	if (dialog.ShowModal() == wxID_OK)
	{
		 value = dialog.GetValue();
		 m_people_num->SetLabelText(wxString(std::to_string(value)));
	}
}
void MainFrame::OnAlarmDuration(wxCommandEvent& event){
	long value;
	wxNumberEntryDialog dialog(this,
		wxT("设置报警时长（单位：秒）：默认为2秒\n 输入值不得小于0或大于999"),
		wxT("输入数字 : "), wxT("报警时长"), 0, 0, 999);
	if (dialog.ShowModal() == wxID_OK)
	{
		value = dialog.GetValue();
		m_data.alarm_duration = value;
	}
}
void MainFrame::OnAlarmInterval(wxCommandEvent& event) {
	long value;
	wxNumberEntryDialog dialog(this,
		wxT("设置报警间隔（单位：秒）：默认为3秒\n 输入值不得小于0或大于999"),
		wxT("输入数字 : "), wxT("报警间隔"), 0, 0, 999);
	if (dialog.ShowModal() == wxID_OK)
	{
		value = dialog.GetValue();
		m_data.alarm_interval = value;
	}
	m_alarm_timer.Start(m_data.alarm_interval * 1000);
}
void MainFrame::OnConnectCamera(wxCommandEvent& event) {

	if (FLAG_IS_CAMERA_ON) {
		wxString msg;
		msg.Printf(wxT("提示：摄像头已连接，请勿重复操作！"));
		wxMessageBox(msg);
		return;
	}

	if (InitSDK() && DeviceLogin()) {
		FLAG_IS_CAMERA_ON = true;
		while (!StartSnap()) {}
		wxString msg;
		msg.Printf(wxT("提示：摄像头连接成功！"));
		wxMessageBox(msg);
	}
	else {
		ClearSDK();
		wxString msg;
		msg.Printf(wxT("错误: 摄像头连接失败\n 提示：请检查网络连接"));
		wxMessageBox(msg);
	}
}
void MainFrame::OnDisconnectCamera(wxCommandEvent& event){
	
	StopSnap();

	if (!FLAG_IS_CAMERA_ON) {
		wxString msg;
		msg.Printf(wxT("提示：摄像头已断开，请勿重复操作！"));
		wxMessageBox(msg);
		return;
	}
	else if (DeviceLogout() && ClearSDK()) {
		FLAG_IS_CAMERA_ON = false;
		wxString msg;
		msg.Printf(wxT("提示：摄像头断开成功！"));
		wxMessageBox(msg);
	}
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_SIZE(MainFrame::OnResizeWindow)
EVT_TIMER(TIMER_UPDATE_ID , MainFrame::OnUpdateWindow)
EVT_TIMER(TIMER_ALARM_ID, MainFrame::OnAlarmBeepSound)
EVT_MENU(SET_PEOPLE_NUM_ID, MainFrame::OnSetPeopleNum)
EVT_MENU(ALARM_DURARION_ID, MainFrame::OnAlarmDuration)
EVT_MENU(ALARM_INTERVAL_ID, MainFrame::OnAlarmInterval)
EVT_MENU(CONNECT_CAMERA_ID, MainFrame::OnConnectCamera)
EVT_MENU(DISCONNECT_CAMERA_ID, MainFrame::OnDisconnectCamera)
END_EVENT_TABLE()