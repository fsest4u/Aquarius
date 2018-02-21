/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub PC Viewer.
**
*************************************************************************/

#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <QtDebug>
#include <QtCore/QStandardPaths>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>


#include "EpubManager.h"
#include "EpubParser.h"
#include "bookData/BookListCtrl.h"
#include "misc/SettingData.h"



static const QString SETTINGS_GROUP = "mainWindow";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_EpubManager(new EpubManager())
	//, m_EpubParser(new EpubParser())
{
    ui->setupUi(this);

	ReadSetting();

	m_EpubManager->GetBookListCtrl()->OpenBookList();
	QStringList sortList = m_EpubManager->GetBookListCtrl()->GetSortedList(0);	// SORT_NONE
	foreach(QString sortItem, sortList) {
		QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
		item->setData(Qt::UserRole, QVariant(sortItem));
		ui->listWidget->setItemWidget(item, new QLabel(sortItem));
	}
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

void MainWindow::ConnectSignalsToSlots()
{

}


void MainWindow::on_actionAdd_triggered()
{
	qDebug() << "on_actionAdd_triggered()";
	ui->listWidget->clear();
	int sortType = m_EpubManager->GetBookListCtrl()->GetSortType();

	m_EpubManager->AddEpubList();
	QStringList sortList = m_EpubManager->GetBookListCtrl()->GetSortedList(sortType);
	foreach(QString sortItem, sortList) {
		QListWidgetItem *item = new QListWidgetItem();
		item->setData(Qt::UserRole, QVariant(sortItem));
		ui->listWidget->setItemWidget(item, new QLabel(sortItem));
	}

}

void MainWindow::on_actionDelete_triggered()
{
	qDebug() << "on_actionDelete_triggered()";
	QListWidgetItem* item = ui->listWidget->currentItem();
	if (item && m_EpubManager->DeleteEpub(item->data(Qt::UserRole).toString())) {
		ui->listWidget->removeItemWidget(item);
		ui->listWidget->takeItem(ui->listWidget->currentRow());
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

