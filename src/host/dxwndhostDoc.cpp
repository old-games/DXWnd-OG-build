// dxwndhostDoc.cpp : CDxwndhostDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "dxwndhost.h"

#include "dxwndhostDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostDoc

IMPLEMENT_DYNCREATE(CDxwndhostDoc, CDocument)

BEGIN_MESSAGE_MAP(CDxwndhostDoc, CDocument)
	//{{AFX_MSG_MAP(CDxwndhostDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostDoc �N���X�̍\�z/����

CDxwndhostDoc::CDxwndhostDoc()
{
}

CDxwndhostDoc::~CDxwndhostDoc()
{
}

BOOL CDxwndhostDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDxwndhostDoc �V���A���C�[�[�V����

void CDxwndhostDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostDoc �N���X�̐f�f

#ifdef _DEBUG
void CDxwndhostDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDxwndhostDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDxwndhostDoc �R�}���h
