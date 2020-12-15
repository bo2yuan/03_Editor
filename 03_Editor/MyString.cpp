#include "stdafx.h"
#include "MyString.h"

IMPLEMENT_SERIAL(MyString, CObject, 1)


MyString::MyString() {

}

MyString::MyString(CString m_char, CPoint m_point) {
	this->m_char = m_char;
    this->m_point = m_point;
}

MyString::~MyString() {

}

void MyString::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << m_char << m_point;
    }
    else
    {
        ar >> m_char >> m_point;
    }
}

void MyString::Draw(CDC* pDC) {
    pDC->TextOut(m_point.x, m_point.y, m_char);
}
