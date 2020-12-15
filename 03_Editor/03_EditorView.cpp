
// 03_EditorView.cpp : CMy03_EditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	//ON_COMMAND(ID_FILE_SAVE, &CMy03_EditorView::OnFileSave)
	//ON_COMMAND(ID_FILE_OPEN, &CMy03_EditorView::OnFileOpen)
END_MESSAGE_MAP()

// CMy03_EditorView ����/����

CMy03_EditorView::CMy03_EditorView()
	: m_point(0)
	, str(_T(""))
{
	//m_dcMetaFile.Create();// �����ڴ��ԭ�ļ�
	// TODO: �ڴ˴���ӹ������

}

CMy03_EditorView::~CMy03_EditorView()
{
}

BOOL CMy03_EditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy03_EditorView ����

void CMy03_EditorView::OnDraw(CDC* pDC)
{
	CMy03_EditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	// �����ػ�֮ǰҪ���浱ǰ�ַ���
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


// CMy03_EditorView ��ӡ

BOOL CMy03_EditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy03_EditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy03_EditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy03_EditorView ���

#ifdef _DEBUG
void CMy03_EditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy03_EditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy03_EditorDoc* CMy03_EditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy03_EditorDoc)));
	return (CMy03_EditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy03_EditorView ��Ϣ�������

//�����ı������
int CMy03_EditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	/*CreateSolidCaret(20, 100);*/
	//��ȡ������Ϣ
	CClientDC dc(this);

	TEXTMETRIC tm; //������Ϣ�ṹ��

	dc.GetTextMetrics(&tm);

	//�̳���CWnd
	CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight); //�����ı������

	ShowCaret(); //��ʾ

	return 0;
}


void CMy03_EditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMy03_EditorDoc* pDoc = GetDocument();
	MyString* pMystr = new MyString(str, m_point);
	pDoc->m_obArray.Add(pMystr);

	m_point = point;
	SetCaretPos(point); //�ƶ������
	//����������
	ShowCaret();
	//���
	str = TEXT("");
	str.Empty();


	CView::OnLButtonDown(nFlags, point);
}

//������̣���������
void CMy03_EditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	//str += (TCHAR)nChar;
	CClientDC dc(this);
	CFont font;
	//font.CreatePointFont(200, "����", NULL);// ��������
	//CFont *pOldFont = dc.SelectObject(&font);	// ������ѡ���豸�������У���pOld��
	//m_dcMetaFile.SelectObject(&font);	// ������ѡ���豸�������У���pOld��
	
	CMy03_EditorDoc* pDoc = GetDocument();
	//CSize size = pDoc->m_ptrArray.GetSize();
	//int x = m_point.x + size.cx;
	//int y = m_point.y;
	//SetCaretPos(CPoint(x, y));//ת����Ϊ��
	TEXTMETRIC tm; //������Ϣ�ṹ��

	dc.GetTextMetrics(&tm);

	if (nChar == VK_RETURN) //����
	{
		// ������һ�е��ַ�����MyString��
		MyString* pMystr = new MyString(str, m_point);
		pDoc->m_obArray.Add(pMystr);
		m_point.y = m_point.y + 1.5 * tm.tmHeight;
		SetCaretPos(m_point);
		str.Empty();
	}
	else if (nChar == VK_BACK) //�˸�
	{
		//��ȡ����ͼ
		COLORREF color = dc.GetBkColor();
		//����д�ֵ���ɫ
		COLORREF oldColor = dc.SetTextColor(color);
		//��ɫ��дһ��
		dc.TextOut(m_point.x, m_point.y, str);
		str = str.Left(str.GetLength() - 1);
		//�ָ�ԭ����ɫ
		dc.SetTextColor(oldColor);
		SetCaretPos(m_point);

	}
	else
	{
		str += (TCHAR)nChar;
	}
	

	CSize size = dc.GetTextExtent(str); //��ȡ�ַ�������
	int x = m_point.x + size.cx;
	int y = m_point.y;
	SetCaretPos(CPoint(x, y));//ת����Ϊ��
	dc.TextOut(m_point.x, m_point.y, str);


	CView::OnChar(nChar, nRepCnt, nFlags);
}

