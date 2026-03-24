/***************************************************************************
 *
 * Project:  OpenCPN  Forked from ShipDriver Mike Rossiter Plugin
 * Purpose:  OFTinfo Plugin
 * Author:   Grigorii Chumakin
 ***************************************************************************
 *   Copyright (C) 2026 by Grigorii Chumakin                               *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   Vlasiha station, Barnaul, PC  656040, RUS.                            *
 ***************************************************************************
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "config.h"
#include "icons.h"
#include "oftinfo_pi.h"
#include "oftinfo_gui.h"
#include "oftinfo_gui_impl.h"
#include "ocpn_plugin.h"
#include "plug_utils.h"

class Dlg;

using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr) {
  return new OFTinfoPi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }

//---------------------------------------------------------------------------------------------------------
//
//    OFTinfo PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

OFTinfoPi::OFTinfoPi(void* ppimgr)
    : opencpn_plugin_118(ppimgr),
      wxTimer(this),
      m_hr_dialog_x(0),
      m_hr_dialog_y(8),
     // m_cursor_lat(0),
     // m_cursor_lon(0),
      m_position_menu_id(-1),
      m_gui_scale_factor(1),
      plugin(nullptr),
      m_dialog(nullptr),
      m_config(nullptr),
      m_parent_window(nullptr),
      m_hr_dialog_width(0),
      m_hr_dialog_height(0),
      m_hr_dialog_sx(0),
      m_hr_dialog_sy(0),
      m_display_width(0),
      m_display_height(0),
      m_leftclick_tool_id(-1),
      m_show_oftinfo_icon(false)
      //m_AIS_Array(*GetAISTargetArray())
     //may be need add preference variable?? gr!!!
{
  // Create the PlugIn icons
  initialize_images();
  auto icon_path = GetPluginIcon("oftinfo_panel_icon", PKG_NAME);
  if (icon_path.type == IconPath::Type::Svg)
    m_panel_bitmap = LoadSvgIcon(icon_path.path.c_str());
  else if (icon_path.type == IconPath::Type::Png)
    m_panel_bitmap = LoadPngIcon(icon_path.path.c_str());
  else  // icon_path.type == NotFound
    wxLogWarning("Cannot find icon for basename: %s", "oftinfo_panel_icon");
  if (m_panel_bitmap.IsOk())
    wxLogDebug("OFTinfoPi::, bitmap OK");
  else
    wxLogDebug("OFTinfoPi::, bitmap fail");
  m_show_oftinfo = false;
}

OFTinfoPi::~OFTinfoPi() {
  delete _img_OFTinfoIcon;

  if (m_dialog) {
    wxFileConfig* pConf = GetOCPNConfigObject();

    if (pConf) {
      // AIS Targets
      pConf->Write("oftinfoAisToFile", m_copy_AisToFile);
      pConf->Write("oftinfoAisToMQTT", m_copy_AisToMQTT);
      pConf->Write("oftinfoAisToPSQL", m_copy_AisToPSQL);
      pConf->Write("oftinfoAISTransPeriod", m_copy_AISTransPeriod);
      // Target filter
      pConf->Write("oftinfoAISTargCargoOnly", m_copy_AISTargCargoOnly);
      pConf->Write("oftinfoAISTargZeroInc", m_copy_AISTargZeroInc);
      // Own Ship
      pConf->Write("oftinfoOwnMMSI", m_copy_OwnMMSI);
      pConf->Write("oftinfoAISTransmitAIVDO", m_copy_AISTransmitAIVDO);
      // OFT
      pConf->Write("oftinfoOFTMMSI1", m_copy_OFTMMSI1);
      pConf->Write("oftinfoOFTMMSI2", m_copy_OFTMMSI2);
      // load areas
      pConf->Write("oftinfoMonToFile", m_copy_MonToFile);
      pConf->Write("oftinfoMonToMQTT", m_copy_MonToMQTT);
      pConf->Write("oftinfoMonToPSQ", m_copy_MonToPSQL);
      pConf->Write("oftinfoMonTransPeriod", m_copy_MonTransPeriod);
      // file
      pConf->Write("oftinfoAisFileName", m_copy_AisFileName);
      pConf->Write("oftinfoAISFilePath", m_copy_AISFilePath);
      // MQTT
      pConf->Write("oftinfoMQTTBrokerIP", m_copy_MQTTBrokerIP);
      pConf->Write("oftinfoMQTTBrokerPort", m_copy_MQTTBrokerPort);
      pConf->Write("oftinfoMQTTclientID", m_copy_MQTTclientID);
      pConf->Write("oftinfoMQTTuser", m_copy_MQTTuser);
      pConf->Write("oftinfoMQTTpassw", m_copy_MQTTpassw);
      pConf->Write("oftinfoMQTTPublishTopic", m_copy_MQTTPublishTopic);
      pConf->Write("oftinfoMQTTSubscribeTopic", m_copy_MQTTSubscribeTopic);
      // Postgresql
      pConf->Write("oftinfoSQLip", m_copy_SQLip);
      pConf->Write("oftinfoSQLport", m_copy_SQLport);
      pConf->Write("oftinfoSQLuser", m_copy_SQLuser);
      pConf->Write("oftinfoSQLpassw", m_copy_SQLpassw);
      pConf->Write("oftinfoSQLDBName", m_copy_SQLDBName);

      // base dialog
      // Unload Area
      pConf->Write("oftinfoUnloadAreaEnable", m_copy_UnloadAreaEnable);
      pConf->Write("oftinfoUnloadAreaVisible", m_copy_UnloadAreaVisible);
      pConf->Write("oftinfoOGVDataVisible", m_copy_OGVDataVisible);
      pConf->Write("oftinfoUnloadAreaSTBD", m_copy_UnloadAreaSTBD);
      pConf->Write("oftinfoUnloadAreaPORT", m_copy_UnloadAreaPORT);
      pConf->Write("oftinfoUnloadAreaAftTrig", m_copy_UnloadAreaAftTrig);
      pConf->Write("oftinfoUnloadAreaBowTrig", m_copy_UnloadAreaBowTrig);
      pConf->Write("oftinfoUnloadAreaHist", m_copy_UnloadAreaHist);
      pConf->Write("oftinfoUnloadAreaDistance", m_copy_UnloadAreaDistance);
      pConf->Write("oftinfoUnloadAreaLostTime", m_copy_UnloadAreaLostTime);
      m_copy_IntUnloadAreaColour = m_copy_UnloadAreaColour.GetRGB();  // red, green, blue
      pConf->Write("oftinfoUnloadAreaColour", m_copy_IntUnloadAreaColour);
      // OGV
      pConf->Write("oftinfoOGVMMSI", m_copy_OGVMMSI);
      pConf->Write("oftinfoOGVName", m_copy_OGVName);
      pConf->Write("oftinfoOGVLoadTime", m_copy_OGVLoadTime);
      pConf->Write("oftinfoOGVMoorTime", m_copy_OGVMoorTime);
      pConf->Write("oftinfoOGVUnMoorTime", m_copy_OGVUnMoorTime);
      // load Areas
      pConf->Write("oftinfoLoadAreaLostTime", m_copy_LoadAreaLostTime);
      pConf->Write("oftinfoLoadAreaHist", m_copy_LoadAreaHist);
      pConf->Write("oftinfoLoadAreaDistance", m_copy_LoadAreaDistance);
      // Crane 1
      pConf->Write("oftinfoCrane1AreaEnable", m_copy_Crane1AreaEnable);
      pConf->Write("oftinfoCrane1AreaVisible", m_copy_Crane1AreaVisible);
      pConf->Write("oftinfoCrane1BargeDataVisible", m_copy_Crane1BargeDataVisible);
      pConf->Write("oftinfoCrane1AreaAftTrig", m_copy_Crane1AreaAftTrig);
      pConf->Write("oftinfoCrane1AreaBowTrig", m_copy_Crane1AreaBowTrig);
      m_copy_IntCrane1AreaColour = m_copy_Crane1AreaColour.GetRGB();  // red, green, blue
      pConf->Write("oftinfoCrane1AreaColour", m_copy_IntCrane1AreaColour);
      // Crane 1 barge
      pConf->Write("oftinfoCrane1MMSI", m_copy_Crane1MMSI);
      pConf->Write("oftinfoCrane1Name", m_copy_Crane1Name);
      pConf->Write("oftinfoCrane1LoadTime", m_copy_Crane1LoadTime);
      pConf->Write("oftinfoCrane1MoorTime", m_copy_Crane1MoorTime);
      pConf->Write("oftinfoCrane1UnMoorTime", m_copy_Crane1UnMoorTime);
      // Crane 2
      pConf->Write("oftinfoCrane2AreaEnable", m_copy_Crane2AreaEnable);
      pConf->Write("oftinfoCrane2AreaVisible", m_copy_Crane2AreaVisible);
      pConf->Write("oftinfoCrane2BargeDataVisible", m_copy_Crane2BargeDataVisible);
      pConf->Write("oftinfoCrane2AreaAftTrig", m_copy_Crane2AreaAftTrig);
      pConf->Write("oftinfoCrane2AreaBowTrig", m_copy_Crane2AreaBowTrig);
      m_copy_IntCrane2AreaColour = m_copy_Crane2AreaColour.GetRGB();  // red, green, blue
      pConf->Write("oftinfoCrane2AreaColour", m_copy_IntCrane2AreaColour);
      // Crane 2 barge
      pConf->Write("oftinfoCrane2MMSI", m_copy_Crane2MMSI);
      pConf->Write("oftinfoCrane2Name", m_copy_Crane2Name);
      pConf->Write("oftinfoCrane2LoadTime", m_copy_Crane2LoadTime);
      pConf->Write("oftinfoCrane2MoorTime", m_copy_Crane2MoorTime);
      pConf->Write("oftinfoCrane2UnMoorTime", m_copy_Crane2UnMoorTime);
      // Crane 3
      pConf->Write("oftinfoCrane3AreaEnable", m_copy_Crane3AreaEnable);
      pConf->Write("oftinfoCrane3AreaVisible", m_copy_Crane3AreaVisible);
      pConf->Write("oftinfoCrane3BargeDataVisible", m_copy_Crane3BargeDataVisible);
      pConf->Write("oftinfoCrane3AreaAftTrig", m_copy_Crane3AreaAftTrig);
      pConf->Write("oftinfoCrane3AreaBowTrig", m_copy_Crane3AreaBowTrig);
      m_copy_IntCrane3AreaColour = m_copy_Crane3AreaColour.GetRGB();  // red, green, blue
      pConf->Write("oftinfoCrane3AreaColour", m_copy_IntCrane3AreaColour);
      // Crane 3 barge
      pConf->Write("oftinfoCrane3MMSI", m_copy_Crane3MMSI);
      pConf->Write("oftinfoCrane3Name", m_copy_Crane3Name);
      pConf->Write("oftinfoCrane3LoadTime", m_copy_Crane3LoadTime);
      pConf->Write("oftinfoCrane3MoorTime", m_copy_Crane3MoorTime);
      pConf->Write("oftinfoCrane3UnMoorTime", m_copy_Crane3UnMoorTime);
      // Crane 4
      pConf->Write("oftinfoCrane4AreaEnable", m_copy_Crane4AreaEnable);
      pConf->Write("oftinfoCrane4AreaVisible", m_copy_Crane4AreaVisible);
      pConf->Write("oftinfoCrane4BargeDataVisible", m_copy_Crane4BargeDataVisible);
      pConf->Write("oftinfoCrane4AreaAftTrig", m_copy_Crane4AreaAftTrig);
      pConf->Write("oftinfoCrane4AreaBowTrig", m_copy_Crane4AreaBowTrig);
      m_copy_IntCrane4AreaColour = m_copy_Crane4AreaColour.GetRGB();  // red, green, blue
      pConf->Write("oftinfoCrane4AreaColour", m_copy_IntCrane4AreaColour);
      // Crane 4 barge
      pConf->Write("oftinfoCrane4MMSI", m_copy_Crane4MMSI);
      pConf->Write("oftinfoCrane4Name", m_copy_Crane4Name);
      pConf->Write("oftinfoCrane4LoadTime", m_copy_Crane4LoadTime);
      pConf->Write("oftinfoCrane4MoorTime", m_copy_Crane4MoorTime);
      pConf->Write("oftinfoCrane4UnMoorTime", m_copy_Crane4UnMoorTime);
      
    }
  }
} //end of destructor

int OFTinfoPi::Init() {
  AddLocaleCatalog("opencpn-OFTinfo_pi");

  // Set some default private member parameters
  m_hr_dialog_x = 40;
  m_hr_dialog_y = 80;
  m_hr_dialog_sx = 400;
  m_hr_dialog_sy = 300;
  ::wxDisplaySize(&m_display_width, &m_display_height);

  //    Get a pointer to the opencpn display canvas, to use as a parent for
  //    the POI Manager dialog
  m_parent_window = GetOCPNCanvasWindow();

  //    Get a pointer to the opencpn configuration object
  m_config = GetOCPNConfigObject();

  //    And load the configuration items
  LoadConfig();
  auto icon = GetPluginIcon("oftinfo_pi", PKG_NAME);
  auto toggled_icon = GetPluginIcon("oftinfo_pi_toggled", PKG_NAME);
  //    This PlugIn needs a toolbar icon, so request its insertion
  if (m_show_oftinfo_icon) {
    if (icon.type == IconPath::Type::Svg)
      m_leftclick_tool_id = InsertPlugInToolSVG(
          "OFTinfo", icon.path, icon.path, toggled_icon.path, wxITEM_CHECK,
          "OFTinfo", "", nullptr, OFTinfo_TOOL_POSITION, 0, this);
    else if (icon.type == IconPath::Type::Png) {
      auto bitmap = LoadPngIcon(icon.path.c_str());
      m_leftclick_tool_id =
          InsertPlugInTool("", &bitmap, &bitmap, wxITEM_CHECK, "OFTinfo", "",
                           nullptr, OFTinfo_TOOL_POSITION, 0, this);
    }
  }
  m_dialog = nullptr;
  int AISTransPeriod = 0;
  m_copy_AISTransPeriod.ToInt(&AISTransPeriod, 10);
  DebugMessage = "Start with " + m_copy_AISTransPeriod + "sec";
  wxMessageBox(DebugMessage, "OFTinfo_Timer");
  Start(1000 * AISTransPeriod, wxTIMER_CONTINUOUS);  // start timer
  
  return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK |
          WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL |  WANTS_CURSOR_LATLON |
          WANTS_NMEA_SENTENCES | WANTS_AIS_SENTENCES | 
          WANTS_PREFERENCES |
          WANTS_PLUGIN_MESSAGING | WANTS_CONFIG);
}

bool OFTinfoPi::DeInit() {
  //    Record the dialog position
   if (m_dialog) {
    // Capture dialog position
    wxPoint p = m_dialog->GetPosition();
    wxRect r = m_dialog->GetRect();
    SetOFTinfoDialogX(p.x);
    SetOFTinfoDialogY(p.y);
    SetOFTinfoDialogSizeX(r.GetWidth());
    SetOFTinfoDialogSizeY(r.GetHeight());
    m_dialog->Close();
    delete m_dialog;
    m_dialog = nullptr;

    m_show_oftinfo = false;
    SetToolbarItemState(m_leftclick_tool_id, m_show_oftinfo);
  }
   if (IsRunning()) {
     //  need to stop the timer or crash on exit
     Stop(); // stop timer
   }
   // add other canceling action this (close file, MQTT and DB connection e.c.
  SaveConfig();
  RequestRefresh(m_parent_window);  // refresh main window
  return true;
}

int OFTinfoPi::GetAPIVersionMajor() { return atoi(API_VERSION); }

int OFTinfoPi::GetAPIVersionMinor() {
  std::string v(API_VERSION);
  size_t dotpos = v.find('.');
  return atoi(v.substr(dotpos + 1).c_str());
}

int OFTinfoPi::GetPlugInVersionMajor() { return PLUGIN_VERSION_MAJOR; }

int OFTinfoPi::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

int OFTinfoPi::GetPlugInVersionPatch() { return PLUGIN_VERSION_PATCH; }

int OFTinfoPi::GetPlugInVersionPost() { return PLUGIN_VERSION_TWEAK; };

const char* OFTinfoPi::GetPlugInVersionPre() { return PKG_PRERELEASE; }

const char* OFTinfoPi::GetPlugInVersionBuild() { return PKG_BUILD_INFO; }

wxBitmap* OFTinfoPi::GetPlugInBitmap() { return &m_panel_bitmap; }

wxString OFTinfoPi::GetCommonName() { return PLUGIN_API_NAME; }

wxString OFTinfoPi::GetShortDescription() { return PKG_SUMMARY; }

wxString OFTinfoPi::GetLongDescription() { return PKG_DESCRIPTION; }

int OFTinfoPi::GetToolbarToolCount() { return 1; }

void OFTinfoPi::SetColorScheme(PI_ColorScheme cs) {
  if (!m_dialog) return;
  DimeWindow(m_dialog);
}

void OFTinfoPi::ShowPreferencesDialog(wxWindow* parent) {
    auto* pref = new oftinfoPreferences(parent);
     // AIS Targets
    pref->m_cbAisToFile->SetValue(m_copy_AisToFile);
    pref->m_cbAisToMQTT->SetValue(m_copy_AisToMQTT);
    pref->m_cbAisToPSQL->SetValue(m_copy_AisToPSQL);
    pref->m_textCtrlAISTransPeriod->SetValue(m_copy_AISTransPeriod);
    // Target filter
    pref->m_cbAISTargCargoOnly->SetValue(m_copy_AISTargCargoOnly);
    pref->m_cbAISTargZeroInc->SetValue(m_copy_AISTargZeroInc);
    // Own Ship
    pref->m_textCtrlOwnMMSI->SetValue(m_copy_OwnMMSI);
    pref->m_cbAISTransmitAIVDO->SetValue(m_copy_AISTransmitAIVDO);
    // OFT
    pref->m_textCtrlOFTMMSI1->SetValue(m_copy_OFTMMSI1);
    pref->m_textCtrlOFTMMSI2->SetValue(m_copy_OFTMMSI2);
    // load areas
    pref->m_cbMonToFile->SetValue(m_copy_MonToFile);
    pref->m_cbMonToMQTT->SetValue(m_copy_MonToMQTT);
    pref->m_cbMonToPSQL->SetValue(m_copy_MonToPSQL);
    pref->m_textCtrlMonTransPeriod->SetValue(m_copy_MonTransPeriod);
    // file
    pref->m_textCtrlAisFileName->SetValue(m_copy_AisFileName);
    pref->m_textCtrlAISFilePath->SetValue(m_copy_AISFilePath);
    // MQTT
    pref->m_textCtrlMQTTBrokerIP->SetValue(m_copy_MQTTBrokerIP);
    pref->m_textCtrlMQTTBrokerPort->SetValue(m_copy_MQTTBrokerPort);
    pref->m_textCtrlMQTTclientID->SetValue(m_copy_MQTTclientID);
    pref->m_textCtrlMQTTuser->SetValue(m_copy_MQTTuser);
    pref->m_textCtrlMQTTuser->SetValue(m_copy_MQTTpassw);
    pref->m_textCtrlMQTTPublishTopic->SetValue(m_copy_MQTTPublishTopic);
    pref->m_textCtrlMQTTSubscribeTopic->SetValue(m_copy_MQTTSubscribeTopic);
    // Postgresql
    pref->m_textCtrlSQLip->SetValue(m_copy_SQLip);
    pref->m_textCtrlSQLport->SetValue(m_copy_SQLport);
    pref->m_textCtrlSQLuser->SetValue(m_copy_SQLuser);
    pref->m_textCtrlSQLpassw->SetValue(m_copy_SQLpassw);
    pref->m_textCtrlSQLDBName->SetValue(m_copy_SQLDBName);
        
  if (pref->ShowModal() == wxID_OK) {
    // AIS Targets
    bool copy_AisToFile = pref->m_cbAisToFile->GetValue();
    bool copy_AisToMQTT = pref->m_cbAisToMQTT->GetValue();
    bool copy_AisToPSQL = pref->m_cbAisToPSQL->GetValue();
    wxString copy_AISTransPeriod = pref->m_textCtrlAISTransPeriod->GetValue();
    // Target filter
    bool copy_AISTargCargoOnly = pref->m_cbAISTargCargoOnly->GetValue();
    bool copy_AISTargZeroInc = pref->m_cbAISTargZeroInc->GetValue();
    // Own Ship
    wxString copy_OwnMMSI = pref->m_textCtrlOwnMMSI->GetValue();
    bool copy_AISTransmitAIVDO = pref->m_cbAISTransmitAIVDO->GetValue();
    // OFT
    wxString copy_OFTMMSI1 = pref->m_textCtrlOFTMMSI1->GetValue();
    wxString copy_OFTMMSI2 = pref->m_textCtrlOFTMMSI2->GetValue();
    // load areas
    bool copy_MonToFile = pref->m_cbMonToFile->GetValue();
    bool copy_MonToMQTT = pref->m_cbMonToMQTT->GetValue();
    bool copy_MonToPSQL = pref->m_cbMonToPSQL->GetValue();
    wxString copy_MonTransPeriod = pref->m_textCtrlMonTransPeriod->GetValue();
    // file
    wxString copy_AisFileName = pref->m_textCtrlAisFileName->GetValue();
    wxString copy_AISFilePath = pref->m_textCtrlAISFilePath->GetValue();
    // MQTT
    wxString copy_MQTTBrokerIP = pref->m_textCtrlMQTTBrokerIP->GetValue();
    wxString copy_MQTTBrokerPort = pref->m_textCtrlMQTTBrokerPort->GetValue();
    wxString copy_MQTTclientID = pref->m_textCtrlMQTTclientID->GetValue();
    wxString copy_MQTTuser = pref->m_textCtrlMQTTuser->GetValue();
    wxString copy_MQTTpassw = pref->m_textCtrlMQTTpassw->GetValue();
    wxString copy_MQTTPublishTopic = pref->m_textCtrlMQTTPublishTopic->GetValue();
    wxString copy_MQTTSubscribeTopic = pref->m_textCtrlMQTTSubscribeTopic->GetValue();
    // Postgresql
    wxString copy_SQLip = pref->m_textCtrlSQLip->GetValue();
    wxString copy_SQLport = pref->m_textCtrlSQLport->GetValue();
    wxString copy_SQLuser = pref->m_textCtrlSQLuser->GetValue();
    wxString copy_SQLpassw = pref->m_textCtrlSQLpassw->GetValue();
    wxString copy_SQLDBName = pref->m_textCtrlSQLDBName->GetValue();


    // AIS Targets
    if (m_copy_AisToFile != copy_AisToFile) {m_copy_AisToFile = copy_AisToFile;}
    if (m_copy_AisToMQTT != copy_AisToMQTT) {m_copy_AisToMQTT = copy_AisToMQTT;}
    if (m_copy_AisToPSQL != copy_AisToPSQL) {m_copy_AisToPSQL = copy_AisToPSQL;}
    if (m_copy_AISTransPeriod != copy_AISTransPeriod) {m_copy_AISTransPeriod = copy_AISTransPeriod;}
    // Target filter
    if (m_copy_AISTargCargoOnly != copy_AISTargCargoOnly) {m_copy_AISTargCargoOnly = copy_AISTargCargoOnly;}
    if (m_copy_AISTargZeroInc != copy_AISTargZeroInc) {m_copy_AISTargZeroInc = copy_AISTargZeroInc;}
    // Own Ship
    if (m_copy_OwnMMSI != copy_OwnMMSI) {m_copy_OwnMMSI = copy_OwnMMSI;}
    if (m_copy_AISTransmitAIVDO != copy_AISTransmitAIVDO) {m_copy_AISTransmitAIVDO = copy_AISTransmitAIVDO;}
    // OFT
    if (m_copy_OFTMMSI1 != copy_OFTMMSI1) {m_copy_OFTMMSI1 = copy_OFTMMSI1;}
    if (m_copy_OFTMMSI2 != copy_OFTMMSI2) {m_copy_OFTMMSI2 = copy_OFTMMSI2;}
    // load areas
    if (m_copy_MonToFile != copy_MonToFile) {m_copy_MonToFile = copy_MonToFile;}
    if (m_copy_MonToMQTT != copy_MonToMQTT) {m_copy_MonToMQTT = copy_MonToMQTT;}
    if (m_copy_MonToPSQL != copy_MonToPSQL) {m_copy_MonToPSQL = copy_MonToPSQL;}
    if (m_copy_MonTransPeriod != copy_MonTransPeriod) {m_copy_MonTransPeriod = copy_MonTransPeriod;}
    // file
    if (m_copy_AisFileName != copy_AisFileName) {m_copy_AisFileName = copy_AisFileName;}
    if (m_copy_AISFilePath != copy_AISFilePath) {m_copy_AISFilePath = copy_AISFilePath;}
    // MQTT
    if (m_copy_MQTTBrokerIP != copy_MQTTBrokerIP) {m_copy_MQTTBrokerIP = copy_MQTTBrokerIP;}
    if (m_copy_MQTTBrokerPort != copy_MQTTBrokerPort) {m_copy_MQTTBrokerPort = copy_MQTTBrokerPort;}
    if (m_copy_MQTTclientID != copy_MQTTclientID) {m_copy_MQTTclientID = copy_MQTTclientID;}
    if (m_copy_MQTTuser != copy_MQTTuser) {m_copy_MQTTuser = copy_MQTTuser;}
    if (m_copy_MQTTpassw != copy_MQTTpassw) {m_copy_MQTTpassw = copy_MQTTpassw;}
    if (m_copy_MQTTPublishTopic != copy_MQTTPublishTopic) {m_copy_MQTTPublishTopic = copy_MQTTPublishTopic;}
    if (m_copy_MQTTSubscribeTopic != copy_MQTTSubscribeTopic) {m_copy_MQTTSubscribeTopic = copy_MQTTSubscribeTopic;}
    // Postgresql
    if (m_copy_SQLip != copy_SQLip) {m_copy_SQLip = copy_SQLip;}
    if (m_copy_SQLport != copy_SQLport) {m_copy_SQLport = copy_SQLport;}
    if (m_copy_SQLuser != copy_SQLuser) {m_copy_SQLuser = copy_SQLuser;}
    if (m_copy_SQLpassw != copy_SQLpassw) {m_copy_SQLpassw = copy_SQLpassw;}
    if (m_copy_SQLDBName != copy_SQLDBName) {m_copy_SQLDBName = copy_SQLDBName;}
    
    SaveConfig();

    OFTinfoPi::SetMainTaskPeriod();

    RequestRefresh(m_parent_window);  // refresh main window
  }

  delete pref;
  pref = nullptr;
  
}

void OFTinfoPi::OnToolbarToolCallback(int id) {
   if (!m_dialog) {
    m_dialog = new Dlg(m_parent_window);
    m_dialog->plugin = this;
    //m_dialog->m_timer = new wxTimer(m_dialog);
    m_dialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
    m_dialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);

         
      // base dialog
    // Unload Area
    m_dialog->m_bUnloadAreaEnable = m_copy_UnloadAreaEnable;
    m_dialog->m_bUnloadAreaVisible = m_copy_UnloadAreaVisible;
    m_dialog->m_bOGVDataVisible = m_copy_OGVDataVisible;
    m_dialog->m_bUnloadAreaSTBD = m_copy_UnloadAreaSTBD;
    m_dialog->m_bUnloadAreaPORT = m_copy_UnloadAreaPORT;
    m_dialog->m_tUnloadAreaAftTrig = m_copy_UnloadAreaAftTrig;
    m_dialog->m_tUnloadAreaBowTrig = m_copy_UnloadAreaBowTrig;
    m_dialog->m_tUnloadAreaHist = m_copy_UnloadAreaHist;
    m_dialog->m_tUnloadAreaDistance = m_copy_UnloadAreaDistance;
    m_dialog->m_tUnloadAreaLostTime = m_copy_UnloadAreaLostTime;
    m_dialog->m_cUnloadAreaColour = m_copy_UnloadAreaColour;
    // OGV
    m_dialog->m_tOGVMMSI = m_copy_OGVMMSI;
    m_dialog->m_tOGVName = m_copy_OGVName;
    m_dialog->m_tOGVLoadTime = m_copy_OGVLoadTime;
    m_dialog->m_tOGVMoorTime = m_copy_OGVMoorTime;
    m_dialog->m_tOGVUnMoorTime = m_copy_OGVUnMoorTime;
    // load Areas
    m_dialog->m_tLoadAreaLostTime = m_copy_LoadAreaLostTime;
    m_dialog->m_tLoadAreaHist = m_copy_LoadAreaHist;
    m_dialog->m_tLoadAreaDistance = m_copy_LoadAreaDistance;
    // Crane 1
    m_dialog->m_bCrane1AreaEnable = m_copy_Crane1AreaEnable;
    m_dialog->m_bCrane1AreaVisible = m_copy_Crane1AreaVisible;
    m_dialog->m_bCrane1BargeDataVisible = m_copy_Crane1BargeDataVisible;
    m_dialog->m_tCrane1AreaAftTrig = m_copy_Crane1AreaAftTrig;
    m_dialog->m_tCrane1AreaBowTrig = m_copy_Crane1AreaBowTrig;
    m_dialog->m_cCrane1AreaColour = m_copy_Crane1AreaColour;
    // Crane 1 barge
    m_dialog->m_tCrane1MMSI = m_copy_Crane1MMSI;
    m_dialog->m_tCrane1Name = m_copy_Crane1Name;
    m_dialog->m_tCrane1LoadTime = m_copy_Crane1LoadTime;
    m_dialog->m_tCrane1MoorTime = m_copy_Crane1MoorTime;
    m_dialog->m_tCrane1UnMoorTime = m_copy_Crane1UnMoorTime;
    // Crane 2
    m_dialog->m_bCrane2AreaEnable = m_copy_Crane2AreaEnable;
    m_dialog->m_bCrane2AreaVisible = m_copy_Crane2AreaVisible;
    m_dialog->m_bCrane2BargeDataVisible = m_copy_Crane2BargeDataVisible;
    m_dialog->m_tCrane2AreaAftTrig = m_copy_Crane2AreaAftTrig;
    m_dialog->m_tCrane2AreaBowTrig = m_copy_Crane2AreaBowTrig;
    m_dialog->m_cCrane2AreaColour = m_copy_Crane2AreaColour;
    // Crane 2 barge
    m_dialog->m_tCrane2MMSI = m_copy_Crane2MMSI;
    m_dialog->m_tCrane2Name = m_copy_Crane2Name;
    m_dialog->m_tCrane2LoadTime = m_copy_Crane2LoadTime;
    m_dialog->m_tCrane2MoorTime = m_copy_Crane2MoorTime;
    m_dialog->m_tCrane2UnMoorTime = m_copy_Crane2UnMoorTime;
    // Crane 3
    m_dialog->m_bCrane3AreaEnable = m_copy_Crane3AreaEnable;
    m_dialog->m_bCrane3AreaVisible = m_copy_Crane3AreaVisible;
    m_dialog->m_bCrane3BargeDataVisible = m_copy_Crane3BargeDataVisible;
    m_dialog->m_tCrane3AreaAftTrig = m_copy_Crane3AreaAftTrig;
    m_dialog->m_tCrane3AreaBowTrig = m_copy_Crane3AreaBowTrig;
    m_dialog->m_cCrane3AreaColour = m_copy_Crane3AreaColour;
    // Crane 3 barge
    m_dialog->m_tCrane3MMSI = m_copy_Crane3MMSI;
    m_dialog->m_tCrane3Name = m_copy_Crane3Name;
    m_dialog->m_tCrane3LoadTime = m_copy_Crane3LoadTime;
    m_dialog->m_tCrane3MoorTime = m_copy_Crane3MoorTime;
    m_dialog->m_tCrane3UnMoorTime = m_copy_Crane3UnMoorTime;
    // Crane 4
    m_dialog->m_bCrane4AreaEnable = m_copy_Crane4AreaEnable;
    m_dialog->m_bCrane4AreaVisible = m_copy_Crane4AreaVisible;
    m_dialog->m_bCrane4BargeDataVisible = m_copy_Crane4BargeDataVisible;
    m_dialog->m_tCrane4AreaAftTrig = m_copy_Crane4AreaAftTrig;
    m_dialog->m_tCrane4AreaBowTrig = m_copy_Crane4AreaBowTrig;
    m_dialog->m_cCrane4AreaColour = m_copy_Crane4AreaColour;
    // Crane 4 barge
    m_dialog->m_tCrane4MMSI = m_copy_Crane4MMSI;
    m_dialog->m_tCrane4Name = m_copy_Crane4Name;
    m_dialog->m_tCrane4LoadTime = m_copy_Crane4LoadTime;
    m_dialog->m_tCrane4MoorTime = m_copy_Crane4MoorTime;
    m_dialog->m_tCrane4UnMoorTime = m_copy_Crane4UnMoorTime;

   // wxMenu dummy_menu;
   // m_position_menu_id = AddCanvasContextMenuItem(
   //     new wxMenuItem(&dummy_menu, -1, _("Select Vessel Start Position")),
   //     this);
   // SetCanvasContextMenuItemViz(m_position_menu_id, true);
  }

  // m_pDialog->Fit();
  // Toggle
  m_show_oftinfo = !m_show_oftinfo;

  //    Toggle dialog?
  if (m_show_oftinfo) {
    m_dialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
    m_dialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
    m_dialog->Show();

  } else { // close dialog
    // base dialog
    // Unload Area
    m_copy_UnloadAreaEnable = m_dialog->m_bUnloadAreaEnable;
    m_copy_UnloadAreaVisible = m_dialog->m_bUnloadAreaVisible;
    m_copy_OGVDataVisible = m_dialog->m_bOGVDataVisible;
    m_copy_UnloadAreaSTBD = m_dialog->m_bUnloadAreaSTBD;
    m_copy_UnloadAreaPORT = m_dialog->m_bUnloadAreaPORT;
    m_copy_UnloadAreaAftTrig = m_dialog->m_tUnloadAreaAftTrig;
    m_copy_UnloadAreaBowTrig = m_dialog->m_tUnloadAreaBowTrig;
    m_copy_UnloadAreaHist = m_dialog->m_tUnloadAreaHist;
    m_copy_UnloadAreaDistance = m_dialog->m_tUnloadAreaDistance;
    m_copy_UnloadAreaLostTime = m_dialog->m_tUnloadAreaLostTime;
    m_copy_UnloadAreaColour = m_dialog->m_cUnloadAreaColour;
    // load Areas
    m_copy_LoadAreaLostTime = m_dialog->m_tLoadAreaLostTime;
    m_copy_LoadAreaHist = m_dialog->m_tLoadAreaHist;
    m_copy_LoadAreaDistance = m_dialog->m_tLoadAreaDistance;
    // Crane 1
    m_copy_Crane1AreaEnable = m_dialog->m_bCrane1AreaEnable;
    m_copy_Crane1AreaVisible = m_dialog->m_bCrane1AreaVisible;
    m_copy_Crane1BargeDataVisible = m_dialog->m_bCrane1BargeDataVisible;
    m_copy_Crane1AreaAftTrig = m_dialog->m_tCrane1AreaAftTrig;
    m_copy_Crane1AreaBowTrig = m_dialog->m_tCrane1AreaBowTrig;
    m_copy_Crane1AreaColour = m_dialog->m_cCrane1AreaColour;
    // Crane 2
    m_copy_Crane2AreaEnable = m_dialog->m_bCrane2AreaEnable;
    m_copy_Crane2AreaVisible = m_dialog->m_bCrane2AreaVisible;
    m_copy_Crane2BargeDataVisible = m_dialog->m_bCrane2BargeDataVisible;
    m_copy_Crane2AreaAftTrig = m_dialog->m_tCrane2AreaAftTrig;
    m_copy_Crane2AreaBowTrig = m_dialog->m_tCrane2AreaBowTrig;
    m_copy_Crane2AreaColour = m_dialog->m_cCrane2AreaColour;
    // Crane 3
    m_copy_Crane3AreaEnable = m_dialog->m_bCrane3AreaEnable;
    m_copy_Crane3AreaVisible = m_dialog->m_bCrane3AreaVisible;
    m_copy_Crane3BargeDataVisible = m_dialog->m_bCrane3BargeDataVisible;
    m_copy_Crane3AreaAftTrig = m_dialog->m_tCrane3AreaAftTrig;
    m_copy_Crane3AreaBowTrig = m_dialog->m_tCrane3AreaBowTrig;
    m_copy_Crane3AreaColour = m_dialog->m_cCrane3AreaColour;
    // Crane 4
    m_copy_Crane4AreaEnable = m_dialog->m_bCrane4AreaEnable;
    m_copy_Crane4AreaVisible = m_dialog->m_bCrane4AreaVisible;
    m_copy_Crane4BargeDataVisible = m_dialog->m_bCrane4BargeDataVisible;
    m_copy_Crane4AreaAftTrig = m_dialog->m_tCrane4AreaAftTrig;
    m_copy_Crane4AreaBowTrig = m_dialog->m_tCrane4AreaBowTrig;
    m_copy_Crane4AreaColour = m_dialog->m_cCrane4AreaColour;
    
    m_dialog->Hide();
  }

  // Toggle is handled by the toolbar but we must keep plugin manager b_toggle
  // updated to actual status to ensure correct status upon toolbar rebuild
  SetToolbarItemState(m_leftclick_tool_id, m_show_oftinfo);

  // Capture dialog position
  wxPoint p = m_dialog->GetPosition();
  wxRect r = m_dialog->GetRect();
  SetOFTinfoDialogX(p.x);
  SetOFTinfoDialogY(p.y);
  SetOFTinfoDialogSizeX(r.GetWidth());
  SetOFTinfoDialogSizeY(r.GetHeight());

  RequestRefresh(m_parent_window);  // refresh main window
}

bool OFTinfoPi::LoadConfig() {
   auto* conf = (wxFileConfig*)m_config;

  if (conf) {
    if (conf->HasGroup(_T("/Settings/OFTinfo_pi"))) {
      // Read the existing settings

      conf->SetPath("/Settings/OFTinfo_pi");
      conf->Read("ShowOFTinfoIcon", &m_show_oftinfo_icon, true);

      // AIS Targets
      conf->Read("oftinfoAisToFile", &m_copy_AisToFile, true);
      conf->Read("oftinfoAisToMQTT", &m_copy_AisToMQTT, false);
      conf->Read("oftinfoAisToPSQL", &m_copy_AisToPSQL, false);
      m_copy_AISTransPeriod = conf->Read("oftinfoAISTransPeriod", "20");
      // Target filter
      conf->Read("oftinfoAISTargCargoOnly", &m_copy_AISTargCargoOnly, true);
      conf->Read("oftinfoAisToAISTargZeroInc", &m_copy_AISTargZeroInc, false);
      // Own Ship
      m_copy_OwnMMSI = conf->Read("oftinfoOwnMMSI", "123456789");
      conf->Read("oftinfoAISTransmitAIVDO", &m_copy_AISTransmitAIVDO, true);
      // OFT
      m_copy_OFTMMSI1 = conf->Read("oftinfoOFTMMSI1", "123456789");
      m_copy_OFTMMSI2 = conf->Read("oftinfoOFTMMSI2", "123456789");
      // load areas
      conf->Read("oftinfoMonToFile", &m_copy_MonToFile, true);
      conf->Read("oftinfoMonToMQTT", &m_copy_MonToMQTT, false);
      conf->Read("oftinfoMonToPSQL", &m_copy_MonToPSQL, false);
      m_copy_MonTransPeriod = conf->Read("oftinfoMonTransPeriod", "20");
      // file
      m_copy_AisFileName = conf->Read("oftinfoAisFileName", "AISTargets.txt");
      m_copy_AISFilePath = conf->Read("oftinfoAISFilePath", "C:\\scripts\\");
      // MQTT
      m_copy_MQTTBrokerIP = conf->Read("oftinfoMQTTBrokerIP", "127.0.0.1");
      m_copy_MQTTBrokerPort = conf->Read("oftinfoMQTTBrokerPort", "1883");
      m_copy_MQTTclientID = conf->Read("oftinfoMQTTclientID", "OFTinfoMain");
      m_copy_MQTTuser = conf->Read("oftinfoMQTTuser", "user");
      m_copy_MQTTpassw = conf->Read("oftinfoMQTTpassw", "password");
      m_copy_MQTTPublishTopic = conf->Read("oftinfoMQTTPublishTopic", "Cargo/OCPN");
      m_copy_MQTTSubscribeTopic = conf->Read("oftinfoMQTTSubscribeTopic", "Cargo/OCPN");
      // Postgresql
      m_copy_SQLip = conf->Read("oftinfoSQLip", "127.0.0.1");
      m_copy_SQLport = conf->Read("oftinfoSQLport", "5432");
      m_copy_SQLuser = conf->Read("oftinfoSQLuser", "user");
      m_copy_SQLpassw = conf->Read("oftinfoSQLpassw", "password");
      m_copy_SQLDBName = conf->Read("oftinfoSQLDBName", "cargo");

      // base dialog
      // Unload Area
      conf->Read("oftinfoUnloadAreaEnable", &m_copy_UnloadAreaEnable, true);
      conf->Read("oftinfoUnloadAreaVisible", &m_copy_UnloadAreaVisible, true);
      conf->Read("oftinfoOGVDataVisible", &m_copy_OGVDataVisible, true);
      conf->Read("oftinfoUnloadAreaSTBD", &m_copy_UnloadAreaSTBD, false);
      conf->Read("oftinfoUnloadAreaPORT", &m_copy_UnloadAreaPORT, true);
      m_copy_UnloadAreaAftTrig = conf->Read("oftinfoUnloadAreaAftTrig", "0");
      m_copy_UnloadAreaBowTrig = conf->Read("oftinfoUnloadAreaBowTrig", "0");
      m_copy_UnloadAreaHist = conf->Read("oftinfoUnloadAreaHist", "60");
      m_copy_UnloadAreaDistance = conf->Read("oftinfoUnloadAreaDistance", "60");
      m_copy_UnloadAreaLostTime = conf->Read("oftinfoUnloadAreaLostTime", "60");
      conf->Read("oftinfoUnloadAreaColour", &m_copy_IntUnloadAreaColour, 0x000000);
      m_copy_UnloadAreaColour.SetRGB(m_copy_IntUnloadAreaColour); //red, green, blue
      // OGV
      m_copy_OGVMMSI = conf->Read("oftinfoOGVMMSI", "0");
      m_copy_OGVName = conf->Read("oftinfoOGVName", "");
      m_copy_OGVLoadTime = conf->Read("oftinfoOGVLoadTime", "00:00:00");
      m_copy_OGVMoorTime = conf->Read("oftinfoOGVMoorTime", "01.01.1970 00:00:00");
      m_copy_OGVUnMoorTime = conf->Read("oftinfoOGVUnMoorTime", "01.01.1970 00:00:00");
      // load Areas
      m_copy_LoadAreaLostTime = conf->Read("oftinfoLoadAreaLostTime", "60");
      m_copy_LoadAreaHist = conf->Read("oftinfoLoadAreaHist", "10");
      m_copy_LoadAreaDistance = conf->Read("oftinfoLoadAreaDistance", "60");
      // Crane 1
      conf->Read("oftinfoCrane1AreaEnable", &m_copy_Crane1AreaEnable, true);
      conf->Read("oftinfoCrane1AreaEnable", &m_copy_Crane1AreaVisible, true);
      conf->Read("oftinfoCrane1BargeDataVisible", &m_copy_Crane1BargeDataVisible, true);
      m_copy_Crane1AreaAftTrig = conf->Read("oftinfoCrane1AreaAftTrig", "70");
      m_copy_Crane1AreaBowTrig = conf->Read("oftinfoCrane1AreaBowTrig", "70");
      conf->Read("oftinfoCrane1AreaColour", &m_copy_IntCrane1AreaColour, 0x000000);
      m_copy_Crane1AreaColour.SetRGB(m_copy_IntCrane1AreaColour);  // red, green, blue
      // Crane 1 barge
      m_copy_Crane1MMSI = conf->Read("oftinfoCrane1MMSI", "0");
      m_copy_Crane1Name = conf->Read("oftinfoCrane1Name", "");
      m_copy_Crane1LoadTime = conf->Read("oftinfoCrane1LoadTime", "00:00:00");
      m_copy_Crane1MoorTime = conf->Read("oftinfoCrane1MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane1UnMoorTime = conf->Read("oftinfoCrane1UnMoorTime", "01.01.1970 00:00:00");
      // Crane 2
      conf->Read("oftinfoCrane2AreaEnable", &m_copy_Crane2AreaEnable, true);
      conf->Read("oftinfoCrane2AreaEnable", &m_copy_Crane2AreaVisible, true);
      conf->Read("oftinfoCrane2BargeDataVisible", &m_copy_Crane2BargeDataVisible, true);
      m_copy_Crane2AreaAftTrig = conf->Read("oftinfoCrane2AreaAftTrig", "50");
      m_copy_Crane2AreaBowTrig = conf->Read("oftinfoCrane2AreaBowTrig", "50");
      conf->Read("oftinfoCrane2AreaColour", &m_copy_IntCrane2AreaColour, 0x000000);
      m_copy_Crane2AreaColour.SetRGB(m_copy_IntCrane2AreaColour);  // red, green, blue
      //  Crane 2 barge
      m_copy_Crane2MMSI = conf->Read("oftinfoCrane2MMSI", "0");
      m_copy_Crane2Name = conf->Read("oftinfoCrane2Name", "");
      m_copy_Crane2LoadTime = conf->Read("oftinfoCrane2LoadTime", "00:00:00");
      m_copy_Crane2MoorTime = conf->Read("oftinfoCrane2MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane2UnMoorTime = conf->Read("oftinfoCrane2UnMoorTime", "01.01.1970 00:00:00");
      // Crane 3
      conf->Read("oftinfoCrane3AreaEnable", &m_copy_Crane3AreaEnable, true);
      conf->Read("oftinfoCrane3AreaEnable", &m_copy_Crane3AreaVisible, true);
      conf->Read("oftinfoCrane3BargeDataVisible", &m_copy_Crane3BargeDataVisible, true);
      m_copy_Crane3AreaAftTrig = conf->Read("oftinfoCrane3AreaAftTrig", "50");
      m_copy_Crane3AreaBowTrig = conf->Read("oftinfoCrane3AreaBowTrig", "50");
      conf->Read("oftinfoCrane3AreaColour", &m_copy_IntCrane3AreaColour, 0x000000);
      m_copy_Crane3AreaColour.SetRGB( m_copy_IntCrane3AreaColour);  // red, green, blue
      //  Crane 3 barge
      m_copy_Crane3MMSI = conf->Read("oftinfoCrane3MMSI", "0");
      m_copy_Crane3Name = conf->Read("oftinfoCrane3Name", "");
      m_copy_Crane3LoadTime = conf->Read("oftinfoCrane3LoadTime", "00:00:00");
      m_copy_Crane3MoorTime = conf->Read("oftinfoCrane3MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane3UnMoorTime = conf->Read("oftinfoCrane3UnMoorTime", "01.01.1970 00:00:00");
      // Crane 4
      conf->Read("oftinfoCrane4AreaEnable", &m_copy_Crane4AreaEnable, true);
      conf->Read("oftinfoCrane4AreaEnable", &m_copy_Crane4AreaVisible, true);
      conf->Read("oftinfoCrane4BargeDataVisible", &m_copy_Crane4BargeDataVisible, true);
      m_copy_Crane4AreaAftTrig = conf->Read("oftinfoCrane4AreaAftTrig", "50");
      m_copy_Crane4AreaBowTrig = conf->Read("oftinfoCrane4AreaBowTrig", "50");
      conf->Read("oftinfoCrane4AreaColour", &m_copy_IntCrane4AreaColour, 0x000000);
      m_copy_Crane4AreaColour.SetRGB(m_copy_IntCrane4AreaColour);  // red, green, blue
      //  Crane 4 barge
      m_copy_Crane4MMSI = conf->Read("oftinfoCrane4MMSI", "0");
      m_copy_Crane4Name = conf->Read("oftinfoCrane4Name", "");
      m_copy_Crane4LoadTime = conf->Read("oftinfoCrane4LoadTime", "00:00:00");
      m_copy_Crane4MoorTime = conf->Read("oftinfoCrane4MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane4UnMoorTime = conf->Read("oftinfoCrane4UnMoorTime", "01.01.1970 00:00:00");
      
      m_hr_dialog_x = conf->Read("DialogPosX", 40L);
      m_hr_dialog_y = conf->Read("DialogPosY", 140L);
      m_hr_dialog_sx = conf->Read("DialogSizeX", 330L);
#ifdef __WXOSX__
      m_hr_dialog_sy = conf->Read("DialogSizeY", 250L);
#else
      m_hr_dialog_sy = conf->Read("DialogSizeY", 300L);
#endif
      conf->DeleteGroup(_T("/Settings/OFTinfo_pi"));
    } else {
      conf->SetPath("/PlugIns/OFTinfo_pi");
      conf->Read("ShowOFTinfoIcon", &m_show_oftinfo_icon, true);

      // AIS Targets
      conf->Read("oftinfoAisToFile", &m_copy_AisToFile, true);
      conf->Read("oftinfoAisToMQTT", &m_copy_AisToMQTT, false);
      conf->Read("oftinfoAisToPSQL", &m_copy_AisToPSQL, false);
      m_copy_AISTransPeriod = conf->Read("oftinfoAISTransPeriod", "20");
      // Target filter
      conf->Read("oftinfoAISTargCargoOnly", &m_copy_AISTargCargoOnly, true);
      conf->Read("oftinfoAisToAISTargZeroInc", &m_copy_AISTargZeroInc, false);
      // Own Ship
      m_copy_OwnMMSI = conf->Read("oftinfoOwnMMSI", "123456789");
      conf->Read("oftinfoAISTransmitAIVDO", &m_copy_AISTransmitAIVDO, true);
      // OFT
      m_copy_OFTMMSI1 = conf->Read("oftinfoOFTMMSI1", "123456789");
      m_copy_OFTMMSI2 = conf->Read("oftinfoOFTMMSI2", "123456789");
      // load areas
      conf->Read("oftinfoMonToFile", &m_copy_MonToFile, true);
      conf->Read("oftinfoMonToMQTT", &m_copy_MonToMQTT, false);
      conf->Read("oftinfoMonToPSQL", &m_copy_MonToPSQL, false);
      m_copy_MonTransPeriod = conf->Read("oftinfoMonTransPeriod", "20");
      // file
      m_copy_AisFileName = conf->Read("oftinfoAisFileName", "AISTargets.txt");
      m_copy_AISFilePath = conf->Read("oftinfoAISFilePath", "C:\\scripts\\");
      // MQTT
      m_copy_MQTTBrokerIP = conf->Read("oftinfoMQTTBrokerIP", "127.0.0.1");
      m_copy_MQTTBrokerPort = conf->Read("oftinfoMQTTBrokerPort", "1883");
      m_copy_MQTTclientID = conf->Read("oftinfoMQTTclientID", "OFTinfoMain");
      m_copy_MQTTuser = conf->Read("oftinfoMQTTuser", "user");
      m_copy_MQTTpassw = conf->Read("oftinfoMQTTpassw", "password");
      m_copy_MQTTPublishTopic = conf->Read("oftinfoMQTTPublishTopic", "Cargo/OCPN");
      m_copy_MQTTSubscribeTopic = conf->Read("oftinfoMQTTSubscribeTopic", "Cargo/OCPN");
      // Postgresql
      m_copy_SQLip = conf->Read("oftinfoSQLip", "127.0.0.1");
      m_copy_SQLport = conf->Read("oftinfoSQLport", "5432");
      m_copy_SQLuser = conf->Read("oftinfoSQLuser", "user");
      m_copy_SQLpassw = conf->Read("oftinfoSQLpassw", "password");
      m_copy_SQLDBName = conf->Read("oftinfoSQLDBName", "cargo");

      // base dialog
      // Unload Area
      conf->Read("oftinfoUnloadAreaEnable", &m_copy_UnloadAreaEnable, true);
      conf->Read("oftinfoUnloadAreaVisible", &m_copy_UnloadAreaVisible, true);
      conf->Read("oftinfoOGVDataVisible", &m_copy_OGVDataVisible, true);
      conf->Read("oftinfoUnloadAreaSTBD", &m_copy_UnloadAreaSTBD, false);
      conf->Read("oftinfoUnloadAreaPORT", &m_copy_UnloadAreaPORT, true);
      m_copy_UnloadAreaAftTrig = conf->Read("oftinfoUnloadAreaAftTrig", "0");
      m_copy_UnloadAreaBowTrig = conf->Read("oftinfoUnloadAreaBowTrig", "0");
      m_copy_UnloadAreaHist = conf->Read("oftinfoUnloadAreaHist", "60");
      m_copy_UnloadAreaDistance = conf->Read("oftinfoUnloadAreaDistance", "60");
      m_copy_UnloadAreaLostTime = conf->Read("oftinfoUnloadAreaLostTime", "60");
      conf->Read("oftinfoUnloadAreaColour", &m_copy_IntUnloadAreaColour, 0x000000);
      m_copy_UnloadAreaColour.SetRGB(m_copy_IntUnloadAreaColour);  // red, green, blue
      //  OGV
      m_copy_OGVMMSI = conf->Read("oftinfoOGVMMSI", "0");
      m_copy_OGVName = conf->Read("oftinfoOGVName", "");
      m_copy_OGVLoadTime = conf->Read("oftinfoOGVLoadTime", "00:00:00");
      m_copy_OGVMoorTime = conf->Read("oftinfoOGVMoorTime", "01.01.1970 00:00:00");
      m_copy_OGVUnMoorTime = conf->Read("oftinfoOGVUnMoorTime", "01.01.1970 00:00:00");
      // load Areas
      m_copy_LoadAreaLostTime = conf->Read("oftinfoLoadAreaLostTime", "60");
      m_copy_LoadAreaHist = conf->Read("oftinfoLoadAreaHist", "10");
      m_copy_LoadAreaDistance = conf->Read("oftinfoLoadAreaDistance", "60");
      // Crane 1
      conf->Read("oftinfoCrane1AreaEnable", &m_copy_Crane1AreaEnable, true);
      conf->Read("oftinfoCrane1AreaEnable", &m_copy_Crane1AreaVisible, true);
      conf->Read("oftinfoCrane1BargeDataVisible", &m_copy_Crane1BargeDataVisible, true);
      m_copy_Crane1AreaAftTrig = conf->Read("oftinfoCrane1AreaAftTrig", "70");
      m_copy_Crane1AreaBowTrig = conf->Read("oftinfoCrane1AreaBowTrig", "70");
      conf->Read("oftinfoCrane1AreaColour", &m_copy_IntCrane1AreaColour, 0x000000);
      m_copy_Crane1AreaColour.SetRGB(m_copy_IntCrane1AreaColour);  // red, green, blue
      //  Crane 1 barge
      m_copy_Crane1MMSI = conf->Read("oftinfoCrane1MMSI", "0");
      m_copy_Crane1Name = conf->Read("oftinfoCrane1Name", "");
      m_copy_Crane1LoadTime = conf->Read("oftinfoCrane1LoadTime", "00:00:00");
      m_copy_Crane1MoorTime = conf->Read("oftinfoCrane1MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane1UnMoorTime = conf->Read("oftinfoCrane1UnMoorTime", "01.01.1970 00:00:00");
      // Crane 2
      conf->Read("oftinfoCrane2AreaEnable", &m_copy_Crane2AreaEnable, true);
      conf->Read("oftinfoCrane2AreaEnable", &m_copy_Crane2AreaVisible, true);
      conf->Read("oftinfoCrane2BargeDataVisible", &m_copy_Crane2BargeDataVisible, true);
      m_copy_Crane2AreaAftTrig = conf->Read("oftinfoCrane2AreaAftTrig", "50");
      m_copy_Crane2AreaBowTrig = conf->Read("oftinfoCrane2AreaBowTrig", "50");
      conf->Read("oftinfoCrane2AreaColour", &m_copy_IntCrane2AreaColour, 0x000000);
      m_copy_Crane2AreaColour.SetRGB(m_copy_IntCrane2AreaColour);  // red, green, blue
      //  Crane 2 barge
      m_copy_Crane2MMSI = conf->Read("oftinfoCrane2MMSI", "0");
      m_copy_Crane2Name = conf->Read("oftinfoCrane2Name", "");
      m_copy_Crane2LoadTime = conf->Read("oftinfoCrane2LoadTime", "00:00:00");
      m_copy_Crane2MoorTime = conf->Read("oftinfoCrane2MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane2UnMoorTime = conf->Read("oftinfoCrane2UnMoorTime", "01.01.1970 00:00:00");
      // Crane 3
      conf->Read("oftinfoCrane3AreaEnable", &m_copy_Crane3AreaEnable, true);
      conf->Read("oftinfoCrane3AreaEnable", &m_copy_Crane3AreaVisible, true);
      conf->Read("oftinfoCrane3BargeDataVisible", &m_copy_Crane3BargeDataVisible, true);
      m_copy_Crane3AreaAftTrig = conf->Read("oftinfoCrane3AreaAftTrig", "50");
      m_copy_Crane3AreaBowTrig = conf->Read("oftinfoCrane3AreaBowTrig", "50");
      conf->Read("oftinfoCrane3AreaColour", &m_copy_IntCrane3AreaColour, 0x000000);
      m_copy_Crane3AreaColour.SetRGB(m_copy_IntCrane3AreaColour);  // red, green, blue
      //  Crane 3 barge
      m_copy_Crane3MMSI = conf->Read("oftinfoCrane3MMSI", "0");
      m_copy_Crane3Name = conf->Read("oftinfoCrane3Name", "");
      m_copy_Crane3LoadTime = conf->Read("oftinfoCrane3LoadTime", "00:00:00");
      m_copy_Crane3MoorTime = conf->Read("oftinfoCrane3MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane3UnMoorTime = conf->Read("oftinfoCrane3UnMoorTime", "01.01.1970 00:00:00");
      // Crane 4
      conf->Read("oftinfoCrane4AreaEnable", &m_copy_Crane4AreaEnable, true);
      conf->Read("oftinfoCrane4AreaEnable", &m_copy_Crane4AreaVisible, true);
      conf->Read("oftinfoCrane4BargeDataVisible", &m_copy_Crane4BargeDataVisible, true);
      m_copy_Crane4AreaAftTrig = conf->Read("oftinfoCrane4AreaAftTrig", "50");
      m_copy_Crane4AreaBowTrig = conf->Read("oftinfoCrane4AreaBowTrig", "50");
      conf->Read("oftinfoCrane4AreaColour", &m_copy_IntCrane4AreaColour, 0x000000);
      m_copy_Crane4AreaColour.SetRGB(m_copy_IntCrane4AreaColour);  // red, green, blue
      //  Crane 4 barge
      m_copy_Crane4MMSI = conf->Read("oftinfoCrane4MMSI", "0");
      m_copy_Crane4Name = conf->Read("oftinfoCrane4Name", "");
      m_copy_Crane4LoadTime = conf->Read("oftinfoCrane4LoadTime", "00:00:00");
      m_copy_Crane4MoorTime = conf->Read("oftinfoCrane4MoorTime", "01.01.1970 00:00:00");
      m_copy_Crane4UnMoorTime = conf->Read("oftinfoCrane4UnMoorTime", "01.01.1970 00:00:00");

      m_hr_dialog_x = conf->Read("DialogPosX", 40L);
      m_hr_dialog_y = conf->Read("DialogPosY", 140L);
      m_hr_dialog_sx = conf->Read("DialogSizeX", 330L);
#ifdef __WXOSX__
      m_hr_dialog_sy = conf->Read("DialogSizeY", 250L);
#else
      m_hr_dialog_sy = conf->Read("DialogSizeY", 300L);
#endif
    }
    if ((m_hr_dialog_x < 0) || (m_hr_dialog_x > m_display_width))
      m_hr_dialog_x = 40;
    if ((m_hr_dialog_y < 0) || (m_hr_dialog_y > m_display_height))
      m_hr_dialog_y = 140;

    return true;
  } else
    
    return false;
}

bool OFTinfoPi::SaveConfig() {
   auto* conf = (wxFileConfig*)m_config;
  // FIXME ADD check all text data!!! 
 

    conf->SetPath("/PlugIns/OFTinfo_pi");
    conf->Write("ShowOFTinfoIcon", m_show_oftinfo_icon);

    // AIS Targets
    conf->Write("oftinfoAisToFile", m_copy_AisToFile);
    conf->Write("oftinfoAisToMQTT", m_copy_AisToMQTT);
    conf->Write("oftinfoAisToPSQL",m_copy_AisToPSQL);
    conf->Write("oftinfoAISTransPeriod", m_copy_AISTransPeriod);
    // Target filter
    conf->Write("oftinfoAISTargCargoOnly", m_copy_AISTargCargoOnly);
    conf->Write("oftinfoAisToAISTargZeroInc", m_copy_AISTargZeroInc);
    // Own Ship
    conf->Write("oftinfoOwnMMSI", m_copy_OwnMMSI);
    conf->Write("oftinfoAISTransmitAIVDO", m_copy_AISTransmitAIVDO);
    // OFT
    conf->Write("oftinfoOFTMMSI1", m_copy_OFTMMSI1);
    conf->Write("oftinfoOFTMMSI2", m_copy_OFTMMSI2);
    // load areas
    conf->Write("oftinfoMonToFile", m_copy_MonToFile);
    conf->Write("oftinfoMonToMQTT", m_copy_MonToMQTT);
    conf->Write("oftinfoMonToPSQL", m_copy_MonToPSQL);
    conf->Write("oftinfoMonTransPeriod", m_copy_MonTransPeriod);
    // file
    conf->Write("oftinfoAisFileName", m_copy_AisFileName);
    conf->Write("oftinfoAISFilePath", m_copy_AISFilePath);
    // MQTT
    conf->Write("oftinfoMQTTBrokerIP", m_copy_MQTTBrokerIP);
    conf->Write("oftinfoMQTTBrokerPort", m_copy_MQTTBrokerPort);
    conf->Write("oftinfoMQTTclientID", m_copy_MQTTclientID);
    conf->Write("oftinfoMQTTuser", m_copy_MQTTuser);
    conf->Write("oftinfoMQTTpassw", m_copy_MQTTpassw);
    conf->Write("oftinfoMQTTPublishTopic", m_copy_MQTTPublishTopic);
    conf->Write("oftinfoMQTTSubscribeTopic", m_copy_MQTTSubscribeTopic);
    // Postgresql
    conf->Write("oftinfoSQLip", m_copy_SQLip);
    conf->Write("oftinfoSQLport", m_copy_SQLport);
    conf->Write("oftinfoSQLuser", m_copy_SQLuser);
    conf->Write("oftinfoSQLpassw", m_copy_SQLpassw);
    conf->Write("oftinfoSQLDBName", m_copy_SQLDBName);

    // base dialog
    // Unload Area
    conf->Write("oftinfoUnloadAreaEnable", m_copy_UnloadAreaEnable);
    conf->Write("oftinfoUnloadAreaVisible", m_copy_UnloadAreaVisible);
    conf->Write("oftinfoOGVDataVisible", m_copy_OGVDataVisible);
    conf->Write("oftinfoUnloadAreaSTBD", m_copy_UnloadAreaSTBD);
    conf->Write("oftinfoUnloadAreaPORT", m_copy_UnloadAreaPORT);
    conf->Write("oftinfoUnloadAreaAftTrig", m_copy_UnloadAreaAftTrig);
    conf->Write("oftinfoUnloadAreaBowTrig", m_copy_UnloadAreaBowTrig);
    conf->Write("oftinfoUnloadAreaHist", m_copy_UnloadAreaHist);
    conf->Write("oftinfoUnloadAreaDistance", m_copy_UnloadAreaDistance);
    conf->Write("oftinfoUnloadAreaLostTime", m_copy_UnloadAreaLostTime);
    m_copy_IntUnloadAreaColour = m_copy_UnloadAreaColour.GetRGB();  // red, green, blue
    conf->Write("oftinfoUnloadAreaColour", m_copy_IntUnloadAreaColour);
    //  OGV
    conf->Write("oftinfoOGVMMSI", m_copy_OGVMMSI);
    conf->Write("oftinfoOGVName", m_copy_OGVName);
    conf->Write("oftinfoOGVLoadTime", m_copy_OGVLoadTime);
    conf->Write("oftinfoOGVMoorTime", m_copy_OGVMoorTime);
    conf->Write("oftinfoOGVUnMoorTime", m_copy_OGVUnMoorTime);
    // load Areas
    conf->Write("oftinfoLoadAreaLostTime", m_copy_LoadAreaLostTime);
    conf->Write("oftinfoLoadAreaHist", m_copy_LoadAreaHist);
    conf->Write("oftinfoLoadAreaDistance", m_copy_LoadAreaDistance);
    // Crane 1
    conf->Write("oftinfoCrane1AreaEnable", m_copy_Crane1AreaEnable);
    conf->Write("oftinfoCrane1AreaEnable", m_copy_Crane1AreaVisible);
    conf->Write("oftinfoCrane1BargeDataVisible", m_copy_Crane1BargeDataVisible);
    conf->Write("oftinfoCrane1AreaAftTrig", m_copy_Crane1AreaAftTrig);
    conf->Write("oftinfoCrane1AreaBowTrig", m_copy_Crane1AreaBowTrig);
    m_copy_IntCrane1AreaColour = m_copy_Crane1AreaColour.GetRGB();  // red, green, blue
    conf->Write("oftinfoCrane1AreaColour", m_copy_IntCrane1AreaColour);
    //  Crane 1 barge
    conf->Write("oftinfoCrane1MMSI", m_copy_Crane1MMSI);
    conf->Write("oftinfoCrane1Name", m_copy_Crane1Name);
    conf->Write("oftinfoCrane1LoadTime", m_copy_Crane1LoadTime);
    conf->Write("oftinfoCrane1MoorTime", m_copy_Crane1MoorTime);
    conf->Write("oftinfoCrane1UnMoorTime", m_copy_Crane1UnMoorTime);
    // Crane 2
    conf->Write("oftinfoCrane2AreaEnable", m_copy_Crane2AreaEnable);
    conf->Write("oftinfoCrane2AreaEnable", m_copy_Crane2AreaVisible);
    conf->Write("oftinfoCrane2BargeDataVisible", m_copy_Crane2BargeDataVisible);
    conf->Write("oftinfoCrane2AreaAftTrig", m_copy_Crane2AreaAftTrig);
    conf->Write("oftinfoCrane2AreaBowTrig", m_copy_Crane2AreaBowTrig);
    m_copy_IntCrane2AreaColour = m_copy_Crane2AreaColour.GetRGB();  // red, green, blue
    conf->Write("oftinfoCrane2AreaColour", m_copy_IntCrane2AreaColour);
    //  Crane 2 barge
    conf->Write("oftinfoCrane2MMSI", m_copy_Crane2MMSI);
    conf->Write("oftinfoCrane2Name", m_copy_Crane2Name);
    conf->Write("oftinfoCrane2LoadTime", m_copy_Crane2LoadTime);
    conf->Write("oftinfoCrane2MoorTime", m_copy_Crane2MoorTime);
    conf->Write("oftinfoCrane2UnMoorTime", m_copy_Crane2UnMoorTime);
    // Crane 3
    conf->Write("oftinfoCrane3AreaEnable", m_copy_Crane3AreaEnable);
    conf->Write("oftinfoCrane3AreaEnable", m_copy_Crane3AreaVisible);
    conf->Write("oftinfoCrane3BargeDataVisible", m_copy_Crane3BargeDataVisible);
    conf->Write("oftinfoCrane3AreaAftTrig", m_copy_Crane3AreaAftTrig);
    conf->Write("oftinfoCrane3AreaBowTrig", m_copy_Crane3AreaBowTrig);
    m_copy_IntCrane3AreaColour = m_copy_Crane3AreaColour.GetRGB();  // red, green, blue
    conf->Write("oftinfoCrane3AreaColour", m_copy_IntCrane3AreaColour);
    //  Crane 3 barge
    conf->Write("oftinfoCrane3MMSI", m_copy_Crane3MMSI);
    conf->Write("oftinfoCrane3Name", m_copy_Crane3Name);
    conf->Write("oftinfoCrane3LoadTime", m_copy_Crane3LoadTime);
    conf->Write("oftinfoCrane3MoorTime", m_copy_Crane3MoorTime);
    conf->Write("oftinfoCrane3UnMoorTime", m_copy_Crane3UnMoorTime);
    // Crane 4
    conf->Write("oftinfoCrane4AreaEnable", m_copy_Crane4AreaEnable);
    conf->Write("oftinfoCrane4AreaEnable", m_copy_Crane4AreaVisible);
    conf->Write("oftinfoCrane4BargeDataVisible", m_copy_Crane4BargeDataVisible);
    conf->Write("oftinfoCrane4AreaAftTrig", m_copy_Crane4AreaAftTrig);
    conf->Write("oftinfoCrane4AreaBowTrig", m_copy_Crane4AreaBowTrig);
    m_copy_IntCrane4AreaColour = m_copy_Crane4AreaColour.GetRGB();  // red, green, blue
    conf->Write("oftinfoCrane4AreaColour", m_copy_IntCrane4AreaColour);
    //  Crane 4 barge
    conf->Write("oftinfoCrane4MMSI", m_copy_Crane4MMSI);
    conf->Write("oftinfoCrane4Name", m_copy_Crane4Name);
    conf->Write("oftinfoCrane4LoadTime", m_copy_Crane4LoadTime);
    conf->Write("oftinfoCrane4MoorTime", m_copy_Crane4MoorTime);
    conf->Write("oftinfoCrane4UnMoorTime", m_copy_Crane4UnMoorTime);

    conf->Write("DialogPosX", m_hr_dialog_x);
    conf->Write("DialogPosY", m_hr_dialog_y);
    conf->Write("DialogSizeX", m_hr_dialog_sx);
    conf->Write("DialogSizeY", m_hr_dialog_sy);
    
   return true;
 
}

void OFTinfoPi::OnOFTinfoDialogClose() {
   m_show_oftinfo = false;
  SetToolbarItemState(m_leftclick_tool_id, m_show_oftinfo);
  m_dialog->Hide();
  SaveConfig();

  RequestRefresh(m_parent_window);  // refresh main window
}

void OFTinfoPi::SetMainTaskPeriod() {
  int AISTransPeriod = 0;
  m_copy_AISTransPeriod.ToInt(&AISTransPeriod, 10);
  DebugMessage = "Start with " + m_copy_AISTransPeriod + "sec";
  wxMessageBox(DebugMessage, "OFTinfo_Timer");
  Start(1000 * AISTransPeriod, wxTIMER_CONTINUOUS);  // restart timer with new interval
}

//!!! main task cicle - timer tick
void OFTinfoPi::Notify() {
  m_AIS_Array = GetAISTargetArray();
  ArrayOfPlugIn_AIS_Targets AIS_Array = *m_AIS_Array;
  auto m_AIS_Array_capacity = to_string(AIS_Array.Count());
  // wxMessageBox(m_AIS_Array_capacity, "OFTinfo_AIS Target Array");
  if (m_copy_AisToFile) {  // transmit AIS targets to file
    auto AISTargetfilePath = m_copy_AISFilePath + m_copy_AisFileName;
    AISTargetfile = new wxTextFile(AISTargetfilePath);
    AISTargetfile->Open();
    AISTargetfile->Clear();
  }

  for (auto i = 0; i < AIS_Array.Count(); ++i) {
    auto AisTargetMessage =
        to_string(wxGetUTCTime()) + ";" + to_string(AIS_Array[i]->MMSI) +
        ";" + AIS_Array[i]->ShipName + ";" + to_string(AIS_Array[i]->Brg) +
        ";" + to_string(AIS_Array[i]->Range_NM) + ";" +
        to_string(AIS_Array[i]->Lon) + ";" + to_string(AIS_Array[i]->Lat) +
        ";" + to_string(AIS_Array[i]->HDG) + ";" +
        to_string(AIS_Array[i]->COG) + ";" + to_string(AIS_Array[i]->SOG) +
        ";" + to_string(int(AIS_Array[i]->ShipType));
        //+ ";" +
        //to_string(m_AIS_Array[i]->DimA) + ";" + to_string(m_AIS_Array[i]->DimB) + ";" +
        //to_string(m_AIS_Array[i]->DimC) + ";" + to_string(m_AIS_Array[i]->DimD);
    // wxMessageBox(AisTargetMessage, "AIS target");
    if (m_copy_AisToFile) {  // transmit AIS targets to file
      AISTargetfile->AddLine(AisTargetMessage);
    }
  }

  if (AISTargetfile) {
    AISTargetfile->Write();
    AISTargetfile->Close();
  }
}




