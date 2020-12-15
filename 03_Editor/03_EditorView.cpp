
// 03_EditorView.cpp : CMy03_EditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "03_Editor.h"
#endif

#include "03_EditorDoc.h"
#include "03_EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MyString.h"


// CMy03_EditorView

IMPLEMENT_DYNCREATE(CMy03_EditorView, CView)

BEGIN_MESSAGE_MAP(CMy03_EditorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	//ON_COMMAND(ID_FILE_SAVE, &CMy03_EditorView::OnFileSave)
	//ON_COMMAND(ID_FILE_OPEN, &CMy03_EditorView::OnFileOpen)
END_MESSAGE_MAP()

// CMy03_EditorView 构造/析构

CMy03_EditorView::CMy03_EditorView()
	: m_point(0)
	, str(_T(""))
{
	//m_dcMetaFile.Create();// 创建内存的原文件
	// TODO: 在此处添加构造代码

}

CMy03_EditorView::~CMy03_EditorView()
{
}

BOOL CMy03_EditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy03_EditorView 绘制

void CMy03_EditorView::OnDraw(CDC* pDC)
{
	CMy03_EditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 在此处为本机数据添加绘制代码
	// 窗口重绘之前要保存当前字符串
	MyString* pMystr = new MyString(str, m_point);
	pDoc->m_obArray.Add(pMystr);
	str.Empty();

	int count;

	count = pDoc->m_obArray.GetSize();

	for (int i = 0; i < count; i++)
	{
		((MyString*)pDoc->m_obArray.GetAt(i))->Draw(pDC);
	}
}


// CMy03_EditorView 打印

BOOL CMy03_EditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy03_EditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy03_EditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy03_EditorView 诊断

#ifdef _DEBUG
void CMy03_EditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy03_EditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy03_EditorDoc* CMy03_EditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03_EditorDoc)));
	return (CMy03_EditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy03_EditorView 消息处理程序

//创建文本插入符
int CMy03_EditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	/*CreateSolidCaret(20, 100);*/
	//获取字体信息
	CClientDC dc(this);

	TEXTMETRIC tm; //字体信息结构体

	dc.GetTextMetrics(&tm);

	//继承与CWnd
	CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight); //创建文本插入符

	ShowCaret(); //显示

	return 0;
}


void CMy03_EditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMy03_EditorDoc* pDoc = GetDocument();
	MyString* pMystr = new MyString(str, m_point);
	pDoc->m_obArray.Add(pMystr);

	m_point = point;
	SetCaretPos(point); //移动插入符
	//保存点击坐标
	ShowCaret();
	//清空
	str = TEXT("");
	str.Empty();


	CView::OnLButtonDown(nFlags, point);
}

//点击键盘，启动调用
void CMy03_EditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//str += (TCHAR)nChar;
	CClientDC dc(this);
	CFont font;
	//font.CreatePointFont(200, "宋体", NULL);// 创建字体
	//CFont *pOldFont = dc.SelectObject(&font);	// 将字体选单设备描述表中，在pOld中
	//m_dcMetaFile.SelectObject(&font);	// 将字体选单设备描述表中，在pOld中
	
	CMy03_EditorDoc* pDoc = GetDocument();
	//CSize size = pDoc->m_ptrArray.GetSize();
	//int x = m_point.x + size.cx;
	//int y = m_point.y;
	//SetCaretPos(CPoint(x, y));//转对象为点
	TEXTMETRIC tm; //字体信息结构体

	dc.GetTextMetrics(&tm);

	if (nChar == VK_RETURN) //换行
	{
		// 保存上一行的字符串到MyString类
		MyString* pMystr = new MyString(str, m_point);
		pDoc->m_obArray.Add(pMystr);
		m_point.y = m_point.y + 1.5 * tm.tmHeight;
		SetCaretPos(m_point);
		str.Empty();
	}
	else if (nChar == VK_BACK) //退格
	{
		//获取背景图
		COLORREF color = dc.GetBkColor();
		//设置写字的颜色
		COLORREF oldColor = dc.SetTextColor(color);
		//白色重写一次
		dc.TextOut(m_point.x, m_point.y, str);
		str = str.Left(str.GetLength() - 1);
		//恢复原来颜色
		dc.SetTextColor(oldColor);
		SetCaretPos(m_point);

	}
	else
	{
		str += (TCHAR)nChar;
	}
	

	CSize size = dc.GetTextExtent(str); //获取字符串长度
	int x = m_point.x + size.cx;
	int y = m_point.y;
	SetCaretPos(CPoint(x, y));//转对象为点
	dc.TextOut(m_point.x, m_point.y, str);


	CView::OnChar(nChar, nRepCnt, nFlags);
}

