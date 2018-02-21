/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub PC Viewer.
**
*************************************************************************/

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QDatetime>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QVariant>

#include "BookListCtrl.h"
#include "BookInfo.h"
#include "AquariusContants.h"

const QString AQUARIUS_BOOKLIST = "aquarius_booklist";

const QString BOOKLIST_FILENAME = "filename";
const QString BOOKLIST_TITLE = "title";
const QString BOOKLIST_AUTHOR = "author";
const QString BOOKLIST_GENRE = "genre";
const QString BOOKLIST_DOWNTIME = "downtime";
const QString BOOKLIST_READTIME = "readtime";
const QString BOOKLIST_FILESIZE = "filesize";
const QString BOOKLIST_COVERPATH = "coverpath";
const QString BOOKLIST_LIBRARY = "library";
const QString BOOKLIST_INFO = "booklistinfo";

BookListCtrl::BookListCtrl(QObject *parent)
	: QObject(parent)
	, m_SortType(SORT_NONE)
	, m_Genre("")
	, m_Library("")
	, m_Author("")
	, m_Title("")
	, m_BookListInfo(new BookListInfo)
{
	ConnectSignalsToSlots();
}


BookListCtrl::~BookListCtrl()
{
	if (m_BookListInfo) {
		delete m_BookListInfo;
		m_BookListInfo = 0;
	}
}

void BookListCtrl::ConnectSignalsToSlots()
{
	connect(this, SIGNAL(ChangedBookList()), this, SLOT(SaveBookList()));

}

QStringList BookListCtrl::GetSortedList(int sortType)
{
	m_SortType = (SortType)sortType;

	QStringList sortList;
	switch (sortType)
	{
	case SORT_AUTHOR:
	{
		sortList = GetSortedListByAuthor();
		break;
	}
	case SORT_TITLE:
	{
		sortList = GetSortedListByTitle();
		break;
	}
	case SORT_DOWNTIME:
	{
		sortList = GetSortedListByDownTime();
		break;
	}
	case SORT_READTIME:
	{
		sortList = GetSortedListByReadTime();
		break;
	}
	default:
	{
		m_SortType = SORT_AUTHOR;
		sortList = GetSortedListByAuthor();
		break;
	}
	}

	return sortList;
}

QStringList BookListCtrl::GetSortedListByAuthor()
{
	return m_BookListInfo->GetBookListAuthor();
}

QStringList BookListCtrl::GetSortedListByTitle()
{
	return m_BookListInfo->GetBookListTitle();
}

QStringList BookListCtrl::GetSortedListByDownTime()
{
	return m_BookListInfo->GetBookListDownTime();
}

QStringList BookListCtrl::GetSortedListByReadTime()
{
	return m_BookListInfo->GetBookListReadTime();
}


bool BookListCtrl::AddBookItem(BookInfo* bInfo)
{
	QString key = bInfo->GetFilename();
	if (!m_BookListInfo->IsContainBookList(key)) {
		m_BookListInfo->AddBookListInfo(bInfo);
		emit ChangedBookList();
		return true;
	}

	return false;
}

bool BookListCtrl::DeleteBookItem(QString key)
{
	if (m_BookListInfo->IsContainBookList(key)) {
		m_BookListInfo->DeleteBookListInfo(key);
		emit ChangedBookList();
		return true;
	}

	return false;
}

bool BookListCtrl::SaveBookList()
{
	QString filename = AQUARIUS_LOCATION_TEMP + "/" + AQUARIUS_BOOKLIST;
	QFile bListFile(filename);
	bListFile.remove();

	QJsonArray bInfoArray;
	QList<BookInfo*> bInfoList = m_BookListInfo->GetBookList();
	foreach (BookInfo* bInfo, bInfoList) {
		QJsonObject bInfoObject;
		bInfoObject[BOOKLIST_FILENAME] = bInfo->GetFilename();
		bInfoObject[BOOKLIST_TITLE] = bInfo->GetTitle();
		bInfoObject[BOOKLIST_AUTHOR] = bInfo->GetAuthor();
		bInfoObject[BOOKLIST_GENRE] = bInfo->GetGenre();
		bInfoObject[BOOKLIST_DOWNTIME] = bInfo->GetDownloadTime().toMSecsSinceEpoch();
		bInfoObject[BOOKLIST_READTIME] = bInfo->GetReadTime().toMSecsSinceEpoch();
		bInfoObject[BOOKLIST_FILESIZE] = bInfo->GetFilesize();
		bInfoObject[BOOKLIST_COVERPATH] = bInfo->GetCoverPath();
		bInfoObject[BOOKLIST_LIBRARY] = bInfo->GetLibrary();

		bInfoArray.append(bInfoObject);
	}

	QJsonObject bListInfo;
	bListInfo.insert(BOOKLIST_INFO, bInfoArray);
	if (bListFile.open(QFile::ReadWrite)) {
		bListFile.write(QJsonDocument(bListInfo).toJson(QJsonDocument::Compact));
		return true;
	}

	return false;
}

bool BookListCtrl::OpenBookList()
{
	QString filename = AQUARIUS_LOCATION_TEMP + "/" + AQUARIUS_BOOKLIST;
	QFile bListFile(filename);
	if (bListFile.exists()) {
		QJsonParseError jError;
		bListFile.open(QFile::ReadWrite);

		QJsonDocument jDoc = QJsonDocument::fromJson(bListFile.readAll(), &jError);
		if (jError.error != QJsonParseError::NoError) return false;

		QJsonArray jInfoArray = jDoc.object()[BOOKLIST_INFO].toArray();
		foreach(QJsonValue jInfo, jInfoArray) {

			const QJsonObject jInfoObject = jInfo.toObject();
			BookInfo* bInfo = new BookInfo();
			bInfo->SetFilename(jInfoObject[BOOKLIST_FILENAME].toString());
			bInfo->SetTitle(jInfoObject[BOOKLIST_TITLE].toString());
			bInfo->SetAuthor(jInfoObject[BOOKLIST_AUTHOR].toString());
			bInfo->SetGenre(jInfoObject[BOOKLIST_GENRE].toString());
			bInfo->SetDownloadTime(QDateTime::fromMSecsSinceEpoch(jInfoObject[BOOKLIST_DOWNTIME].toVariant().toLongLong()));
			bInfo->SetReadTime(QDateTime::fromMSecsSinceEpoch(jInfoObject[BOOKLIST_READTIME].toVariant().toLongLong()));
			bInfo->SetFilesize(jInfoObject[BOOKLIST_FILESIZE].toVariant().toLongLong());
			bInfo->SetCoverPath(jInfoObject[BOOKLIST_COVERPATH].toString());
			bInfo->SetLibrary(jInfoObject[BOOKLIST_LIBRARY].toString());

			if (QDir(AQUARIUS_LOCATION_TEMP+"/"+bInfo->GetFilename()).exists()) {
				AddBookItem(bInfo);
			}
		}
	}
	else {
		QDir dir(AQUARIUS_LOCATION_TEMP);
		if (dir.exists()) {
			dir.removeRecursively();
		}
	}

	// draw book list

	return true;
}