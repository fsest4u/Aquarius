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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class EpubManager;
//class EpubParser;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_actionAdd_triggered();
	void on_actionDelete_triggered();
	void on_actionExit_triggered();

private:

	void ConnectSignalsToSlots();

	void ReadSetting();
	void WriteSetting();

	EpubManager*	m_EpubManager;
	//EpubParser*		m_EpubParser;
	


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
