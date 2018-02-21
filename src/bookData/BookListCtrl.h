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
#ifndef BOOKLISTCTRL_H
#define BOOKLISTCTRL_H

#include <QtCore/QObject>

#include "BookListInfo.h"

class BookInfo;

class BookListCtrl : QObject
{
	Q_OBJECT

public:

	enum SortType {
		SORT_NONE = 0,
		SORT_AUTHOR,
		SORT_TITLE,
		SORT_DOWNTIME,
		SORT_READTIME,
		SORT_MAX
	};

	explicit BookListCtrl(QObject *parent = 0);
	virtual ~BookListCtrl();

	int GetSortType() { return (int)m_SortType; }
	QString GetGenre() { return m_Genre; }
	QString GetLibrary() { return m_Library; }
	QString GetAuthor() { return m_Author; }
	QString GetTitle() { return m_Title; }

	QStringList GetSortedList(int sortType);

	QStringList GetFilteredListByGenre();
	QStringList GetFilteredListByLibrary();
	QStringList GetFilteredListByAuthor();
	QStringList GetFilteredListByTitle();

	bool AddBookItem(BookInfo* bInfo);
	bool DeleteBookItem(QString key);

	bool OpenBookList();

	BookListInfo* GetBookListInfo() { return m_BookListInfo; }

signals:

	void ChangedBookList();

private slots:

	bool SaveBookList();


private:

	void ConnectSignalsToSlots();

	QStringList GetSortedListByAuthor();
	QStringList GetSortedListByTitle();
	QStringList GetSortedListByDownTime();
	QStringList GetSortedListByReadTime();

	SortType m_SortType;
	QString m_Genre;
	QString m_Library;
	QString m_Author;
	QString m_Title;

	BookListInfo*	m_BookListInfo;


};

#endif // BOOKLISTCTRL_H