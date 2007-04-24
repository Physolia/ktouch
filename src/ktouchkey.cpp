/***************************************************************************
 *   ktouchkey.cpp                                                         *
 *   -------------                                                         *
 *   Copyright (C) 2000 by Håvard Frøiland, 2004 by Andreas Nicolai        *
 *   ghorwin@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "ktouchkey.h"
#include "ktouchkey.moc"

#include <QtXml>
#include <QtCore>

#include <kdebug.h>

#include "ktouchcolorscheme.h"
#include "prefs.h"

const double PEN_WIDTH = 1.0;

KTouchKey::KTouchKey(keytype_t type, int x, int y, int w, int h, QChar ch)
	: m_type(type), m_x(x), m_y(y), m_w(w), m_h(h)
{
	m_keyChar[0] = ch;
	m_keyChar[1] = QChar();
	m_keyChar[2] = QChar();
	m_keyChar[3] = QChar();
	setPos(m_x, m_y);
}
// ----------------------------------------------------------------------------

KTouchKey::KTouchKey(int x, int y, int w, int h, const QString &text) :
	m_x(x), m_y(y), m_w(w), m_h(h)
{
	m_type = OTHER;
	m_keyChar[0] = QChar();
	m_keyText = text;
	setPos(m_x, m_y);
}
// ----------------------------------------------------------------------------

// Reads the key data from the DomElement
bool KTouchKey::read(QDomNode node) {
/*
	if (node.isNull()) 
		return false;	// TODO : Error message
	QString primaryCharText = node.firstChild().nodeValue();
	if (primaryCharText.length() >= 1)
		m_primaryChar = primaryCharText[0];
	else
		return false; // TODO : Error message
	QDomNamedNodeMap nmap = node.attributes();
	// Get height, widht, x and y
	node = nmap.namedItem("Height");
	if (node.isNull())
		return false; // TODO : Error message
	m_h = node.nodeValue().toInt();
	node = nmap.namedItem("Width");
	if (node.isNull())
		return false; // TODO : Error message
	m_w = node.nodeValue().toInt();
	node = nmap.namedItem("X");
	if (node.isNull())
		return false; // TODO : Error message
	m_x = node.nodeValue().toInt();
	node = nmap.namedItem("Y");
	if (node.isNull())
		return false; // TODO : Error message
	m_y = node.nodeValue().toInt();
	// read type of key
	node = nmap.namedItem("Type");
	if (node.isNull())
		return false; // TODO : Error message
	QString typetext = node.nodeValue();
	if (typetext=="NORMAL")  		m_type = NORMAL;
	else if (typetext=="FINGER")  	m_type = FINGER;
	else if (typetext=="ENTER")  	m_type = ENTER;
	else if (typetext=="BACKSPACE")	m_type = BACKSPACE;
	else if (typetext=="SHIFT")  	m_type = SHIFT;
	else if (typetext=="SPACE")  	m_type = SPACE;
	else if (typetext=="OTHER") {
	  	m_type = OTHER;
		node = nmap.namedItem("OtherKeyText");
		if (!node.isNull())
			m_otherKeyText = node.nodeValue();
	}
	else
		return false; // TODO : Error message
	// read optional secondary character
	node = nmap.namedItem("SecondaryChar");
	QString charvalue;
	if (!node.isNull())
		charvalue = node.nodeValue();
	if (charvalue.length() >= 1)
		m_secondaryChar = charvalue[0];
	else
		m_secondaryChar = QChar(0);
	kDebug() << "H:" << m_h << " W:" << m_w << " X:" << m_x << " Y:" << m_y 
	          << " Type:" << m_type << " SecondaryChar:" << m_secondaryChar 
			  << "' PrimaryChar:" << m_primaryChar << "'" << endl;
*/
	return true;
}
// ----------------------------------------------------------------------------

// Writes the key data into the DomElement
void KTouchKey::write(QDomDocument& doc, QDomElement& root) const {
	QDomElement element = doc.createElement("Key");
	switch (m_type) {
		case NORMAL     : element.setAttribute("Type", "NORMAL"); break;
		case FINGER     : element.setAttribute("Type", "FINGER"); break;
		case ENTER 		: element.setAttribute("Type", "ENTER"); break;
		case BACKSPACE 	: element.setAttribute("Type", "BACKSPACE"); break;
		case SHIFT 		: element.setAttribute("Type", "SHIFT"); break;
		case SPACE 		: element.setAttribute("Type", "SPACE"); break;
		case OTHER 		: 
			element.setAttribute("Type", "OTHER"); 
			element.setAttribute("KeyText", m_keyText);
			break;
	}
/*	QDomText charnode = doc.createTextNode(QString(m_primaryChar));
	element.appendChild(charnode);
//	element.setAttribute("PrimaryChar", QString(m_primaryChar));
	if (m_secondaryChar!=QChar(0))
		element.setAttribute("SecondaryChar", QString(m_secondaryChar));
	element.setAttribute("X", m_x);
	element.setAttribute("Y", m_y);
	element.setAttribute("Width", m_w);
	element.setAttribute("Height", m_h);
	root.appendChild(element);
*/
}
// ----------------------------------------------------------------------------

void KTouchKey::setState(state_t state) {
	
}
// ----------------------------------------------------------------------------

QRectF KTouchKey::boundingRect() const {
	return QRectF(0 - PEN_WIDTH/2.0, 0 - PEN_WIDTH/2.0, 
		m_w + PEN_WIDTH/2.0, m_h + PEN_WIDTH/2.0);
}
// ----------------------------------------------------------------------------

void KTouchKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

	// get the colorscheme from the configuration
    const KTouchColorScheme& colorScheme = KTouchColorScheme::m_colorSchemes[Prefs::currentColorScheme()];

	// TODO : painting
/*    if (m_isNextKey) {
        painter->setBrush( colorScheme.m_backgroundH );
        painter->setPen( colorScheme.m_frame );
        painter->drawRoundRect(0, 0, m_w, m_h);
        painter->setBrush(colorScheme.m_cBackgroundH );
        painter->drawEllipse(0, 0, m_w, m_h);
    }
    else {
        painter->setBrush( colorScheme.m_background[m_colorIndex] );
        painter->setPen( colorScheme.m_frame );
        painter->drawRoundRect(0, 0, m_w, m_h);
    }

    painter->setPen( colorScheme.m_text );
    painter->setFont( m_font );
    painter->drawText(0, 0+1, m_w, m_h, Qt::AlignCenter, m_keyText);
*/
}
