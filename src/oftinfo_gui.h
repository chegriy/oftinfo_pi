///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/clrpicker.h>
#include <wx/statbox.h>
#include <wx/collpane.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/button.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class OFTinfoBase
///////////////////////////////////////////////////////////////////////////////
class OFTinfoBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticUnloadAreaAftTrig;
		wxStaticText* m_staticUnloadAreaBowTrig;
		wxStaticText* m_staticUnloadAreaAftTrig1;
		wxStaticText* m_staticUnloadAreaAftTrig21;
		wxStaticText* m_staticUnloadAreaLostTime;
		wxStaticText* m_staticUnloadAreaColourPicker;
		wxColourPickerCtrl* m_colourPickerUnloadArea;
		wxStaticText* m_staticOGVMMSI;
		wxStaticText* m_statiOGVName;
		wxStaticText* m_staticOGVLoadTime;
		wxStaticText* m_staticOGVMoorTime;
		wxStaticText* m_statiOGVUnMoorTime;
		wxStaticText* m_staticUnloadAreaLostTime2;
		wxStaticText* m_staticUnloadAreaAftTrig11;
		wxStaticText* m_staticUnloadAreaAftTrig211;
		wxCollapsiblePane* m_collapsiblePane1;
		wxStaticText* m_staticCraneAreaAftTrig;
		wxStaticText* m_staticCraneAreaBowTrig;
		wxStaticText* m_staticCraneAreaColorPicker;
		wxColourPickerCtrl* m_colourPickerCrane1Area;
		wxStaticText* m_staticCraneMMSI;
		wxStaticText* m_statiCraneName;
		wxStaticText* m_staticCraneLoadTime;
		wxStaticText* m_staticCraneMoorTime;
		wxStaticText* m_statiCraneUnMoorTime;
		wxCollapsiblePane* m_collapsiblePane2;
		wxStaticText* m_staticCraneAreaAftTrig1;
		wxStaticText* m_staticCraneAreaBowTrig1;
		wxStaticText* m_staticCraneAreaColorPicker1;
		wxColourPickerCtrl* m_colourPickerCrane2Area;
		wxStaticText* m_staticCraneMMSI1;
		wxStaticText* m_statiCraneName1;
		wxStaticText* m_staticCraneLoadTime1;
		wxStaticText* m_staticCraneMoorTime1;
		wxStaticText* m_statiCraneUnMoorTime1;
		wxCollapsiblePane* m_collapsiblePane3;
		wxStaticText* m_staticCraneAreaAftTrig2;
		wxStaticText* m_staticCraneAreaBowTrig2;
		wxStaticText* m_staticCraneAreaColorPicker2;
		wxColourPickerCtrl* m_colourPickerCrane3Area;
		wxStaticText* m_staticCraneMMSI2;
		wxStaticText* m_statiCraneName2;
		wxStaticText* m_staticCraneLoadTime2;
		wxStaticText* m_staticCraneMoorTime2;
		wxStaticText* m_statiCraneUnMoorTime2;
		wxCollapsiblePane* m_collapsiblePane4;
		wxStaticText* m_staticCraneAreaAftTrig3;
		wxStaticText* m_staticCraneAreaBowTrig3;
		wxStaticText* m_staticCraneAreaColorPicker3;
		wxColourPickerCtrl* m_colourPickerCrane4Area;
		wxStaticText* m_staticCraneMMSI3;
		wxStaticText* m_statiCraneName3;
		wxStaticText* m_staticCraneLoadTime3;
		wxStaticText* m_staticCraneMoorTime3;
		wxStaticText* m_statiCraneUnMoorTime3;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnDLeftClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxCheckBox* m_cbUnloadAreaEnable;
		wxCheckBox* m_cbUnloadAreaVisible;
		wxCheckBox* m_cbOGVDataVisible;
		wxCheckBox* m_cbUnloadAreaSTBD;
		wxCheckBox* m_cbUnloadAreaPORT;
		wxTextCtrl* m_textCtrlUnloadAreaAftTrig;
		wxTextCtrl* m_textCtrlUnloadAreaBowTrig;
		wxTextCtrl* m_textCtrlUnloadAreaHist;
		wxTextCtrl* m_textCtrlUnloadAreaDistance;
		wxTextCtrl* m_textCtrlUnloadAreaLostTime;
		wxTextCtrl* m_textCtrlOGVMMSI;
		wxTextCtrl* m_textCtrlOGVName;
		wxTextCtrl* m_textCtrlOGVLoadTime;
		wxTextCtrl* m_textCtrlOGVMoorTime;
		wxTextCtrl* m_textCtrlOGVUnMoorTime;
		wxTextCtrl* m_textCtrlLoadAreaLostTime;
		wxTextCtrl* m_textCtrlLoadAreaHist;
		wxTextCtrl* m_textCtrlLoadAreaDistance;
		wxCheckBox* m_cbCrane1AreaEnable;
		wxCheckBox* m_cbCrane1AreaVisible;
		wxCheckBox* m_cbCrane1BargeDataVisible;
		wxTextCtrl* m_textCtrlCrane1AreaAftTrig;
		wxTextCtrl* m_textCtrlCrane1AreaBowTrig;
		wxTextCtrl* m_textCtrlCrane1MMSI;
		wxTextCtrl* m_textCtrlCrane1Name;
		wxTextCtrl* m_textCtrlCrane1LoadTime;
		wxTextCtrl* m_textCtrlCrane1MoorTime;
		wxTextCtrl* m_textCtrlCrane1UnMoorTime;
		wxCheckBox* m_cbCrane2AreaEnable;
		wxCheckBox* m_cbCrane2AreaVisible;
		wxCheckBox* m_cbCrane2BargeDataVisible;
		wxTextCtrl* m_textCtrlCrane2AreaAftTrig;
		wxTextCtrl* m_textCtrlCrane2AreaBowTrig;
		wxTextCtrl* m_textCtrlCrane2MMSI;
		wxTextCtrl* m_textCtrlCrane2Name;
		wxTextCtrl* m_textCtrlCrane2LoadTime;
		wxTextCtrl* m_textCtrlCrane2MoorTime;
		wxTextCtrl* m_textCtrlCrane2UnMoorTime;
		wxCheckBox* m_cbCrane3AreaEnable;
		wxCheckBox* m_cbCrane3AreaVisible;
		wxCheckBox* m_cbCrane3BargeDataVisible;
		wxTextCtrl* m_textCtrlCrane3AreaAftTrig;
		wxTextCtrl* m_textCtrlCrane3AreaBowTrig;
		wxTextCtrl* m_textCtrlCrane3MMSI;
		wxTextCtrl* m_textCtrlCrane3Name;
		wxTextCtrl* m_textCtrlCrane3LoadTime;
		wxTextCtrl* m_textCtrlCrane3MoorTime;
		wxTextCtrl* m_textCtrlCrane3UnMoorTime;
		wxCheckBox* m_cbCrane4AreaEnable;
		wxCheckBox* m_cbCrane4AreaVisible;
		wxCheckBox* m_cbCrane4BargeDataVisible;
		wxTextCtrl* m_textCtrlCrane4AreaAftTrig;
		wxTextCtrl* m_textCtrlCrane4AreaBowTrig;
		wxTextCtrl* m_textCtrlCrane4MMSI;
		wxTextCtrl* m_textCtrlCrane4Name;
		wxTextCtrl* m_textCtrlCrane4LoadTime;
		wxTextCtrl* m_textCtrlCrane4MoorTime;
		wxTextCtrl* m_textCtrlCrane4UnMoorTime;
		wxTimer m_timer;

		OFTinfoBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 886,936 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~OFTinfoBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class oftinfoPreferences
