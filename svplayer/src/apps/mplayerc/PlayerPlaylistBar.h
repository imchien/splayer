/* 
 *	Copyright (C) 2003-2006 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#pragma once
#include <afxcoll.h>
#include "PlayerListCtrl.h"
#include "Playlist.h"

class OpenMediaData;

class CPlayerPlaylistBar : public CSizingControlBarG
{
	DECLARE_DYNAMIC(CPlayerPlaylistBar)

private:
	enum {COL_NAME, COL_TIME};

	CImageList m_fakeImageList;
	CPlayerListCtrl m_list;
	CButton m_clearall;
	CButton m_addsubforplaylist;
	CWnd* m_pMaindFrame;
	int m_nTimeColWidth;
	void ResizeListColumn();

	void AddItem(CString fn, CAtlList<CString>* subs);
	void AddItem(CAtlList<CString>& fns, CAtlList<CString>* subs);
	void ParsePlayList(CString fn, CAtlList<CString>* subs);
	void ParsePlayList(CAtlList<CString>& fns, CAtlList<CString>* subs);

	bool ParseMPCPlayList(CString fn);
	bool SaveMPCPlayList(CString fn, CTextFile::enc e, bool fRemovePath);

	void SetupList();	
	void UpdateList();
	void EnsureVisible(POSITION pos);
	int FindItem(POSITION pos);
	POSITION FindPos(int i);
	
	CImageList* m_pDragImage;
	BOOL m_bDragging;
	int m_nDragIndex, m_nDropIndex;
	CPoint m_ptDropPoint;
	CFont font;

	void DropItemOnList();

public:
	CPlayerPlaylistBar();
	virtual ~CPlayerPlaylistBar();

	BOOL Create(CWnd* pParentWnd);

	CPlaylist m_pl;

	void CheckForPlaylistSubtitle();

	int GetCount();
	int GetSelIdx();
	void SetSelIdx(int i);
	bool IsAtEnd();
	bool GetCur(CPlaylistItem& pli);
	CString GetCur();
	void SetNext(), SetPrev(), SetFirst(), SetLast();
	void SetCurValid(bool fValid);
	void SetCurTime(REFERENCE_TIME rt);
	int GetTotalTimeBeforeCur();
	void Refresh();
	void Empty();

	void FindMoreFileFromOneFileAndPutIntoPlaylist(CString szMediaFile , CAtlList<CString>& szaIn );
	void Open(CAtlList<CString>& fns, bool fMulti, CAtlList<CString>* subs = NULL, int smartAddMorefile = 1);
	void Append(CAtlList<CString>& fns, bool fMulti, CAtlList<CString>* subs = NULL);

	void Open(CStringW vdn, CStringW adn, int vinput, int vchannel, int ainput);
	void Append(CStringW vdn, CStringW adn, int vinput, int vchannel, int ainput);

	OpenMediaData* GetCurOMD(REFERENCE_TIME rtStart = 0);

	void LoadPlaylist();
	void SavePlaylist();

	POSITION FindPosByFilename(CString fn);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnButtonClearAll();
	afx_msg void OnButtonAddSubForPlayList();
	afx_msg void OnUpdateButtonAddSubForPlayList(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus( CWnd* pOldWnd );

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnKeyDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnFileClosePlaylist(UINT nID);
	afx_msg BOOL OnPlayPlay(UINT nID);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLvnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
};
