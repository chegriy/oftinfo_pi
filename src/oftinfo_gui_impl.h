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

  // base dialog
  // Unload Area
  bool m_bUnloadAreaEnable;
  bool m_bUnloadAreaVisible;
  bool m_bOGVDataVisible;
  bool m_bUnloadAreaSTBD;
  bool m_bUnloadAreaPORT;
  wxString m_tUnloadAreaAftTrig;
  wxString m_tUnloadAreaBowTrig;
  wxString m_tUnloadAreaHist;
  wxString m_tUnloadAreaDistance;
  wxString m_tUnloadAreaLostTime;
  wxColour m_cUnloadAreaColour;
  int m_iUnloadAreaColour;
  // OGV
  wxString m_tOGVMMSI;
  wxString m_tOGVName;
  wxString m_tOGVLoadTime;
  wxString m_tOGVMoorTime;
  wxString m_tOGVUnMoorTime;
  // load Areas
  wxString m_tLoadAreaLostTime;
  wxString m_tLoadAreaHist;
  wxString m_tLoadAreaDistance;
  // Crane 1
  bool m_bCrane1AreaEnable;
  bool m_bCrane1AreaVisible;
  bool m_bCrane1BargeDataVisible;
  wxString m_tCrane1AreaAftTrig;
  wxString m_tCrane1AreaBowTrig;
  wxColour m_cCrane1AreaColour;
  int m_iCrane1AreaColour;
  // Crane 1 barge
  wxString m_tCrane1MMSI;
  wxString m_tCrane1Name;
  wxString m_tCrane1LoadTime;
  wxString m_tCrane1MoorTime;
  wxString m_tCrane1UnMoorTime;
  // Crane 2
  bool m_bCrane2AreaEnable;
  bool m_bCrane2AreaVisible;
  bool m_bCrane2BargeDataVisible;
  wxString m_tCrane2AreaAftTrig;
  wxString m_tCrane2AreaBowTrig;
  wxColour m_cCrane2AreaColour;
  int m_iCrane2AreaColour;
  // Crane 2 barge
  wxString m_tCrane2MMSI;
  wxString m_tCrane2Name;
  wxString m_tCrane2LoadTime;
  wxString m_tCrane2MoorTime;
  wxString m_tCrane2UnMoorTime;
  // Crane 3
  bool m_bCrane3AreaEnable;
  bool m_bCrane3AreaVisible;
  bool m_bCrane3BargeDataVisible;
  wxString m_tCrane3AreaAftTrig;
  wxString m_tCrane3AreaBowTrig;
  wxColour m_cCrane3AreaColour;
  int m_iCrane3AreaColour;
  // Crane 3 barge
  wxString m_tCrane3MMSI;
  wxString m_tCrane3Name;
  wxString m_tCrane3LoadTime;
  wxString m_tCrane3MoorTime;
  wxString m_tCrane3UnMoorTime;
  // Crane 4
  bool m_bCrane4AreaEnable;
  bool m_bCrane4AreaVisible;
  bool m_bCrane4BargeDataVisible;
  wxString m_tCrane4AreaAftTrig;
  wxString m_tCrane4AreaBowTrig;
  wxColour m_cCrane4AreaColour;
  int m_iCrane4AreaColour;
  // Crane 4 barge
  wxString m_tCrane4MMSI;
  wxString m_tCrane4Name;
  wxString m_tCrane4LoadTime;
  wxString m_tCrane4MoorTime;
  wxString m_tCrane4UnMoorTime;

  
};

#endif

