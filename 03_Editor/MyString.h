#pragma once
#include <afx.h>

/*
 生成一个可串行化的类的步骤
(1) Derive your class from CObject. （定义一个基类为CObject的类）
(2) Override the Serialize member function.（重写串行化函数）
(3) Use the DECLARE_SERIAL macro in the class declaration.（在类声明文件中使用DECLARE_SERIAL宏）
(4) Define a constructor with no arguments (a default constructor).（定义一个无参数的构造函数）
(5) Use the IMPLEMENT_SERIAL macro in the class implementation file.（在实现文件中使用IMPLEMENT_SERIAL宏）
*/

class MyString :
    public CObject
{
public:
    DECLARE_SERIAL(MyString) //(3)使用DECLARE_SERIAL宏
    MyString::MyString();//(4)一个无参数的构造函数
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

