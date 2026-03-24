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
 
  
 
}






