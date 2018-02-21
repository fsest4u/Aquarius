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
	: m_BookList(new QHash<QString, BookInfo*>)
	, m_BookListAuthor(new QMap<QString, QString>)
	, m_BookListTitle(new QMap<QString, QString>)
	, m_BookListDownTime(new QMap<QString, QString>)
	, m_BookListReadTime(new QMap<QString, QString>)
{
}


BookListInfo::~BookListInfo()
{
	if (m_BookList) {
		m_BookList->clear();
		delete m_BookList;
		m_BookList = 0;
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

bool BookListInfo::IsContainBookList(QString key)
{
	return m_BookList->contains(key);
}

void BookListInfo::AddBookListInfo(BookInfo* bInfo)
{
	QString key = bInfo->GetFilename();
	QString downTime = QString::number(bInfo->GetDownloadTime().toMSecsSinceEpoch());
	QString readTime = QString::number(bInfo->GetReadTime().toMSecsSinceEpoch());

	m_BookList->insert(key.toLower(), bInfo);
	m_BookListAuthor->insert(QString(bInfo->GetAuthor() + key).toLower(), key);
	m_BookListTitle->insert(QString(bInfo->GetTitle() + key).toLower(), key);
	m_BookListDownTime->insert(QString(downTime + key).toLower(), key);
	m_BookListReadTime->insert(QString(readTime + key).toLower(), key);

	//refresh book list
}

void BookListInfo::DeleteBookListInfo(QString key)
{
	m_BookList->remove(key);
	m_BookListAuthor->remove(m_BookListAuthor->key(key));
	m_BookListTitle->remove(m_BookListTitle->key(key));
	m_BookListDownTime->remove(m_BookListDownTime->key(key));
	m_BookListReadTime->remove(m_BookListReadTime->key(key));

	//refresh book list
}
