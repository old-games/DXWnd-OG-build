// dxwndhostView.h : CDxwndhostView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_)
#define AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDxwndhostView : public CListView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDxwndhostView();
	DECLARE_DYNCREATE(CDxwndhostView)

private:
	void Resize(void);
// �A�g���r���[�g
public:
	CDxwndhostDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDxwndhostView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDxwndhostView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDxwndhostView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRun();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // dxwndhostView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CDxwndhostDoc* CDxwndhostView::GetDocument()
   { return (CDxwndhostDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_)
