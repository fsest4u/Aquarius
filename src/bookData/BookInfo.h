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
#ifndef BOOKINFO_H
#define BOOKINFO_H

#include <QObject>

class BookInfo
{
public:
	BookInfo();
	virtual ~BookInfo();

	QString GetFilename() { return m_Filename; }
	void SetFilename(QString data) { m_Filename = data; }
	QString GetTitle() { return m_Title; }
	void SetTitle(QString data) { m_Title = data; }
	QString GetAuthor() { return m_Author; }
	void SetAuthor(QString data) { m_Author = data; }
	QString GetGenre() { return m_Genre; }
	void SetGenre(QString data) { m_Genre = data; }
	QString GetDownloadTime() { return m_DownloadTime; }
	void SetDownloadTime(QString data) { m_DownloadTime = data; }
	QString GetReadTime() { return m_ReadTime; }
	void SetReadTime(QString data) { m_ReadTime = data; }
	QString GetFilesize() { return m_Filesize; }
	void SetFilesize(QString data) { m_Filesize = data; }
	QString GetCoverPath() { return m_CoverPath; }
	void SetCoverPath(QString data) { m_CoverPath = data; }
	QString GetLibrary() { return m_Library; }
	void SetLibrary(QString data) { m_Library = data; }

private:

	QString m_Filename;
	QString m_Title;
	QString m_Author;
	QString m_Genre;
	QString m_DownloadTime;
	QString m_ReadTime;
	QString m_Filesize;
	QString m_CoverPath;
	QString m_Library;

};

#endif	// BOOKINFO_H