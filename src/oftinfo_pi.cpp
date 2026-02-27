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
      m_hr_dialog_x(0),
      m_hr_dialog_y(8),
      m_cursor_lat(0),
      m_cursor_lon(0),
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
    //may be need add preverence variamle?? gr
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
    }
  }
}

int OFTinfoPi::Init() {
  /**/ AddLocaleCatalog("opencpn-OFTinfo_pi");

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

  return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK |
          WANTS_TOOLBAR_CALLBACK | INSTALLS_TOOLBAR_TOOL | WANTS_CURSOR_LATLON |
          WANTS_NMEA_SENTENCES | WANTS_AIS_SENTENCES | WANTS_PREFERENCES |
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
    /* if (m_copy_use_nmea) {
      if (m_dialog->nmeastream->IsOpened()) {
        m_dialog->nmeastream->Write();
         m_dialog->nmeastream->Close();
      }
    }
    */
  

   if ((m_dialog->m_timer) && (m_dialog->m_timer->IsRunning())) {
    //  need to stop the timer or crash on exit
      m_dialog->m_timer->Stop();
   }
    m_dialog->Close();
    delete m_dialog;
    m_dialog = nullptr;

    m_show_oftinfo = false;
    SetToolbarItemState(m_leftclick_tool_id, m_show_oftinfo);
  }

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
    if (m_copy_AisToFile != copy_AisToFile) {
      m_copy_AisToFile = copy_AisToFile;
    }
    if (m_copy_AisToMQTT != copy_AisToMQTT) {
      m_copy_AisToMQTT = copy_AisToMQTT;
    }
    if (m_copy_AisToPSQL != copy_AisToPSQL) {
      m_copy_AisToPSQL = copy_AisToPSQL;
    }
    if (m_copy_AISTransPeriod != copy_AISTransPeriod) {
      m_copy_AISTransPeriod = copy_AISTransPeriod;
    }
    // Target filter
    if (m_copy_AISTargCargoOnly != copy_AISTargCargoOnly) {
      m_copy_AISTargCargoOnly = copy_AISTargCargoOnly;
    }
    if (m_copy_AISTargZeroInc != copy_AISTargZeroInc) {
      m_copy_AISTargZeroInc = copy_AISTargZeroInc;
    }
    // Own Ship
    if (m_copy_OwnMMSI != copy_OwnMMSI) {
      m_copy_OwnMMSI = copy_OwnMMSI;
    }
    if (m_copy_AISTransmitAIVDO != copy_AISTransmitAIVDO) {
      m_copy_AISTransmitAIVDO = copy_AISTransmitAIVDO;
    }
    // OFT
    if (m_copy_OFTMMSI1 != copy_OFTMMSI1) {
      m_copy_OFTMMSI1 = copy_OFTMMSI1;
    }
    if (m_copy_OFTMMSI2 != copy_OFTMMSI2) {
      m_copy_OFTMMSI2 = copy_OFTMMSI2;
    }
    // load areas
    if (m_copy_MonToFile != copy_MonToFile) {
      m_copy_MonToFile = copy_MonToFile;
    }
    if (m_copy_MonToMQTT != copy_MonToMQTT) {
      m_copy_MonToMQTT = copy_MonToMQTT;
    }
    if (m_copy_MonToPSQL != copy_MonToPSQL) {
      m_copy_MonToPSQL = copy_MonToPSQL;
    }
    if (m_copy_MonTransPeriod != copy_MonTransPeriod) {
      m_copy_MonTransPeriod = copy_MonTransPeriod;
    }
    // file
    if (m_copy_AisFileName != copy_AisFileName) {
      m_copy_AisFileName = copy_AisFileName;
    }
    if (m_copy_AISFilePath != copy_AISFilePath) {
      m_copy_AISFilePath = copy_AISFilePath;
    }
    // MQTT
    if (m_copy_MQTTBrokerIP != copy_MQTTBrokerIP) {
      m_copy_MQTTBrokerIP = copy_MQTTBrokerIP;
    }
    if (m_copy_MQTTBrokerPort != copy_MQTTBrokerPort) {
      m_copy_MQTTBrokerPort = copy_MQTTBrokerPort;
    }
    if (m_copy_MQTTclientID != copy_MQTTclientID) {
      m_copy_MQTTclientID = copy_MQTTclientID;
    }
    if (m_copy_MQTTuser != copy_MQTTuser) {
      m_copy_MQTTuser = copy_MQTTuser;
    }
    if (m_copy_MQTTpassw != copy_MQTTpassw) {
      m_copy_MQTTpassw = copy_MQTTpassw;
    }
    if (m_copy_MQTTPublishTopic != copy_MQTTPublishTopic) {
      m_copy_MQTTPublishTopic = copy_MQTTPublishTopic;
    }
    if (m_copy_MQTTSubscribeTopic != copy_MQTTSubscribeTopic) {
      m_copy_MQTTSubscribeTopic = copy_MQTTSubscribeTopic;
    }
    // Postgresql
    if (m_copy_SQLip != copy_SQLip) {
      m_copy_SQLip = copy_SQLip;
    }
    if (m_copy_SQLport != copy_SQLport) {
      m_copy_SQLport = copy_SQLport;
    }
    if (m_copy_SQLuser != copy_SQLuser) {
      m_copy_SQLuser = copy_SQLuser;
    }
    if (m_copy_SQLpassw != copy_SQLpassw) {
      m_copy_SQLpassw = copy_SQLpassw;
    }
    if (m_copy_SQLDBName != copy_SQLDBName) {
      m_copy_SQLDBName = copy_SQLDBName;
    }
    
    if (m_dialog) {
      // AIS Targets
      m_dialog->m_bAisToFile = m_copy_AisToFile;
      m_dialog->m_bAisToMQTT = m_copy_AisToMQTT;
      m_dialog->m_bAisToPSQL = m_copy_AisToPSQL;
      m_dialog->m_tAISTransPeriod = m_copy_AISTransPeriod;
      // Target filter
      m_dialog->m_bAISTargCargoOnly = m_copy_AISTargCargoOnly;
      m_dialog->m_bAISTargZeroInc = m_copy_AISTargZeroInc;
      // Own Ship
      m_dialog->m_tOwnMMSI = m_copy_OwnMMSI;
      m_dialog->m_bAISTransmitAIVDO = m_copy_AISTransmitAIVDO;
      // OFT
      m_dialog->m_tOFTMMSI1 = m_copy_OFTMMSI1;
      m_dialog->m_tOFTMMSI2 = m_copy_OFTMMSI2;
      // load areas
      m_dialog->m_bMonToFile = m_copy_MonToFile;
      m_dialog->m_bMonToMQTT = m_copy_MonToMQTT;
      m_dialog->m_bMonToPSQL = m_copy_MonToPSQL;
      m_dialog->m_tMonTransPeriod = m_copy_MonTransPeriod;
      // file
      m_dialog->m_tAisFileName = m_copy_AisFileName;
      m_dialog->m_tAISFilePath = m_copy_AISFilePath;
      // MQTT
      m_dialog->m_tMQTTBrokerIP = m_copy_MQTTBrokerIP;
      m_dialog->m_tMQTTBrokerPort = m_copy_MQTTBrokerPort;
      m_dialog->m_tMQTTclientID = m_copy_MQTTclientID;
      m_dialog->m_tMQTTuser = m_copy_MQTTuser;
      m_dialog->m_tMQTTpassw = m_copy_MQTTpassw;
      m_dialog->m_tMQTTPublishTopic = m_copy_MQTTPublishTopic;
      m_dialog->m_tMQTTSubscribeTopic = m_copy_MQTTSubscribeTopic;
      // Postgresql
      m_dialog->m_tSQLip = m_copy_SQLip;
      m_dialog->m_tSQLport = m_copy_SQLport;
      m_dialog->m_tSQLuser = m_copy_SQLuser;
      m_dialog->m_tSQLpassw = m_copy_SQLpassw;
      m_dialog->m_tSQLDBName = m_copy_SQLDBName;
    }

    SaveConfig();

    RequestRefresh(m_parent_window);  // refresh main window
  }

  delete pref;
  pref = nullptr;
  
}

