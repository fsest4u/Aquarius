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
#include <QtCore/QDateTime>
#include <QtCore/QStandardPaths>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMessageBox>

#include "EpubParser.h"
#include "AquariusContants.h"
#include "bookData/BookListCtrl.h"
#include "bookData/BookInfo.h"
#include "mainUI/MainWindow.h"
#include "misc/SettingData.h"



const QString SETTINGS_GROUP = "epubmanager";

const QString AQUARIUS_LOCATION_DOCUMENTS = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/aquarius";
const QString AQUARIUS_LOCATION_TEMP = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/aquarius";

const double LONG_PRESS_TIME_THRESHOLD = 500.0;	// unit ms


EpubManager::EpubManager(QWidget* parent)
	: QWidget(parent)
	, m_mainWindow(qobject_cast<MainWindow *>(parent))
	, m_EpubParser(new EpubParser())
	, m_BookListCtrl(new BookListCtrl(parent))
	, m_LastFolderOpen("")
{
    m_LastFolderOpenList.clear();

	ReadSetting();

	ConnectSignalsToSlots();
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

void EpubManager::ConnectSignalsToSlots()
{
	connect(this, SIGNAL(AddListItem(QString)), m_mainWindow, SLOT(AddListItem(QString)));
	connect(this, SIGNAL(DeleteListItem(QListWidgetItem *)), m_mainWindow, SLOT(DeleteListItem(QListWidgetItem *)));
	connect(this, SIGNAL(UpdateListItem()), m_mainWindow, SLOT(UpdateListItem()));
}

BookInfo* EpubManager::CovertBookInfo(QFileInfo& fileInfo)
{
	BookInfo* bInfo = new BookInfo();

	bInfo->SetFilename(fileInfo.completeBaseName());
	bInfo->SetTitle(m_EpubParser->GetMetadataTitle());
	bInfo->SetAuthor(m_EpubParser->GetMetadataAuthor());
	bInfo->SetGenre(m_EpubParser->GetMetadataGenre());
	bInfo->SetDownloadTime(fileInfo.lastModified());
	bInfo->SetReadTime(fileInfo.lastRead());
	bInfo->SetFilesize(fileInfo.size());
	bInfo->SetCoverPath(m_EpubParser->GetMetadataCoverPath());
	bInfo->SetLibrary("");

	return bInfo;
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

					BookInfo* bInfo = CovertBookInfo(fileInfo);
					// to add book item
					m_BookListCtrl->AddBookItem(bInfo);
					emit AddListItem(bInfo->GetFilename());
				}
				else {
					QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr(QString("Unable to parse epub file. - %1").arg(fileInfo.fileName()).toStdString().c_str()));
				}
			}
			else {
				QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr(QString("Unable to read epub file. - %1").arg(fileInfo.fileName()).toStdString().c_str()));
			}
		}
	}
	else {
		QMessageBox::warning(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("No items selected."));
		return false;
	}

	//emit UpdateListItem();
	QMessageBox::information(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Success to add epub file."));
	return true;
}

bool EpubManager::DeleteEpub(QString key)
{
	qDebug() << "EpubManager - DeleteEpub()";
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str())
								, tr("Are you sure you want to delete the file?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		m_BookListCtrl->DeleteBookItem(key);
		// to remove directory
		QString removePath = AQUARIUS_LOCATION_TEMP + "/" + key;
		QDir dir(removePath);
		if (dir.exists()) {
			dir.removeRecursively();
		}
		return true;
	}

	return false;

}

void EpubManager::OnItemPressed(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemPressed() - mouse button down";
	m_LastPressTime = QDateTime::currentMSecsSinceEpoch();
}

void EpubManager::OnItemClicked(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemClicked() - mouse left button up";
	double releaseTime = QDateTime::currentMSecsSinceEpoch() - m_LastPressTime;
	qDebug() << "EpubManager - releaseTime " << releaseTime;
	if (releaseTime > LONG_PRESS_TIME_THRESHOLD) {
		if (item && DeleteEpub(item->data(Qt::UserRole).toString())) {
			//if (item) {
			emit DeleteListItem(item);
		}

	}
}

void EpubManager::OnItemDoubleClicked(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemDoubleClicked()";
}

#if 1
void EpubManager::OnCurrentItemChanged(QListWidgetItem * current, QListWidgetItem * previous)
{
	qDebug() << "EpubManager - OnCurrentItemChanged()";
}

void EpubManager::OnCurrentRowChanged(int currentRow)
{
	qDebug() << "EpubManager - OnCurrentRowChanged()";
}

void EpubManager::OnCurrentTextChanged(const QString & currentText)
{
	qDebug() << "EpubManager - OnCurrentTextChanged()";
}

void EpubManager::OnItemActivated(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemActivated()";
}

void EpubManager::OnItemChanged(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemChanged()";
}

void EpubManager::OnItemEntered(QListWidgetItem * item)
{
	qDebug() << "EpubManager - OnItemEntered()";
}

void EpubManager::OnItemSelectionChanged()
{
	qDebug() << "EpubManager - OnItemSelectionChanged()";
}
#endif
