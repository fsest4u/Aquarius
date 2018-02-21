/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub PC Viewer.
**
*************************************************************************/

#pragma once
#ifndef BOOKLISTINFO_H
#define BOOKLISTINFO_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QMap>


class BookInfo;

class BookListInfo
{
public:
	explicit BookListInfo();
	virtual ~BookListInfo();

	QList<BookInfo*> GetBookList() { return m_BookList->values(); }
	QStringList GetBookListAuthor() { return m_BookListAuthor->values(); }
	QStringList GetBookListTitle() { return m_BookListTitle->values(); }
	QStringList GetBookListDownTime() { return m_BookListDownTime->values(); }
	QStringList GetBookListReadTime() { return m_BookListReadTime->values(); }

	bool IsContainBookList(QString key);

	void AddBookListInfo(BookInfo* bInfo);
	void DeleteBookListInfo(QString key);
	
private:

	QHash<QString, BookInfo*> *m_BookList;
	QMap<QString, QString> *m_BookListAuthor;
	QMap<QString, QString> *m_BookListTitle;
	QMap<QString, QString> *m_BookListDownTime;
	QMap<QString, QString> *m_BookListReadTime;

};

#endif	//BOOKLISTINFO_H