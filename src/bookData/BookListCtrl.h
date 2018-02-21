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

class BookListCtrl : QObject
{
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

	bool AddBookItem();
	bool DeleteBookItem();
	BookListInfo* GetBookListInfo();
	BookInfo*	GetBookInfo();


private:

	QString m_SortType;
	QString m_GenreType;
	QString m_Library;
	QString m_Author;
	QString m_Title;

	BookListInfo*	m_BookListInfo;


};

#endif // BOOKLISTCTRL_H