void OFTinfoPi::OnToolbarToolCallback(int id) {
   if (!m_dialog) {
    m_dialog = new Dlg(m_parent_window);
    m_dialog->plugin = this;
    m_dialog->m_timer = new wxTimer(m_dialog);
    m_dialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
    m_dialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);

    wxMenu dummy_menu;
    m_position_menu_id = AddCanvasContextMenuItem(
        new wxMenuItem(&dummy_menu, -1, _("Select Vessel Start Position")),
        this);
    SetCanvasContextMenuItemViz(m_position_menu_id, true);
  }

  // m_pDialog->Fit();
  // Toggle
  m_show_oftinfo = !m_show_oftinfo;

  //    Toggle dialog?
  if (m_show_oftinfo) {
    m_dialog->Move(wxPoint(m_hr_dialog_x, m_hr_dialog_y));
    m_dialog->SetSize(m_hr_dialog_sx, m_hr_dialog_sy);
    m_dialog->Show();

  } else {
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
      m_copy_AisFileName = conf->Read("oftinfoAisFileName", "AISTargets");
      m_copy_AISFilePath = conf->Read("oftinfoAISFilePath", "C:\\scripts");
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
      m_copy_AisFileName = conf->Read("oftinfoAisFileName", "AISTargets");
      m_copy_AISFilePath = conf->Read("oftinfoAISFilePath", "C:\\scripts");
      // MQTT
      m_copy_MQTTBrokerIP = conf->Read("oftinfoMQTTBrokerIP", "127.0.0.1");
      m_copy_MQTTBrokerPort = conf->Read("oftinfoMQTTBrokerPort", "1883");
      m_copy_MQTTclientID = conf->Read("oftinfoMQTTclientID", "OFTinfoMain");
      m_copy_MQTTuser = conf->Read("oftinfoMQTTuser", "user");
      m_copy_MQTTpassw = conf->Read("oftinfoMQTTpassw", "password");
      m_copy_MQTTPublishTopic =
          conf->Read("oftinfoMQTTPublishTopic", "Cargo/OCPN");
      m_copy_MQTTSubscribeTopic =
          conf->Read("oftinfoMQTTSubscribeTopic", "Cargo/OCPN");
      // Postgresql
      m_copy_SQLip = conf->Read("oftinfoSQLip", "127.0.0.1");
      m_copy_SQLport = conf->Read("oftinfoSQLport", "5432");
      m_copy_SQLuser = conf->Read("oftinfoSQLuser", "user");
      m_copy_SQLpassw = conf->Read("oftinfoSQLpassw", "password");
      m_copy_SQLDBName = conf->Read("oftinfoSQLDBName", "cargo");

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




