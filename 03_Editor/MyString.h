#pragma once
#include <afx.h>

/*
 ����һ���ɴ��л�����Ĳ���
(1) Derive your class from CObject. ������һ������ΪCObject���ࣩ
(2) Override the Serialize member function.����д���л�������
(3) Use the DECLARE_SERIAL macro in the class declaration.�����������ļ���ʹ��DECLARE_SERIAL�꣩
(4) Define a constructor with no arguments (a default constructor).������һ���޲����Ĺ��캯����
(5) Use the IMPLEMENT_SERIAL macro in the class implementation file.����ʵ���ļ���ʹ��IMPLEMENT_SERIAL�꣩
*/

class MyString :
    public CObject
{
public:
    DECLARE_SERIAL(MyString) //(3)ʹ��DECLARE_SERIAL��
    MyString::MyString();//(4)һ���޲����Ĺ��캯��
    MyString::MyString(CString str, CPoint point);
    MyString::~MyString();
    void Draw(CDC* pDC);
    void Serialize(CArchive& ar);

public:
    //CString m_str;
    CString m_char;
    CPoint m_point;
    //TEXTMETRIC m_tm;

};

