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

#ifndef SDR_PI_H_
#define SDR_PI_H_


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include <wx/glcanvas.h>
#endif

#include <wx/fileconf.h>
#include <wx/datetime.h>
#include <wx/tokenzr.h>

#include "config.h"

#include "json/reader.h"
#include "json/writer.h"

#include "ocpn_plugin.h"  //Required for OCPN plugin functions
#include "oftinfo_gui_impl.h"


class Dlg;


//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define OFTinfo_TOOL_POSITION (-1)  ///< toolbar tool default positioning

class OFTinfoPi : public opencpn_plugin_118 {
public:
  explicit OFTinfoPi(void* ppimgr);
  ~OFTinfoPi() override;

  //    The required PlugIn Methods
  int Init() override;
  bool DeInit() override;

  int GetAPIVersionMajor() override;
  int GetAPIVersionMinor() override;
  int GetPlugInVersionMajor() override;
  int GetPlugInVersionMinor() override;
  int GetPlugInVersionPatch() override;
  int GetPlugInVersionPost() override;
  const char* GetPlugInVersionPre() override;
  const char* GetPlugInVersionBuild() override;

  wxBitmap* GetPlugInBitmap() override;
  wxString GetCommonName() override;
  wxString GetShortDescription() override;
  wxString GetLongDescription() override;

  //    The required override PlugIn Methods
  int GetToolbarToolCount() override;
  void OnToolbarToolCallback(int id) override;

  //    Optional plugin overrides
  void SetColorScheme(PI_ColorScheme cs) override;

  //    The override PlugIn Methods
 // void OnContextMenuItemCallback(int id) override;
 // void SetCursorLatLon(double lat, double lon) override;

  //    Other public methods
  void SetOFTinfoDialogX(int x) { m_hr_dialog_x = x; };
  void SetOFTinfoDialogY(int x) { m_hr_dialog_y = x; };
  void SetOFTinfoDialogWidth(int x) { m_hr_dialog_width = x; };
  void SetOFTinfoDialogHeight(int x) { m_hr_dialog_height = x; };
  void SetOFTinfoDialogSizeX(int x) { m_hr_dialog_sx = x; }
  void SetOFTinfoDialogSizeY(int x) { m_hr_dialog_sy = x; }
  void OnOFTinfoDialogClose();

  int m_hr_dialog_x, m_hr_dialog_y;

  [[nodiscard]] double GetCursorLat() const { return m_cursor_lat; }
  [[nodiscard]] double GetCursorLon() const { return m_cursor_lon; }

  void ShowPreferencesDialog(wxWindow* parent) override;
//  void SetPluginMessage(wxString& message_id, wxString& message_body) override;
 
  wxBitmap m_panel_bitmap;

private:
  double m_cursor_lat;
  double m_cursor_lon;

  int m_position_menu_id;
  double m_gui_scale_factor;

  OFTinfoPi* plugin;

  Dlg* m_dialog;

  wxFileConfig* m_config;
  wxWindow* m_parent_window;
  bool LoadConfig();
  bool SaveConfig();

  int m_hr_dialog_width, m_hr_dialog_height;
  int m_hr_dialog_sx, m_hr_dialog_sy;
  int m_display_width, m_display_height;
  int m_leftclick_tool_id;
  bool m_show_oftinfo_icon;
  bool m_show_oftinfo;

  //preference dialog
  // AIS Targets
  bool m_copy_AisToFile;
  bool m_copy_AisToMQTT;
  bool m_copy_AisToPSQL;
  wxString m_copy_AISTransPeriod;
  // Target filter
  bool m_copy_AISTargCargoOnly;
  bool m_copy_AISTargZeroInc;
  //Own Ship
  wxString m_copy_OwnMMSI;
  bool m_copy_AISTransmitAIVDO;
  // OFT
  wxString m_copy_OFTMMSI1;
  wxString m_copy_OFTMMSI2;
  //load areas
  bool m_copy_MonToFile;
  bool m_copy_MonToMQTT;
  bool m_copy_MonToPSQL;
  wxString m_copy_MonTransPeriod;
  //file
  wxString m_copy_AisFileName;
  wxString m_copy_AISFilePath;
  //MQTT
  wxString m_copy_MQTTBrokerIP;
  wxString m_copy_MQTTBrokerPort;
  wxString m_copy_MQTTclientID;
  wxString m_copy_MQTTuser;
  wxString m_copy_MQTTpassw;
  wxString m_copy_MQTTPublishTopic;
  wxString m_copy_MQTTSubscribeTopic;
  //Postgresql
  wxString m_copy_SQLip;
  wxString m_copy_SQLport;
  wxString m_copy_SQLuser;
  wxString m_copy_SQLpassw;
  wxString m_copy_SQLDBName;

};

#endif
