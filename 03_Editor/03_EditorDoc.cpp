
// 03_EditorDoc.cpp : CMy03_EditorDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "03_Editor.h"
#endif

#include "03_EditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MyString.h"

// CMy03_EditorDoc

IMPLEMENT_DYNCREATE(CMy03_EditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy03_EditorDoc, CDocument)
END_MESSAGE_MAP()


// CMy03_EditorDoc 构造/析构

CMy03_EditorDoc::CMy03_EditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMy03_EditorDoc::~CMy03_EditorDoc()
{
}

BOOL CMy03_EditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy03_EditorDoc 序列化

void CMy03_EditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		int count = m_obArray.GetSize();
		ar << count;
		for (int i = 0; i < count; i++) {
			ar << m_obArray.GetAt(i);
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		int count;
		MyString* pMyString;

		ar >> count;

		for (int i = 0; i < count; i++)
		{
			ar >> pMyString;
			m_obArray.Add(pMyString);
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy03_EditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy03_EditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy03_EditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy03_EditorDoc 诊断

#ifdef _DEBUG
void CMy03_EditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy03_EditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy03_EditorDoc 命令


void CMy03_EditorDoc::DeleteContents()
{
	// TODO: 在此添加专用代码和/或调用基类
	int nCount;
	nCount = m_obArray.GetSize();
	/* 删除一个元素之后，后面的元素会向前补位，倒序删除数据不会移动位置，删除不会出错 */
	while (nCount--)
	{
		delete m_obArray.GetAt(nCount);
		m_obArray.RemoveAt(nCount);
	}
	CDocument::DeleteContents();
}