///////////////////////////////////////////////////////////////////////////////
class oftinfoPreferences : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText82;
		wxStaticText* m_staticText821;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText81;
		wxStaticText* m_staticText822;
		wxStaticText* m_staticText8221;
		wxStaticText* m_staticText82211;
		wxStaticText* m_staticText822111;
		wxStaticText* m_staticText8221111;
		wxStaticText* m_staticText82211111;
		wxStaticText* m_staticText822111111;
		wxStaticText* m_staticText8222;
		wxStaticText* m_staticText82212;
		wxStaticText* m_staticText8221112;
		wxStaticText* m_staticText82211112;
		wxStaticText* m_staticText822111112;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

	public:
		wxCheckBox* m_cbAisToFile;
		wxCheckBox* m_cbAisToMQTT;
		wxCheckBox* m_cbAisToPSQL;
		wxTextCtrl* m_textCtrlAISTransPeriod;
		wxCheckBox* m_cbAISTargCargoOnly;
		wxCheckBox* m_cbAISTargZeroInc;
		wxTextCtrl* m_textCtrlOwnMMSI;
		wxCheckBox* m_cbAISTransmitAIVDO;
		wxTextCtrl* m_textCtrlOFTMMSI1;
		wxTextCtrl* m_textCtrlOFTMMSI2;
		wxCheckBox* m_cbMonToFile;
		wxCheckBox* m_cbMonToMQTT;
		wxCheckBox* m_cbMonToPSQL;
		wxTextCtrl* m_textCtrlMonTransPeriod;
		wxTextCtrl* m_textCtrlAisFileName;
		wxTextCtrl* m_textCtrlAISFilePath;
		wxTextCtrl* m_textCtrlMQTTBrokerIP;
		wxTextCtrl* m_textCtrlMQTTBrokerPort;
		wxTextCtrl* m_textCtrlMQTTclientID;
		wxTextCtrl* m_textCtrlMQTTuser;
		wxTextCtrl* m_textCtrlMQTTpassw;
		wxTextCtrl* m_textCtrlMQTTPublishTopic;
		wxTextCtrl* m_textCtrlMQTTSubscribeTopic;
		wxTextCtrl* m_textCtrlSQLip;
		wxTextCtrl* m_textCtrlSQLport;
		wxTextCtrl* m_textCtrlSQLuser;
		wxTextCtrl* m_textCtrlSQLpassw;
		wxTextCtrl* m_textCtrlSQLDBName;

		oftinfoPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1061,667 ), long style = wxCAPTION|wxRESIZE_BORDER );

		~oftinfoPreferences();

};

