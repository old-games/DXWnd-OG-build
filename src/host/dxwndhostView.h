// dxwndhostView.h : CDxwndhostView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_)
#define AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDxwndhostView : public CListView
{
protected: // シリアライズ機能のみから作成します。
	CDxwndhostView();
	DECLARE_DYNCREATE(CDxwndhostView)

private:
	void Resize(void);
// アトリビュート
public:
	CDxwndhostDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDxwndhostView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 構築後の最初の１度だけ呼び出されます。
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDxwndhostView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
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

#ifndef _DEBUG  // dxwndhostView.cpp ファイルがデバッグ環境の時使用されます。
inline CDxwndhostDoc* CDxwndhostView::GetDocument()
   { return (CDxwndhostDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DXWNDHOSTVIEW_H__E8E112CE_6FE9_4F01_AB94_D53F844D5A09__INCLUDED_)
