/***************************************************************************
 *   ktouchkey.h                                                           *
 *   -----------                                                           *
 *   Copyright (C) 2000-2007 by Håvard Frøiland and Andreas Nicolai        *
 *   ghorwin@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef KTOUCHKEY_H
#define KTOUCHKEY_H

#include <QPainter>
#include <QObject>
#include <QGraphicsItem>

class QDomElement;
class QDomNode;
class QDomDocument;

/// This class represents a key on the keyboard.
///
/// This class contains all the geometrical information for a key to be drawn
/// on the keyboard. A KTouchKey is a QGraphicsItem and draws itself on
/// the graphics scene containing the keyboard.
class KTouchKey : public QObject, public QGraphicsItem {
  Q_OBJECT
public:

	/// Position of a character on the key.
	enum position_t {
      TOP_LEFT,
      TOP_RIGHT,
      BOTTOM_LEFT,
      BOTTOM_RIGHT
    };

	/// Type of a key
    enum keytype_t {
	  NORMAL,
	  FINGER,
	  ENTER,
	  BACKSPACE,
	  SHIFT,
	  SPACE,
	  OTHER
	};
 
	/// The (highlighting, marking) state of a key
	enum state_t {
		NORMAL_STATE,			// normal key appearance on the keyboard
		HIGH_LIGHTED_STATE,		// when indicating the next target key
		FINGER_KEY_STATE,		// when indicating the origin key of the finger to be used
		MODIFIER_STATE			// when indicating a certain modifier key
	};

	/// Default constructor.
	KTouchKey() : m_type(NORMAL), m_x(0), m_y(0), m_w(0), m_h(0) {}
	/// Convenience constructor for a key with a single character.
	KTouchKey(keytype_t type, int x, int y, int w, int h, QChar ch);
	/// Convenience constructor for a key with a text on it (type will be OTHER).
	KTouchKey(int x, int y, int w, int h, const QString &text);
	/// Default destructor.
	virtual ~KTouchKey() {}

	/// Reads the key data from the DomElement
	bool read(QDomNode node);
	/// Creates a new DomElement, writes the key data into it and appends it to the root object.
	void write(QDomDocument& doc, QDomElement& root) const;

	/// Changes the state of the key.
	///
	/// This function will be called from the keyboard widget whenever the key appearance should change.
	void setState(state_t state);

	// *** re-implementations of QGraphicsItem functions ***

	/// Returns the bounding rectangle of this key.
	virtual QRectF boundingRect() const;
	/// Draws the key onto the graphics scene using the provided painter.
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


	// *** member variables ***

	unsigned int	m_number;		///< The number of the key.
	keytype_t		m_type;			///< The type of the key.
	QChar			m_keyChar[4];	///< The characters on each key, one for each possible position.
	QString			m_keyText;		///< The alternative text for decorative keys.
	int				m_x;			///< The x-coordinate of the top-left corner of the key.
	int				m_y;			///< The y-coordinate of the top-left corner of the key.
	int				m_w;			///< The width.
	int				m_h;			///< The height.
};
// ---------------------------------------------------------------------------------------

#endif  // KTOUCHKEYS_H
