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

#include <QtCore/QObject>
#include <QtCore/QDateTime>

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
	QDateTime GetDownloadTime() { return m_DownloadTime; }
	void SetDownloadTime(QDateTime data) { m_DownloadTime = data; }
	QDateTime GetReadTime() { return m_ReadTime; }
	void SetReadTime(QDateTime data) { m_ReadTime = data; }
	double GetFilesize() { return m_Filesize; }
	void SetFilesize(double data) { m_Filesize = data; }
	QString GetCoverPath() { return m_CoverPath; }
	void SetCoverPath(QString data) { m_CoverPath = data; }
	QString GetLibrary() { return m_Library; }
	void SetLibrary(QString data) { m_Library = data; }

private:

	QString m_Filename;
	QString m_Title;
	QString m_Author;
	QString m_Genre;
	QDateTime m_DownloadTime;
	QDateTime m_ReadTime;
	double m_Filesize;
	QString m_CoverPath;
	QString m_Library;

};

#endif	// BOOKINFO_H