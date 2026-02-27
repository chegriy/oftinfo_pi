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

#include <stdio.h>

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/progdlg.h>
#include <wx/textfile.h>
#include <wx/timer.h>
#include <wx/wx.h>
#include "wx/tglbtn.h"

#include "qtstylesheet.h"
#include "oftinfo_gui_impl.h"
#include "oftinfo_pi.h"


#include <wx/listimpl.cpp>
WX_DEFINE_LIST(Plugin_WaypointExList);

//void assign(char* dest, char* arrTest2) { strcpy(dest, arrTest2); }

#define BUFSIZE 0x10000

Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title,
         const wxPoint& pos, const wxSize& size, long style)
    : OFTinfoBase(parent, id, title, pos, size, style) {
  this->Fit();
 
  wxFileConfig* pConf = GetOCPNConfigObject();

  if (pConf) {
    pConf->SetPath("/PlugIns/OFTinfo_pi");

    // AIS Targets
    pConf->Read("oftinfoAisToFile", &m_bAisToFile, 1);
    pConf->Read("oftinfoAisToMQTT", &m_bAisToMQTT, 0);
    pConf->Read("oftinfoAisToPSQL", &m_bAisToPSQL, 0);
    pConf->Read("oftinfoAISTransPeriod", &m_tAISTransPeriod, "20");
    // Target filter
    pConf->Read("oftinfoAISTargCargoOnly", &m_bAISTargCargoOnly, 1);
    pConf->Read("oftinfoAisToAISTargZeroInc", &m_bAISTargZeroInc, 0);
    // Own Ship
    pConf->Read("oftinfoOwnMMSI", &m_tOwnMMSI, "123456789");
    pConf->Read("oftinfoAISTransmitAIVDO", &m_bAISTransmitAIVDO, 1);
    // OFT
    pConf->Read("oftinfoOFTMMSI1", &m_tOFTMMSI1, "123456789");
    pConf->Read("oftinfoOFTMMSI2", &m_tOFTMMSI2, "123456789");
    // load areas
    pConf->Read("oftinfoMonToFile", &m_bMonToFile, 1);
    pConf->Read("oftinfoMonToMQTT", &m_bMonToMQTT, 0);
    pConf->Read("oftinfoMonToPSQL", &m_bMonToPSQL, 0);
    pConf->Read("oftinfoMonTransPeriod", &m_tMonTransPeriod, "20");
    // file
    pConf->Read("oftinfoAisFileName", &m_tAisFileName, "AISTargets");
    pConf->Read("oftinfoAISFilePath", &m_tAISFilePath, "C:\\scripts");
    // MQTT
    pConf->Read("oftinfoMQTTBrokerIP", &m_tMQTTBrokerIP, "127.0.0.1");
    pConf->Read("oftinfoMQTTBrokerPort", &m_tMQTTBrokerPort, "1883");
    pConf->Read("oftinfoMQTTclientID", &m_tMQTTclientID, "OFTinfoMain");
    pConf->Read("oftinfoMQTTuser", &m_tMQTTuser, "user");
    pConf->Read("oftinfoMQTTpassw", &m_tMQTTpassw, "password");
    pConf->Read("oftinfoMQTTPublishTopic", &m_tMQTTPublishTopic, "Cargo/OCPN");
    pConf->Read("oftinfoMQTTSubscribeTopic", &m_tMQTTSubscribeTopic, "Cargo/OCPN");
    // Postgresql
    pConf->Read("oftinfoSQLip", &m_tSQLip, "127.0.0.1");
    pConf->Read("oftinfoSQLport", &m_tSQLport, "5432");
    pConf->Read("oftinfoSQLuser", &m_tSQLuser, "user");
    pConf->Read("oftinfoSQLpassw", &m_tSQLpassw, "password");
    pConf->Read("oftinfoSQLDBName", &m_tSQLDBName, "cargo");
  }
}




