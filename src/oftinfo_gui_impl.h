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

#ifndef _HRGUI_IMPL_H_
#define _HRGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "oftinfo_pi.h"
#include "oftinfo_gui.h"
#include "ocpn_plugin.h"
#include "tinyxml.h"
#include "wx/process.h"
#include "json/reader.h"
#include "json/writer.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/listctrl.h>
#include <wx/stdpaths.h>
#include <wx/thread.h>
#include <wx/utils.h>
#include <wx/msgdlg.h>
#include <wx/arrstr.h>
#include <wx/vector.h>
#include <wx/dataobj.h>
#include <wx/list.h>
#include <wx/window.h>
#include <wx/menu.h>

#define ID_SOMETHING 2001
#define ID_SOMETHING_ELSE 2002

#define KNOT_2_KPH 1.852
#define METER_2_FEET 3.280839895
#define METER_2_FATHOM 0.5468066492

#ifdef __WXOSX__
#define OFTINFO_DLG_STYLE \
  wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxSTAY_ON_TOP
#else
#define OFTINFO_DLG_STYLE \
  wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
#endif
using namespace std;

class OFTinfoPi;

class Dlg : public OFTinfoBase {
public:
  Dlg(wxWindow* parent, wxWindowID id = wxID_ANY,
      const wxString& title = _("OFTinfo"),
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = OFTINFO_DLG_STYLE);
  OFTinfoPi* plugin;

  wxTimer* m_timer;

  // AIS Targets
  bool m_bAisToFile;
  bool m_bAisToMQTT;
  bool m_bAisToPSQL;
  wxString m_tAISTransPeriod;
  // Target filter
  bool m_bAISTargCargoOnly;
  bool m_bAISTargZeroInc;
  // Own Ship
  wxString m_tOwnMMSI;
  bool m_bAISTransmitAIVDO;
  // OFT
  wxString m_tOFTMMSI1;
  wxString m_tOFTMMSI2;
  // load areas
  bool m_bMonToFile;
  bool m_bMonToMQTT;
  bool m_bMonToPSQL;
  wxString m_tMonTransPeriod;
  // file
  wxString m_tAisFileName;
  wxString m_tAISFilePath;
  // MQTT
  wxString m_tMQTTBrokerIP;
  wxString m_tMQTTBrokerPort;
  wxString m_tMQTTclientID;
  wxString m_tMQTTuser;
  wxString m_tMQTTpassw;
  wxString m_tMQTTPublishTopic;
  wxString m_tMQTTSubscribeTopic;
  // Postgresql
  wxString m_tSQLip;
  wxString m_tSQLport;
  wxString m_tSQLuser;
  wxString m_tSQLpassw;
  wxString m_tSQLDBName;

  wxDateTime dt;
  
};

#endif

