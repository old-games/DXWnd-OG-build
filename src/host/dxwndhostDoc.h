// dxwndhostDoc.h : CDxwndhostDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXWNDHOSTDOC_H__07C9FF34_8B9B_49CC_BE82_B76813FE88FE__INCLUDED_)
#define AFX_DXWNDHOSTDOC_H__07C9FF34_8B9B_49CC_BE82_B76813FE88FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDxwndhostDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CDxwndhostDoc();
	DECLARE_DYNCREATE(CDxwndhostDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDxwndhostDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CDxwndhostDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDxwndhostDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DXWNDHOSTDOC_H__07C9FF34_8B9B_49CC_BE82_B76813FE88FE__INCLUDED_)
