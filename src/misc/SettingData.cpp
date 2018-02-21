/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub Manager.
**
*************************************************************************/

#include <QtCore/QStandardPaths>

#include "SettingData.h"



SettingData::SettingData()
	: QSettings(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/aquarius/aquarius.ini", QSettings::IniFormat)
{
}


SettingData::~SettingData()
{
}
