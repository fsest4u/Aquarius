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
#ifndef BOOKLISTVIEW_H
#define BOOKLISTVIEW_H

class BookListView
{
public:
	BookListView();
	virtual ~BookListView();

	int GetViewMode() { return m_ViewMode; }
	bool DrawBookList();

private:

	int m_ViewMode;

};

#endif	// BOOKLISTVIEW_H