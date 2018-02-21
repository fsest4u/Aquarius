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
	explicit BookListCtrl(QObject *parent = 0);
	virtual ~BookListCtrl();

	QString GetSortType() { return m_SortType; }
	QString GetGenreType() { return m_GenreType; }
	QString GetLibrary() { return m_Library; }
	QString GetAuthor() { return m_Author; }
	QString GetTitle() { return m_Title; }

	QStringList GetSortedListByAuthor();
	QStringList GetSortedListByTitle();
	QStringList GetSortedListByDownTime();
	QStringList GetSortedListByReadTime();

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

	QString m_SortType;
	QString m_GenreType;
	QString m_Library;
	QString m_Author;
	QString m_Title;

	BookListInfo*	m_BookListInfo;


};

#endif // BOOKLISTCTRL_H