/************************************************************************
**
**  Copyright (C) 2018  spdevapp <spdevapp@joara.com>
**
**  This file is part of Aquarius.
**
**  Aquarius is Epub Manager.
**
*************************************************************************/
#include "BookInfo.h"



BookInfo::BookInfo()
	: m_Filename("")
	, m_Title("")
	, m_Author("")
	, m_Genre("")
	//, m_DownloadTime("")
	//, m_ReadTime("")
	, m_Filesize(0.0)
	, m_CoverPath("")
	, m_Library("")
{
}


BookInfo::~BookInfo()
{
}
