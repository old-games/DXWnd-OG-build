// dxwndhost.h : DXWNDHOST �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_)
#define AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� dxwndhost.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CDxwndhostApp : public CWinApp
{
public:
	CDxwndhostApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDxwndhostApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CDxwndhostApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DXWNDHOST_H__C68B92A2_C45F_4B59_986D_5BBC6BAD3AD8__INCLUDED_)
