/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub Manager.
**
*************************************************************************/

#include <QtCore/QtDebug>
#include <QtCore/QStandardPaths>
#include <QtCore/QVariant>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "EpubManager.h"
#include "EpubParser.h"
#include "bookData/BookListCtrl.h"
#include "misc/SettingData.h"
#include "AquariusContants.h"



static const QString SETTINGS_GROUP = "mainWindow";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_EpubManager(new EpubManager(this))
	//, m_EpubParser(new EpubParser())
{
    ui->setupUi(this);

	ReadSetting();
	InitUI();
	ConnectSignalsToSlots();
}

MainWindow::~MainWindow()
{
	WriteSetting();
    delete ui;

	if (m_EpubManager) {
		delete m_EpubManager;
		m_EpubManager = 0;
	}

	//if (m_EpubParser) {
	//	delete m_EpubParser;
	//	m_EpubParser = 0;
	//}
}

void MainWindow::ReadSetting()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	QByteArray geometry = settings.value("geometry").toByteArray();

	if (!geometry.isNull()) {
		restoreGeometry(geometry);
	}

	settings.endGroup();

}

void MainWindow::WriteSetting()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	settings.setValue("geometry", saveGeometry());


	settings.endGroup();
}

void MainWindow::InitUI()
{
	QDir dir(AQUARIUS_LOCATION_TEMP);
	if (!dir.exists()) {
		dir.mkdir(AQUARIUS_LOCATION_TEMP);
	}

	ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

	m_EpubManager->GetBookListCtrl()->OpenBookList();
	//draw book list
	int sortType = m_EpubManager->GetBookListCtrl()->GetSortType();
	QStringList sortList = m_EpubManager->GetBookListCtrl()->GetSortedList(sortType);
	foreach(QString sortItem, sortList) {
		QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
		item->setData(Qt::UserRole, QVariant(sortItem));
		ui->listWidget->setItemWidget(item, new QLabel(sortItem));
	}

}

void MainWindow::ConnectSignalsToSlots()
{
	connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem *)), m_EpubManager, SLOT(OnItemPressed(QListWidgetItem *)));
	connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), m_EpubManager, SLOT(OnItemClicked(QListWidgetItem *)));
	connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), m_EpubManager, SLOT(OnItemDoubleClicked(QListWidgetItem *)));
#if 0	// block mouse event
	connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem * )), m_EpubManager, SLOT(OnCurrentItemChanged(QListWidgetItem * , QListWidgetItem * )));
	connect(ui->listWidget, SIGNAL(currentRowChanged(int )), m_EpubManager, SLOT(OnCurrentRowChanged(int )));
	connect(ui->listWidget, SIGNAL(currentTextChanged(const QString & )), m_EpubManager, SLOT(OnCurrentTextChanged(const QString & )));
	connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem * )), m_EpubManager, SLOT(OnItemActivated(QListWidgetItem * )));
	connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem * )), m_EpubManager, SLOT(OnItemChanged(QListWidgetItem * )));
	connect(ui->listWidget, SIGNAL(itemEntered(QListWidgetItem * )), m_EpubManager, SLOT(OnItemEntered(QListWidgetItem * )));
	connect(ui->listWidget, SIGNAL(itemSelectionChanged()), m_EpubManager, SLOT(OnItemSelectionChanged()));
#endif
}


void MainWindow::on_actionAdd_triggered()
{
	qDebug() << "on_actionAdd_triggered()";
	m_EpubManager->AddEpubList();
}

void MainWindow::on_actionDelete_triggered()
{
	qDebug() << "on_actionDelete_triggered()";
	// multi item
	QList<QListWidgetItem*> itemList = ui->listWidget->selectedItems();
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str())
		, tr("Are you sure you want to delete the file or files?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		foreach(QListWidgetItem* item, itemList) {
			if (item) {
				m_EpubManager->DeleteEpub(item);
			}
		}
	}
}

void MainWindow::on_actionExit_triggered()
{
	qDebug() << "on_actionExit_triggered()";
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Are you sure you want to exit the application?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		this->close();
		return;
	}
}

void MainWindow::AddListItem(QString key)
{
	qDebug() << "MainWindow - AddListItem()";
	QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
	item->setData(Qt::UserRole, QVariant(key));
	ui->listWidget->setItemWidget(item, new QLabel(key));
}

void MainWindow::UpdateListItem()
{
	qDebug() << "MainWindow - UpdateListItem()";
	int sortType = m_EpubManager->GetBookListCtrl()->GetSortType();
	QStringList sortList = m_EpubManager->GetBookListCtrl()->GetSortedList(sortType);
	foreach(QString sortItem, sortList) {
		QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
		item->setData(Qt::UserRole, QVariant(sortItem));
		ui->listWidget->setItemWidget(item, new QLabel(sortItem));
	}
}

void MainWindow::DeleteListItem(QListWidgetItem* item)
{
	qDebug() << "MainWindow - DeleteListItem()";
	if (item) {
		qDebug() << "item[ " << item->data(Qt::UserRole).toString() << " ]";
		ui->listWidget->removeItemWidget(item);
		ui->listWidget->takeItem(ui->listWidget->currentRow());
	}
}