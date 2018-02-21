/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub Manager.
**
*************************************************************************/

#pragma once
#ifndef EPUB_MANAGER_H
#define EPUB_MANAGER_H

#include <QtWidgets/QWidget>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QStringList>

class QListWidgetItem;
class MainWindow;
class EpubParser;
class BookListCtrl;
class BookInfo;


class EpubManager : public QWidget
{
	Q_OBJECT

public:
    EpubManager(QWidget* parent = 0);
    virtual ~EpubManager();

	bool AddEpubList();
	bool DeleteEpub(QListWidgetItem* item);

	BookListCtrl*	GetBookListCtrl() { return m_BookListCtrl; }

signals:

	void AddListItem(QString key);
	void DeleteListItem(QListWidgetItem* item);
	void UpdateListItem();

public slots:
	
	void OnItemPressed(QListWidgetItem * item);
	void OnItemClicked(QListWidgetItem * item);
	void OnItemDoubleClicked(QListWidgetItem * item);
#if 0	// block mouse event
	void OnCurrentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
	void OnCurrentRowChanged(int currentRow);
	void OnCurrentTextChanged(const QString & currentText);
	void OnItemActivated(QListWidgetItem * item);
	void OnItemChanged(QListWidgetItem * item);
	void OnItemEntered(QListWidgetItem * item);
	void OnItemSelectionChanged();
#endif

private:

	void			ReadSetting();
	void			WriteSetting();

	void			ConnectSignalsToSlots();

	BookInfo*		CovertBookInfo(QFileInfo& fileInfo);

	MainWindow *	m_mainWindow;
	EpubParser*		m_EpubParser;
	BookListCtrl*	m_BookListCtrl;

	QString			m_LastFolderOpen;
	QStringList		m_LastFolderOpenList;

	double			m_LastPressTime;


};

#endif // EPUB_MANAGER_H
