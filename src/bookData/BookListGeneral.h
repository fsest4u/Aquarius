/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub Manager.
**
*************************************************************************/

#pragma once
#ifndef BOOKLISTGENERAL_H
#define BOOKLISTGENERAL_H

#include <QtCore/QObject>

class BookListGeneral
{
public:
	BookListGeneral();
	virtual ~BookListGeneral();

	QString GetFilename() { return m_Filename; }
	QString GetTitle() { return m_Title; }
	QString GetCoverPath() { return m_CoverPath; }

private:

	QString m_Filename;
	QString m_Title;
	QString m_CoverPath;
};

#endif	// BOOKLISTGENERAL_H