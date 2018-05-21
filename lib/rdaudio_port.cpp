// rdaudio_port.cpp
//
// Abstract a Rivendell Audio Port.
//
//   (C) Copyright 2002-2003,2016-2018 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
#include <rddb.h>
#include <rdaudio_port.h>
#include <rdescape_string.h>

//
// Global Classes
//
RDAudioPort::RDAudioPort(QString station,int card)
{
  port_station=station;
  port_card=card;
}


QString RDAudioPort::station() const
{
  return port_station;
}


int RDAudioPort::card() const
{
  return port_card;
}


RDCae::ClockSource RDAudioPort::clockSource()
{
  RDCae::ClockSource ret=RDCae::InternalClock;
  QString sql=QString("select CLOCK_SOURCE from AUDIO_CARDS where ")+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d",port_card);
  RDSqlQuery *q=new RDSqlQuery(sql);
  if(q->first()) {
    ret=(RDCae::ClockSource)q->value(0).toInt();
  }

  return ret;
}


void RDAudioPort::setClockSource(RDCae::ClockSource src)
{
  QString sql=QString("update AUDIO_CARDS set ")+
    QString().sprintf("CLOCK_SOURCE=%d where ",src)+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d",port_card);
  RDSqlQuery *q=new RDSqlQuery(sql);
  delete q;
}


RDAudioPort::PortType RDAudioPort::inputPortType(int port)
{
  RDAudioPort::PortType ret=RDAudioPort::Analog;
  QString sql=QString("select TYPE from AUDIO_INPUTS where ")+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  if(q->first()) {
    ret=(RDAudioPort::PortType)q->value(0).toInt();
  }

  return ret;
}


void RDAudioPort::setInputPortType(int port,RDAudioPort::PortType type)
{
  if(port<0) {
    return;
  }
  QString sql=QString("update AUDIO_INPUTS set ")+
    QString().sprintf("TYPE=%d where ",type)+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  delete q;
}


RDCae::ChannelMode RDAudioPort::inputPortMode(int port)
{
  RDCae::ChannelMode ret=RDCae::Normal;
  QString sql=QString("select MODE from AUDIO_INPUTS where ")+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  if(q->first()) {
    ret=(RDCae::ChannelMode)q->value(0).toInt();
  }

  return ret;
}


void RDAudioPort::setInputPortMode(int port,RDCae::ChannelMode mode)
{
  if(port<0) {
    return;
  }
  QString sql=QString("update AUDIO_INPUTS set ")+
    QString().sprintf("MODE=%d where ",mode)+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  delete q;
}


int RDAudioPort::inputPortLevel(int port)
{
  if(port<0) {
    return 400;
  }
  int ret=400;
  QString sql=QString("select LEVEL from AUDIO_INPUTS where ")+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  if(q->first()) {
    ret=q->value(0).toInt();
  }

  return ret;
}


void RDAudioPort::setInputPortLevel(int port,int level)
{
  if(port<0) {
    return;
  }
  QString sql=QString("update AUDIO_INPUTS set ")+
    QString().sprintf("LEVEL=%d where ",level)+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  delete q;
}


int RDAudioPort::outputPortLevel(int port)
{
  if(port<0) {
    return 400;
  }
  int ret=400;
  QString sql=QString("select LEVEL from AUDIO_OUTPUTS where ")+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  if(q->first()) {
    ret=q->value(0).toInt();
  }

  return ret;
}


void RDAudioPort::setOutputPortLevel(int port,int level)
{
  if(port<0) {
    return;
  }
  QString sql=QString("update AUDIO_OUTPUTS set ")+
    QString().sprintf("LEVEL=%d where ",level)+
    "STATION_NAME=\""+RDEscapeString(port_station)+"\" && "+
    QString().sprintf("CARD_NUMBER=%d && ",port_card)+
    QString().sprintf("PORT_NUMBER=%d",port);
  RDSqlQuery *q=new RDSqlQuery(sql);
  delete q;
}
