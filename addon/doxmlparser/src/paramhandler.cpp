/******************************************************************************
 *
 * $Id$
 *
 *
 * Copyright (C) 1997-2002 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 */

#include "paramhandler.h"
#include "memberhandler.h"
#include "debug.h"

ParamHandler::ParamHandler(IBaseHandler *parent) : m_parent(parent)
{
  addEndHandler("param",this,&ParamHandler::endParam);

  addStartHandler("type",this,&ParamHandler::startType);

  addStartHandler("declname");
  addEndHandler("declname",this,&ParamHandler::endDeclName);

  addStartHandler("defname");
  addEndHandler("defname",this,&ParamHandler::endDefName);

  addStartHandler("array");
  addEndHandler("array",this,&ParamHandler::endArray);

  addStartHandler("attrib");
  addEndHandler("attrib",this,&ParamHandler::endAttrib);

  addStartHandler("defval",this,&ParamHandler::startDefVal);

  m_linkedTextHandler = 0;
}

ParamHandler::~ParamHandler()
{
  delete m_linkedTextHandler;
}

void ParamHandler::startParam(const QXmlAttributes& /*attrib*/)
{
  m_parent->setDelegate(this);
  debug(2,"param\n");
}

void ParamHandler::endParam()
{
  m_parent->setDelegate(0);
}

void ParamHandler::startType(const QXmlAttributes& /*attrib*/)
{
  delete m_linkedTextHandler;
  m_linkedTextHandler = new LinkedTextHandler(this,m_type);
  m_linkedTextHandler->start("type");
  debug(2,"param type\n");
}

void ParamHandler::endDeclName()
{
  m_declName = m_curString.stripWhiteSpace();
  debug(2,"member declName=`%s'\n",m_declName.data());
}

void ParamHandler::endDefName()
{
  m_defName = m_curString.stripWhiteSpace();
  debug(2,"member defName=`%s'\n",m_defName.data());
}

void ParamHandler::endAttrib()
{
  m_attrib = m_curString.stripWhiteSpace();
  debug(2,"member attrib=`%s'\n",m_attrib.data());
}

void ParamHandler::endArray()
{
  m_array = m_curString.stripWhiteSpace();
  debug(2,"member array=`%s'\n",m_array.data());
}

void ParamHandler::startDefVal(const QXmlAttributes& /*attrib*/)
{
  delete m_linkedTextHandler;
  m_linkedTextHandler = new LinkedTextHandler(this,m_defVal);
  m_linkedTextHandler->start("defval");
  debug(2,"member defVal\n");
}


