/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub PC Viewer.
**
*************************************************************************/

#include "BookListInfo.h"

#include "BookInfo.h"


BookListInfo::BookListInfo()
	: m_BookListInfo(new QHash<QString, BookInfo*>)
	, m_BookListAuthor(new QMap<QString, QString>)
	, m_BookListTitle(new QMap<QString, QString>)
	, m_BookListDownTime(new QMap<QString, QString>)
	, m_BookListReadTime(new QMap<QString, QString>)
{
}


BookListInfo::~BookListInfo()
{
	if (m_BookListInfo) {
		m_BookListInfo->clear();
		delete m_BookListAuthor;
		m_BookListAuthor = 0;
	}

	if (m_BookListAuthor) {
		m_BookListAuthor->clear();
		delete m_BookListAuthor;
		m_BookListAuthor = 0;
	}

	if (m_BookListTitle) {
		m_BookListTitle->clear();
		delete m_BookListTitle;
		m_BookListTitle = 0;
	}

	if (m_BookListDownTime) {
		m_BookListDownTime->clear();
		delete m_BookListDownTime;
		m_BookListDownTime = 0;
	}

	if (m_BookListReadTime) {
		m_BookListReadTime->clear();
		delete m_BookListReadTime;
		m_BookListReadTime = 0;
	}
}
