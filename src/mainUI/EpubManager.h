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
#ifndef EPUB_MANAGER_H
#define EPUB_MANAGER_H

#include <QtWidgets/QWidget>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QStringList>

class EpubParser;
class BookListCtrl;
class BookInfo;


class EpubManager : public QWidget
{

public:
    EpubManager(QWidget* parent = 0);
    virtual ~EpubManager();

	bool AddEpubList();
	bool DeleteEpub();

	BookListCtrl*	GetBookListCtrl() { return m_BookListCtrl; }


private:

	void			ReadSetting();
	void			WriteSetting();

	BookInfo*		CovertBookInfo(QFileInfo& fileInfo);

	EpubParser*		m_EpubParser;
	BookListCtrl*	m_BookListCtrl;

	QString			m_LastFolderOpen;
	QStringList		m_LastFolderOpenList;



};

#endif // EPUB_MANAGER_H
