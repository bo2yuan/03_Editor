
// 03_EditorView.h : CMy03_EditorView 类的接口
//

#pragma once
#include "atltypes.h"


class CMy03_EditorView : public CView
{
protected: // 仅从序列化创建
	CMy03_EditorView();
	DECLARE_DYNCREATE(CMy03_EditorView)

// 特性
public:
	CMy03_EditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy03_EditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint m_point;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString str;
	CMetaFileDC m_dcMetaFile;
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // 03_EditorView.cpp 中的调试版本
inline CMy03_EditorDoc* CMy03_EditorView::GetDocument() const
   { return reinterpret_cast<CMy03_EditorDoc*>(m_pDocument); }
#endif

