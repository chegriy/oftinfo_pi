///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "oftinfo_gui.h"

///////////////////////////////////////////////////////////////////////////

OFTinfoBase::OFTinfoBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	this->SetBackgroundColour( wxColour( 201, 201, 201 ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Unload area") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer3->AddGrowableCol( 2 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbUnloadAreaEnable = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbUnloadAreaEnable->SetValue(true);
	fgSizer3->Add( m_cbUnloadAreaEnable, 0, wxALL, 5 );

	m_cbUnloadAreaVisible = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbUnloadAreaVisible->SetValue(true);
	fgSizer3->Add( m_cbUnloadAreaVisible, 0, wxALL, 5 );

	m_cbOGVDataVisible = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, _("OGV Data Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbOGVDataVisible->SetValue(true);
	fgSizer3->Add( m_cbOGVDataVisible, 0, wxALL, 5 );


	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_cbUnloadAreaSTBD = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, _("STBD"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_cbUnloadAreaSTBD, 0, wxALL, 5 );

	m_cbUnloadAreaPORT = new wxCheckBox( sbSizer3->GetStaticBox(), wxID_ANY, _("PORT"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_cbUnloadAreaPORT, 0, wxALL, 5 );


	sbSizer3->Add( fgSizer3, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer5->AddGrowableCol( 1 );
	fgSizer5->AddGrowableCol( 3 );
	fgSizer5->AddGrowableCol( 5 );
	fgSizer5->AddGrowableCol( 7 );
	fgSizer5->AddGrowableRow( 0 );
	fgSizer5->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticUnloadAreaAftTrig = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Afr Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaAftTrig->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaAftTrig, 0, wxALL, 5 );

	m_textCtrlUnloadAreaAftTrig = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlUnloadAreaAftTrig, 0, wxALL, 5 );

	m_staticUnloadAreaBowTrig = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Bow Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaBowTrig->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaBowTrig, 0, wxALL, 5 );

	m_textCtrlUnloadAreaBowTrig = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlUnloadAreaBowTrig, 0, wxALL, 5 );

	m_staticUnloadAreaAftTrig1 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Hyst(m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaAftTrig1->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaAftTrig1, 0, wxALL, 5 );

	m_textCtrlUnloadAreaHist = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlUnloadAreaHist, 0, wxALL, 5 );

	m_staticUnloadAreaAftTrig21 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Distance(m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaAftTrig21->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaAftTrig21, 0, wxALL, 5 );

	m_textCtrlUnloadAreaDistance = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlUnloadAreaDistance, 0, wxALL, 5 );

	m_staticUnloadAreaLostTime = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Lost after (min):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaLostTime->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaLostTime, 0, wxALL, 5 );

	m_textCtrlUnloadAreaLostTime = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( m_textCtrlUnloadAreaLostTime, 0, wxALL, 5 );

	m_staticUnloadAreaColourPicker = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaColourPicker->Wrap( -1 );
	fgSizer5->Add( m_staticUnloadAreaColourPicker, 0, wxALL, 5 );

	m_colourPickerUnloadArea = new wxColourPickerCtrl( sbSizer3->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer5->Add( m_colourPickerUnloadArea, 0, wxALL, 5 );


	sbSizer3->Add( fgSizer5, 0, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5 );

	wxFlexGridSizer* fgSizer52;
	fgSizer52 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer52->AddGrowableCol( 3 );
	fgSizer52->AddGrowableRow( 0 );
	fgSizer52->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer52->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticOGVMMSI = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("OGV MMSI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticOGVMMSI->Wrap( -1 );
	fgSizer52->Add( m_staticOGVMMSI, 0, wxALL, 5 );

	m_textCtrlOGVMMSI = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52->Add( m_textCtrlOGVMMSI, 0, wxALL, 5 );

	m_statiOGVName = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("OGV name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiOGVName->Wrap( -1 );
	fgSizer52->Add( m_statiOGVName, 0, wxALL, 5 );

	m_textCtrlOGVName = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52->Add( m_textCtrlOGVName, 0, wxALL|wxEXPAND, 5 );

	m_staticOGVLoadTime = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Loading Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticOGVLoadTime->Wrap( -1 );
	fgSizer52->Add( m_staticOGVLoadTime, 0, wxALL, 5 );

	m_textCtrlOGVLoadTime = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52->Add( m_textCtrlOGVLoadTime, 0, wxALL, 5 );


	sbSizer3->Add( fgSizer52, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer521;
	fgSizer521 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer521->AddGrowableCol( 1 );
	fgSizer521->AddGrowableCol( 3 );
	fgSizer521->AddGrowableRow( 0 );
	fgSizer521->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer521->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticOGVMoorTime = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Mooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticOGVMoorTime->Wrap( -1 );
	fgSizer521->Add( m_staticOGVMoorTime, 0, wxALL, 5 );

	m_textCtrlOGVMoorTime = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer521->Add( m_textCtrlOGVMoorTime, 0, wxALL|wxEXPAND, 5 );

	m_statiOGVUnMoorTime = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Unmooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiOGVUnMoorTime->Wrap( -1 );
	fgSizer521->Add( m_statiOGVUnMoorTime, 0, wxALL, 5 );

	m_textCtrlOGVUnMoorTime = new wxTextCtrl( sbSizer3->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer521->Add( m_textCtrlOGVUnMoorTime, 0, wxALL|wxEXPAND, 5 );


	sbSizer3->Add( fgSizer521, 1, wxEXPAND, 5 );


	bSizer10->Add( sbSizer3, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Load areas") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer51;
	fgSizer51 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer51->AddGrowableCol( 1 );
	fgSizer51->AddGrowableCol( 3 );
	fgSizer51->AddGrowableCol( 5 );
	fgSizer51->AddGrowableCol( 7 );
	fgSizer51->AddGrowableRow( 0 );
	fgSizer51->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer51->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticUnloadAreaLostTime2 = new wxStaticText( sbSizer31->GetStaticBox(), wxID_ANY, _("Lost after (min):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaLostTime2->Wrap( -1 );
	fgSizer51->Add( m_staticUnloadAreaLostTime2, 0, wxALL, 5 );

	m_textCtrlLoadAreaLostTime = new wxTextCtrl( sbSizer31->GetStaticBox(), wxID_ANY, _("60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer51->Add( m_textCtrlLoadAreaLostTime, 0, wxALL, 5 );


	fgSizer51->Add( 0, 0, 1, wxEXPAND, 5 );


	fgSizer51->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticUnloadAreaAftTrig11 = new wxStaticText( sbSizer31->GetStaticBox(), wxID_ANY, _("Hyst(m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaAftTrig11->Wrap( -1 );
	fgSizer51->Add( m_staticUnloadAreaAftTrig11, 0, wxALL, 5 );

	m_textCtrlLoadAreaHist = new wxTextCtrl( sbSizer31->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer51->Add( m_textCtrlLoadAreaHist, 0, wxALL, 5 );

	m_staticUnloadAreaAftTrig211 = new wxStaticText( sbSizer31->GetStaticBox(), wxID_ANY, _("Distance(m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticUnloadAreaAftTrig211->Wrap( -1 );
	fgSizer51->Add( m_staticUnloadAreaAftTrig211, 0, wxALL, 5 );

	m_textCtrlLoadAreaDistance = new wxTextCtrl( sbSizer31->GetStaticBox(), wxID_ANY, _("60"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer51->Add( m_textCtrlLoadAreaDistance, 0, wxALL, 5 );


	sbSizer31->Add( fgSizer51, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 4, 1, 10, 0 );
	fgSizer25->AddGrowableRow( 0 );
	fgSizer25->AddGrowableRow( 1 );
	fgSizer25->AddGrowableRow( 2 );
	fgSizer25->AddGrowableRow( 3 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_collapsiblePane1 = new wxCollapsiblePane( sbSizer31->GetStaticBox(), wxID_ANY, _("Crane 1"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE );
	m_collapsiblePane1->Collapse( false );

	wxStaticBoxSizer* sbSizer311;
	sbSizer311 = new wxStaticBoxSizer( new wxStaticBox( m_collapsiblePane1->GetPane(), wxID_ANY, _("Crane 1 load area") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer311;
	fgSizer311 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer311->AddGrowableCol( -1 );
	fgSizer311->AddGrowableRow( 0 );
	fgSizer311->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer311->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbCrane1AreaEnable = new wxCheckBox( sbSizer311->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCrane1AreaEnable->SetValue(true);
	fgSizer311->Add( m_cbCrane1AreaEnable, 0, wxALL, 5 );

	m_cbCrane1AreaVisible = new wxCheckBox( sbSizer311->GetStaticBox(), wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCrane1AreaVisible->SetValue(true);
	fgSizer311->Add( m_cbCrane1AreaVisible, 0, wxALL, 5 );

	m_cbCrane1BargeDataVisible = new wxCheckBox( sbSizer311->GetStaticBox(), wxID_ANY, _("Barge Data Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbCrane1BargeDataVisible->SetValue(true);
	fgSizer311->Add( m_cbCrane1BargeDataVisible, 0, wxALL, 5 );


	sbSizer311->Add( fgSizer311, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer511;
	fgSizer511 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer511->AddGrowableCol( 3 );
	fgSizer511->AddGrowableRow( 0 );
	fgSizer511->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer511->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneAreaAftTrig = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Afr Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaAftTrig->Wrap( -1 );
	fgSizer511->Add( m_staticCraneAreaAftTrig, 0, wxALL, 5 );

	m_textCtrlCrane1AreaAftTrig = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("70"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer511->Add( m_textCtrlCrane1AreaAftTrig, 0, wxALL, 5 );

	m_staticCraneAreaBowTrig = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Bow Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaBowTrig->Wrap( -1 );
	fgSizer511->Add( m_staticCraneAreaBowTrig, 0, wxALL, 5 );

	m_textCtrlCrane1AreaBowTrig = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("70"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer511->Add( m_textCtrlCrane1AreaBowTrig, 0, wxALL, 5 );

	m_staticCraneAreaColorPicker = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaColorPicker->Wrap( -1 );
	fgSizer511->Add( m_staticCraneAreaColorPicker, 0, wxALL, 5 );

	m_colourPickerCrane1Area = new wxColourPickerCtrl( sbSizer311->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer511->Add( m_colourPickerCrane1Area, 0, wxALL, 5 );


	sbSizer311->Add( fgSizer511, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer522;
	fgSizer522 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer522->AddGrowableCol( 3 );
	fgSizer522->AddGrowableRow( 0 );
	fgSizer522->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer522->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMMSI = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Barge MMSI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMMSI->Wrap( -1 );
	fgSizer522->Add( m_staticCraneMMSI, 0, wxALL, 5 );

	m_textCtrlCrane1MMSI = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer522->Add( m_textCtrlCrane1MMSI, 0, wxALL, 5 );

	m_statiCraneName = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Barge name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneName->Wrap( -1 );
	fgSizer522->Add( m_statiCraneName, 0, wxALL, 5 );

	m_textCtrlCrane1Name = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer522->Add( m_textCtrlCrane1Name, 0, wxALL|wxEXPAND, 5 );

	m_staticCraneLoadTime = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Loading Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneLoadTime->Wrap( -1 );
	fgSizer522->Add( m_staticCraneLoadTime, 0, wxALL, 5 );

	m_textCtrlCrane1LoadTime = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer522->Add( m_textCtrlCrane1LoadTime, 0, wxALL, 5 );


	sbSizer311->Add( fgSizer522, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5211;
	fgSizer5211 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer5211->AddGrowableCol( 1 );
	fgSizer5211->AddGrowableCol( 3 );
	fgSizer5211->AddGrowableRow( 0 );
	fgSizer5211->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5211->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMoorTime = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Mooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMoorTime->Wrap( -1 );
	fgSizer5211->Add( m_staticCraneMoorTime, 0, wxALL, 5 );

	m_textCtrlCrane1MoorTime = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5211->Add( m_textCtrlCrane1MoorTime, 0, wxALL|wxEXPAND, 5 );

	m_statiCraneUnMoorTime = new wxStaticText( sbSizer311->GetStaticBox(), wxID_ANY, _("Unmooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneUnMoorTime->Wrap( -1 );
	fgSizer5211->Add( m_statiCraneUnMoorTime, 0, wxALL, 5 );

	m_textCtrlCrane1UnMoorTime = new wxTextCtrl( sbSizer311->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5211->Add( m_textCtrlCrane1UnMoorTime, 0, wxALL|wxEXPAND, 5 );


	sbSizer311->Add( fgSizer5211, 1, wxEXPAND, 5 );


	m_collapsiblePane1->GetPane()->SetSizer( sbSizer311 );
	m_collapsiblePane1->GetPane()->Layout();
	sbSizer311->Fit( m_collapsiblePane1->GetPane() );
	fgSizer25->Add( m_collapsiblePane1, 1, wxALL|wxEXPAND, 5 );

	m_collapsiblePane2 = new wxCollapsiblePane( sbSizer31->GetStaticBox(), wxID_ANY, _("Crane 2"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE );
	m_collapsiblePane2->Collapse( true );

	wxStaticBoxSizer* sbSizer3111;
	sbSizer3111 = new wxStaticBoxSizer( new wxStaticBox( m_collapsiblePane2->GetPane(), wxID_ANY, _("Crane 2 load area") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3111;
	fgSizer3111 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer3111->AddGrowableCol( -1 );
	fgSizer3111->AddGrowableRow( 0 );
	fgSizer3111->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbCrane2AreaEnable = new wxCheckBox( sbSizer3111->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3111->Add( m_cbCrane2AreaEnable, 0, wxALL, 5 );

	m_cbCrane2AreaVisible = new wxCheckBox( sbSizer3111->GetStaticBox(), wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3111->Add( m_cbCrane2AreaVisible, 0, wxALL, 5 );

	m_cbCrane2BargeDataVisible = new wxCheckBox( sbSizer3111->GetStaticBox(), wxID_ANY, _("Barge Data Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3111->Add( m_cbCrane2BargeDataVisible, 0, wxALL, 5 );


	sbSizer3111->Add( fgSizer3111, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5111;
	fgSizer5111 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer5111->AddGrowableCol( 3 );
	fgSizer5111->AddGrowableRow( 0 );
	fgSizer5111->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneAreaAftTrig1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Afr Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaAftTrig1->Wrap( -1 );
	fgSizer5111->Add( m_staticCraneAreaAftTrig1, 0, wxALL, 5 );

	m_textCtrlCrane2AreaAftTrig = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5111->Add( m_textCtrlCrane2AreaAftTrig, 0, wxALL, 5 );

	m_staticCraneAreaBowTrig1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Bow Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaBowTrig1->Wrap( -1 );
	fgSizer5111->Add( m_staticCraneAreaBowTrig1, 0, wxALL, 5 );

	m_textCtrlCrane2AreaBowTrig = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5111->Add( m_textCtrlCrane2AreaBowTrig, 0, wxALL, 5 );

	m_staticCraneAreaColorPicker1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaColorPicker1->Wrap( -1 );
	fgSizer5111->Add( m_staticCraneAreaColorPicker1, 0, wxALL, 5 );

	m_colourPickerCrane2Area = new wxColourPickerCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer5111->Add( m_colourPickerCrane2Area, 0, wxALL, 5 );


	sbSizer3111->Add( fgSizer5111, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5221;
	fgSizer5221 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer5221->AddGrowableCol( 3 );
	fgSizer5221->AddGrowableRow( 0 );
	fgSizer5221->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5221->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMMSI1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Barge MMSI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMMSI1->Wrap( -1 );
	fgSizer5221->Add( m_staticCraneMMSI1, 0, wxALL, 5 );

	m_textCtrlCrane2MMSI = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5221->Add( m_textCtrlCrane2MMSI, 0, wxALL, 5 );

	m_statiCraneName1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Barge name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneName1->Wrap( -1 );
	fgSizer5221->Add( m_statiCraneName1, 0, wxALL, 5 );

	m_textCtrlCrane2Name = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5221->Add( m_textCtrlCrane2Name, 0, wxALL|wxEXPAND, 5 );

	m_staticCraneLoadTime1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Loading Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneLoadTime1->Wrap( -1 );
	fgSizer5221->Add( m_staticCraneLoadTime1, 0, wxALL, 5 );

	m_textCtrlCrane2LoadTime = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5221->Add( m_textCtrlCrane2LoadTime, 0, wxALL, 5 );


	sbSizer3111->Add( fgSizer5221, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer52111;
	fgSizer52111 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer52111->AddGrowableCol( 1 );
	fgSizer52111->AddGrowableCol( 3 );
	fgSizer52111->AddGrowableRow( 0 );
	fgSizer52111->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer52111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMoorTime1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Mooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMoorTime1->Wrap( -1 );
	fgSizer52111->Add( m_staticCraneMoorTime1, 0, wxALL, 5 );

	m_textCtrlCrane2MoorTime = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52111->Add( m_textCtrlCrane2MoorTime, 0, wxALL|wxEXPAND, 5 );

	m_statiCraneUnMoorTime1 = new wxStaticText( sbSizer3111->GetStaticBox(), wxID_ANY, _("Unmooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneUnMoorTime1->Wrap( -1 );
	fgSizer52111->Add( m_statiCraneUnMoorTime1, 0, wxALL, 5 );

	m_textCtrlCrane2UnMoorTime = new wxTextCtrl( sbSizer3111->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52111->Add( m_textCtrlCrane2UnMoorTime, 0, wxALL|wxEXPAND, 5 );


	sbSizer3111->Add( fgSizer52111, 1, wxEXPAND, 5 );


	m_collapsiblePane2->GetPane()->SetSizer( sbSizer3111 );
	m_collapsiblePane2->GetPane()->Layout();
	sbSizer3111->Fit( m_collapsiblePane2->GetPane() );
	fgSizer25->Add( m_collapsiblePane2, 1, wxEXPAND | wxALL, 5 );

	m_collapsiblePane3 = new wxCollapsiblePane( sbSizer31->GetStaticBox(), wxID_ANY, _("Crane 3"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE );
	m_collapsiblePane3->Collapse( true );

	wxStaticBoxSizer* sbSizer3112;
	sbSizer3112 = new wxStaticBoxSizer( new wxStaticBox( m_collapsiblePane3->GetPane(), wxID_ANY, _("Crane 3 load area") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3112;
	fgSizer3112 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer3112->AddGrowableCol( -1 );
	fgSizer3112->AddGrowableRow( 0 );
	fgSizer3112->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3112->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbCrane3AreaEnable = new wxCheckBox( sbSizer3112->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3112->Add( m_cbCrane3AreaEnable, 0, wxALL, 5 );

	m_cbCrane3AreaVisible = new wxCheckBox( sbSizer3112->GetStaticBox(), wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3112->Add( m_cbCrane3AreaVisible, 0, wxALL, 5 );

	m_cbCrane3BargeDataVisible = new wxCheckBox( sbSizer3112->GetStaticBox(), wxID_ANY, _("Barge Data Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3112->Add( m_cbCrane3BargeDataVisible, 0, wxALL, 5 );


	sbSizer3112->Add( fgSizer3112, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5112;
	fgSizer5112 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer5112->AddGrowableCol( 3 );
	fgSizer5112->AddGrowableRow( 0 );
	fgSizer5112->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5112->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneAreaAftTrig2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Afr Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaAftTrig2->Wrap( -1 );
	fgSizer5112->Add( m_staticCraneAreaAftTrig2, 0, wxALL, 5 );

	m_textCtrlCrane3AreaAftTrig = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5112->Add( m_textCtrlCrane3AreaAftTrig, 0, wxALL, 5 );

	m_staticCraneAreaBowTrig2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Bow Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaBowTrig2->Wrap( -1 );
	fgSizer5112->Add( m_staticCraneAreaBowTrig2, 0, wxALL, 5 );

	m_textCtrlCrane3AreaBowTrig = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5112->Add( m_textCtrlCrane3AreaBowTrig, 0, wxALL, 5 );

	m_staticCraneAreaColorPicker2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaColorPicker2->Wrap( -1 );
	fgSizer5112->Add( m_staticCraneAreaColorPicker2, 0, wxALL, 5 );

	m_colourPickerCrane3Area = new wxColourPickerCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer5112->Add( m_colourPickerCrane3Area, 0, wxALL, 5 );


	sbSizer3112->Add( fgSizer5112, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5222;
	fgSizer5222 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer5222->AddGrowableCol( 3 );
	fgSizer5222->AddGrowableRow( 0 );
	fgSizer5222->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5222->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMMSI2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Barge MMSI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMMSI2->Wrap( -1 );
	fgSizer5222->Add( m_staticCraneMMSI2, 0, wxALL, 5 );

	m_textCtrlCrane3MMSI = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5222->Add( m_textCtrlCrane3MMSI, 0, wxALL, 5 );

	m_statiCraneName2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Barge name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneName2->Wrap( -1 );
	fgSizer5222->Add( m_statiCraneName2, 0, wxALL, 5 );

	m_textCtrlCrane3Name = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5222->Add( m_textCtrlCrane3Name, 0, wxALL|wxEXPAND, 5 );

	m_staticCraneLoadTime2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Loading Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneLoadTime2->Wrap( -1 );
	fgSizer5222->Add( m_staticCraneLoadTime2, 0, wxALL, 5 );

	m_textCtrlCrane3LoadTime = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5222->Add( m_textCtrlCrane3LoadTime, 0, wxALL, 5 );


	sbSizer3112->Add( fgSizer5222, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer52112;
	fgSizer52112 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer52112->AddGrowableCol( 1 );
	fgSizer52112->AddGrowableCol( 3 );
	fgSizer52112->AddGrowableRow( 0 );
	fgSizer52112->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer52112->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMoorTime2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Mooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMoorTime2->Wrap( -1 );
	fgSizer52112->Add( m_staticCraneMoorTime2, 0, wxALL, 5 );

	m_textCtrlCrane3MoorTime = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52112->Add( m_textCtrlCrane3MoorTime, 0, wxALL|wxEXPAND, 5 );

	m_statiCraneUnMoorTime2 = new wxStaticText( sbSizer3112->GetStaticBox(), wxID_ANY, _("Unmooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneUnMoorTime2->Wrap( -1 );
	fgSizer52112->Add( m_statiCraneUnMoorTime2, 0, wxALL, 5 );

	m_textCtrlCrane3UnMoorTime = new wxTextCtrl( sbSizer3112->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52112->Add( m_textCtrlCrane3UnMoorTime, 0, wxALL|wxEXPAND, 5 );


	sbSizer3112->Add( fgSizer52112, 1, wxEXPAND, 5 );


	m_collapsiblePane3->GetPane()->SetSizer( sbSizer3112 );
	m_collapsiblePane3->GetPane()->Layout();
	sbSizer3112->Fit( m_collapsiblePane3->GetPane() );
	fgSizer25->Add( m_collapsiblePane3, 1, wxEXPAND | wxALL, 5 );

	m_collapsiblePane4 = new wxCollapsiblePane( sbSizer31->GetStaticBox(), wxID_ANY, _("Crane 4"), wxDefaultPosition, wxDefaultSize, wxCP_DEFAULT_STYLE );
	m_collapsiblePane4->Collapse( true );

	wxStaticBoxSizer* sbSizer3113;
	sbSizer3113 = new wxStaticBoxSizer( new wxStaticBox( m_collapsiblePane4->GetPane(), wxID_ANY, _("Crane 4 load area") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer3113;
	fgSizer3113 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer3113->AddGrowableCol( -1 );
	fgSizer3113->AddGrowableRow( 0 );
	fgSizer3113->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3113->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbCrane4AreaEnable = new wxCheckBox( sbSizer3113->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3113->Add( m_cbCrane4AreaEnable, 0, wxALL, 5 );

	m_cbCrane4AreaVisible = new wxCheckBox( sbSizer3113->GetStaticBox(), wxID_ANY, _("Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3113->Add( m_cbCrane4AreaVisible, 0, wxALL, 5 );

	m_cbCrane4BargeDataVisible = new wxCheckBox( sbSizer3113->GetStaticBox(), wxID_ANY, _("Barge Data Visible"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3113->Add( m_cbCrane4BargeDataVisible, 0, wxALL, 5 );


	sbSizer3113->Add( fgSizer3113, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5113;
	fgSizer5113 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer5113->AddGrowableCol( 3 );
	fgSizer5113->AddGrowableRow( 0 );
	fgSizer5113->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5113->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneAreaAftTrig3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Afr Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaAftTrig3->Wrap( -1 );
	fgSizer5113->Add( m_staticCraneAreaAftTrig3, 0, wxALL, 5 );

	m_textCtrlCrane4AreaAftTrig = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5113->Add( m_textCtrlCrane4AreaAftTrig, 0, wxALL, 5 );

	m_staticCraneAreaBowTrig3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Bow Trigger (m):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaBowTrig3->Wrap( -1 );
	fgSizer5113->Add( m_staticCraneAreaBowTrig3, 0, wxALL, 5 );

	m_textCtrlCrane4AreaBowTrig = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5113->Add( m_textCtrlCrane4AreaBowTrig, 0, wxALL, 5 );

	m_staticCraneAreaColorPicker3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneAreaColorPicker3->Wrap( -1 );
	fgSizer5113->Add( m_staticCraneAreaColorPicker3, 0, wxALL, 5 );

	m_colourPickerCrane4Area = new wxColourPickerCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer5113->Add( m_colourPickerCrane4Area, 0, wxALL, 5 );


	sbSizer3113->Add( fgSizer5113, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer5223;
	fgSizer5223 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer5223->AddGrowableCol( 3 );
	fgSizer5223->AddGrowableRow( 0 );
	fgSizer5223->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer5223->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMMSI3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Barge MMSI:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMMSI3->Wrap( -1 );
	fgSizer5223->Add( m_staticCraneMMSI3, 0, wxALL, 5 );

	m_textCtrlCrane4MMSI = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5223->Add( m_textCtrlCrane4MMSI, 0, wxALL, 5 );

	m_statiCraneName3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Barge name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneName3->Wrap( -1 );
	fgSizer5223->Add( m_statiCraneName3, 0, wxALL, 5 );

	m_textCtrlCrane4Name = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5223->Add( m_textCtrlCrane4Name, 0, wxALL|wxEXPAND, 5 );

	m_staticCraneLoadTime3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Loading Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneLoadTime3->Wrap( -1 );
	fgSizer5223->Add( m_staticCraneLoadTime3, 0, wxALL, 5 );

	m_textCtrlCrane4LoadTime = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5223->Add( m_textCtrlCrane4LoadTime, 0, wxALL, 5 );


	sbSizer3113->Add( fgSizer5223, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer52113;
	fgSizer52113 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer52113->AddGrowableCol( 1 );
	fgSizer52113->AddGrowableCol( 3 );
	fgSizer52113->AddGrowableRow( 0 );
	fgSizer52113->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer52113->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticCraneMoorTime3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Mooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticCraneMoorTime3->Wrap( -1 );
	fgSizer52113->Add( m_staticCraneMoorTime3, 0, wxALL, 5 );

	m_textCtrlCrane4MoorTime = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52113->Add( m_textCtrlCrane4MoorTime, 0, wxALL|wxEXPAND, 5 );

	m_statiCraneUnMoorTime3 = new wxStaticText( sbSizer3113->GetStaticBox(), wxID_ANY, _("Unmooring Time:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_statiCraneUnMoorTime3->Wrap( -1 );
	fgSizer52113->Add( m_statiCraneUnMoorTime3, 0, wxALL, 5 );

	m_textCtrlCrane4UnMoorTime = new wxTextCtrl( sbSizer3113->GetStaticBox(), wxID_ANY, _("01.01.1970 00:00:00"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer52113->Add( m_textCtrlCrane4UnMoorTime, 0, wxALL|wxEXPAND, 5 );


	sbSizer3113->Add( fgSizer52113, 1, wxEXPAND, 5 );


	m_collapsiblePane4->GetPane()->SetSizer( sbSizer3113 );
	m_collapsiblePane4->GetPane()->Layout();
	sbSizer3113->Fit( m_collapsiblePane4->GetPane() );
	fgSizer25->Add( m_collapsiblePane4, 1, wxEXPAND | wxALL, 5 );


	sbSizer31->Add( fgSizer25, 1, wxEXPAND, 5 );


	bSizer10->Add( sbSizer31, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer10 );
	this->Layout();
	m_timer.SetOwner( this, m_timer.GetId() );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OFTinfoBase::OnClose ) );
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OFTinfoBase::OnDLeftClick ) );
	this->Connect( m_timer.GetId(), wxEVT_TIMER, wxTimerEventHandler( OFTinfoBase::OnTimer ) );
}

OFTinfoBase::~OFTinfoBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( OFTinfoBase::OnClose ) );
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( OFTinfoBase::OnDLeftClick ) );
	this->Disconnect( m_timer.GetId(), wxEVT_TIMER, wxTimerEventHandler( OFTinfoBase::OnTimer ) );

}

oftinfoPreferences::oftinfoPreferences( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("AIS Targets") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_cbAisToFile = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit to file"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbAisToFile, 0, wxALL, 5 );

	m_cbAisToMQTT = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit to MQTT"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbAisToMQTT, 0, wxALL, 5 );

	m_cbAisToPSQL = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit to PSQL"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_cbAisToPSQL, 0, wxALL, 5 );

	m_staticText82 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("Transmit period:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	fgSizer2->Add( m_staticText82, 0, wxALL, 5 );

	m_textCtrlAISTransPeriod = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, _("20"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlAISTransPeriod, 0, wxALL, 5 );


	sbSizer1->Add( fgSizer2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer211;
	sbSizer211 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Target filter") ), wxHORIZONTAL );

	m_cbAISTargCargoOnly = new wxCheckBox( sbSizer211->GetStaticBox(), wxID_ANY, _("Cargo Vessel Only"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbAISTargCargoOnly->SetValue(true);
	sbSizer211->Add( m_cbAISTargCargoOnly, 0, wxALL, 5 );

	m_cbAISTargZeroInc = new wxCheckBox( sbSizer211->GetStaticBox(), wxID_ANY, _("Zero Type Include"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer211->Add( m_cbAISTargZeroInc, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer211, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Own Ship MMSI") ), wxHORIZONTAL );

	m_textCtrlOwnMMSI = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, _("123456789"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_textCtrlOwnMMSI, 0, wxALL, 5 );

	m_cbAISTransmitAIVDO = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, _("Transmit AIVDO"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_cbAISTransmitAIVDO, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("OFT MMSI") ), wxHORIZONTAL );

	m_textCtrlOFTMMSI1 = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, _("123456789"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	sbSizer22->Add( m_textCtrlOFTMMSI1, 0, wxALL, 5 );

	m_textCtrlOFTMMSI2 = new wxTextCtrl( sbSizer22->GetStaticBox(), wxID_ANY, _("123456789"), wxPoint( 1,-1 ), wxDefaultSize, 0 );
	sbSizer22->Add( m_textCtrlOFTMMSI2, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer22, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Load Area Monitoring Data") ), wxHORIZONTAL );

	m_cbMonToFile = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, _("Transmit to file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbMonToFile->SetValue(true);
	sbSizer4->Add( m_cbMonToFile, 0, wxALL, 5 );

	m_cbMonToMQTT = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, _("Transmit to MQTT"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_cbMonToMQTT, 0, wxALL, 5 );

	m_cbMonToPSQL = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, _("Transmit to PSQL"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_cbMonToPSQL, 0, wxALL, 5 );

	m_staticText821 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Transmit period:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText821->Wrap( -1 );
	sbSizer4->Add( m_staticText821, 0, wxALL, 5 );

	m_textCtrlMonTransPeriod = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, _("20"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_textCtrlMonTransPeriod, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer4, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer221;
	sbSizer221 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("File") ), wxHORIZONTAL );

	m_staticText8 = new wxStaticText( sbSizer221->GetStaticBox(), wxID_ANY, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	sbSizer221->Add( m_staticText8, 0, wxALL, 5 );

	m_textCtrlAisFileName = new wxTextCtrl( sbSizer221->GetStaticBox(), wxID_ANY, _("AISTargets"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	sbSizer221->Add( m_textCtrlAisFileName, 0, wxALL, 5 );

	m_staticText81 = new wxStaticText( sbSizer221->GetStaticBox(), wxID_ANY, _("Path:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	sbSizer221->Add( m_staticText81, 0, wxALL, 5 );

	m_textCtrlAISFilePath = new wxTextCtrl( sbSizer221->GetStaticBox(), wxID_ANY, _("C:\\scripts"), wxPoint( 1,-1 ), wxDefaultSize, 0 );
	sbSizer221->Add( m_textCtrlAISFilePath, 0, wxALL, 5 );


	sbSizer1->Add( sbSizer221, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2211;
	sbSizer2211 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("MQTT") ), wxHORIZONTAL );

	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 10, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText822 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("Broker IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText822->Wrap( -1 );
	fgSizer21->Add( m_staticText822, 0, wxALL, 5 );

	m_textCtrlMQTTBrokerIP = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTBrokerIP, 0, wxALL, 5 );

	m_staticText8221 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8221->Wrap( -1 );
	fgSizer21->Add( m_staticText8221, 0, wxALL, 5 );

	m_textCtrlMQTTBrokerPort = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("1883"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTBrokerPort, 0, wxALL, 5 );

	m_staticText82211 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("client_id:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82211->Wrap( -1 );
	fgSizer21->Add( m_staticText82211, 0, wxALL, 5 );

	m_textCtrlMQTTclientID = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("OFTinfoMain"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTclientID, 0, wxALL, 5 );

	m_staticText822111 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("user:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText822111->Wrap( -1 );
	fgSizer21->Add( m_staticText822111, 0, wxALL, 5 );

	m_textCtrlMQTTuser = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("user"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTuser, 0, wxALL, 5 );

	m_staticText8221111 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("passw:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8221111->Wrap( -1 );
	fgSizer21->Add( m_staticText8221111, 0, wxALL, 5 );

	m_textCtrlMQTTpassw = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("password"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTpassw, 0, wxALL, 5 );

	m_staticText82211111 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("Publish Topic:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82211111->Wrap( -1 );
	fgSizer21->Add( m_staticText82211111, 0, wxALL, 5 );

	m_textCtrlMQTTPublishTopic = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("Cargo/OCPN"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer21->Add( m_textCtrlMQTTPublishTopic, 0, wxALL|wxEXPAND, 5 );

	m_staticText822111111 = new wxStaticText( sbSizer2211->GetStaticBox(), wxID_ANY, _("SubscribeTopic:"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText822111111->Wrap( -1 );
	fgSizer21->Add( m_staticText822111111, 0, wxALL, 5 );

	m_textCtrlMQTTSubscribeTopic = new wxTextCtrl( sbSizer2211->GetStaticBox(), wxID_ANY, _("Cargo/OCPN"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	fgSizer21->Add( m_textCtrlMQTTSubscribeTopic, 0, wxALL|wxEXPAND, 5 );


	sbSizer2211->Add( fgSizer21, 1, wxEXPAND, 5 );


	sbSizer1->Add( sbSizer2211, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer22111;
	sbSizer22111 = new wxStaticBoxSizer( new wxStaticBox( sbSizer1->GetStaticBox(), wxID_ANY, _("PostgreSQL") ), wxHORIZONTAL );

	wxFlexGridSizer* fgSizer211;
	fgSizer211 = new wxFlexGridSizer( 0, 8, 0, 0 );
	fgSizer211->SetFlexibleDirection( wxBOTH );
	fgSizer211->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText8222 = new wxStaticText( sbSizer22111->GetStaticBox(), wxID_ANY, _("DB IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8222->Wrap( -1 );
	fgSizer211->Add( m_staticText8222, 0, wxALL, 5 );

	m_textCtrlSQLip = new wxTextCtrl( sbSizer22111->GetStaticBox(), wxID_ANY, _("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer211->Add( m_textCtrlSQLip, 0, wxALL, 5 );

	m_staticText82212 = new wxStaticText( sbSizer22111->GetStaticBox(), wxID_ANY, _("port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82212->Wrap( -1 );
	fgSizer211->Add( m_staticText82212, 0, wxALL, 5 );

	m_textCtrlSQLport = new wxTextCtrl( sbSizer22111->GetStaticBox(), wxID_ANY, _("5432"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer211->Add( m_textCtrlSQLport, 0, wxALL, 5 );

	m_staticText8221112 = new wxStaticText( sbSizer22111->GetStaticBox(), wxID_ANY, _("user:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8221112->Wrap( -1 );
	fgSizer211->Add( m_staticText8221112, 0, wxALL, 5 );

	m_textCtrlSQLuser = new wxTextCtrl( sbSizer22111->GetStaticBox(), wxID_ANY, _("user"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer211->Add( m_textCtrlSQLuser, 0, wxALL, 5 );

	m_staticText82211112 = new wxStaticText( sbSizer22111->GetStaticBox(), wxID_ANY, _("passw:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82211112->Wrap( -1 );
	fgSizer211->Add( m_staticText82211112, 0, wxALL, 5 );

	m_textCtrlSQLpassw = new wxTextCtrl( sbSizer22111->GetStaticBox(), wxID_ANY, _("password"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer211->Add( m_textCtrlSQLpassw, 0, wxALL, 5 );

	m_staticText822111112 = new wxStaticText( sbSizer22111->GetStaticBox(), wxID_ANY, _("DB name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText822111112->Wrap( -1 );
	fgSizer211->Add( m_staticText822111112, 0, wxALL, 5 );

	m_textCtrlSQLDBName = new wxTextCtrl( sbSizer22111->GetStaticBox(), wxID_ANY, _("cargo"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer211->Add( m_textCtrlSQLDBName, 0, wxALL, 5 );


	sbSizer22111->Add( fgSizer211, 1, wxEXPAND, 5 );


	sbSizer1->Add( sbSizer22111, 1, wxEXPAND, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( sbSizer1->GetStaticBox(), wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( sbSizer1->GetStaticBox(), wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	sbSizer1->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( sbSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

oftinfoPreferences::~oftinfoPreferences()
{
}
