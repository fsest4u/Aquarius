/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub PC Viewer.
**
*************************************************************************/

#include "EpubManager.h"

#include <QtDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>


#include "EpubParser.h"
#include "bookData/BookListCtrl.h"
#include "bookData/BookInfo.h"
#include "misc/SettingData.h"



static const QString SETTINGS_GROUP = "epubmanager";

static const QString AQUARIUS_LOCATION_DOCUMENTS = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/aquarius";
static const QString AQUARIUS_LOCATION_TEMP = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/aquarius";



EpubManager::EpubManager(QWidget* parent)
	: QWidget(parent)
	, m_EpubParser(new EpubParser())
	, m_BookListCtrl(new BookListCtrl(parent))
	, m_LastFolderOpen("")
{
    m_LastFolderOpenList.clear();

	ReadSetting();
}

EpubManager::~EpubManager()
{
	WriteSetting();

    m_LastFolderOpenList.clear();

	if (m_EpubParser) {
		delete m_EpubParser;
		m_EpubParser = 0;
	}

	if (m_BookListCtrl) {
		delete m_BookListCtrl;
		m_BookListCtrl = 0;
	}
}

void EpubManager::ReadSetting()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	QByteArray geometry = settings.value("geometry").toByteArray();

	if (!geometry.isNull()) {
		restoreGeometry(geometry);
	}

	m_LastFolderOpen = settings.value("lastfolderopen").toString();
	if (m_LastFolderOpen.isEmpty()) {
		m_LastFolderOpen = AQUARIUS_LOCATION_DOCUMENTS;
	}

	settings.endGroup();

}

void EpubManager::WriteSetting()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	settings.setValue("geometry", saveGeometry());

	settings.setValue("lastfolderopen", m_LastFolderOpen);

	settings.endGroup();
}

bool EpubManager::AddEpubList()
{
	qDebug() << "EpubManager - AddEpubList()";
	bool ret = false;
	QString filter = "Epubs (*.epub)";
	m_LastFolderOpenList = QFileDialog::getOpenFileNames(this, tr("Add the Epub Files"), m_LastFolderOpen, filter);
	if (!m_LastFolderOpenList.empty()) {
		m_LastFolderOpen = QFileInfo(m_LastFolderOpenList.first()).absolutePath();
		BookInfo bInfo;
		foreach (QString epubItem, m_LastFolderOpenList) {
			QFileInfo fileInfo(epubItem);
			QString extractPath = AQUARIUS_LOCATION_TEMP + "/"+ fileInfo.completeBaseName();
			m_EpubParser->SetZipFilePath(epubItem);
			m_EpubParser->SetFolderPath(extractPath);
			// to extract epub
			if (m_EpubParser->EpubRead()) {
				// to parse epub
				if (m_EpubParser->EpubParsing()) {
					// to add book item
					m_BookListCtrl->AddBookItem();
					QMessageBox::information(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Success to add epub file."));
					ret = true;
				}
				else {
					QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Unable to parse epub file."));
					ret = false;
				}
			}
			else {
				QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Unable to read epub file."));
				ret = false;
			}
		}
	}
	else {
		QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("No items selected."));
		ret = false;
	}

	return ret;

}

bool EpubManager::DeleteEpub()
{
	qDebug() << "EpubManager - DeleteEpub()";
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Are you sure you want to delete the file?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		return true;
	}

	return false;

}

