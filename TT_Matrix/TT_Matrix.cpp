// TT_Matrix.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"



int main()
{
	cout << "����᣺" << endl;
	Matrix<double> a(2, 2);
	a.inPut();
	a.outPut();

	cout << "����⣺" << endl;
	Matrix<double> b(2, 2);
	b.inPut();
	b.outPut();

	cout << "����㣺" << endl;
	Matrix<double> c = a + b;
	c.outPut();

	cout << "����ģ�" << endl;
	Matrix<double> D = a;
	D.outPut();

	cout << "�����ת�ã�" << endl;
	a.outPut();
	a.transpose();
	a.outPut();

	cout << "����塡�����⣭�᣺" << endl;
	Matrix<double> e = b - a;
	e.outPut();

	cout << "��������ţ�" << endl;
	e.reshape(1, 4);
	e.outPut();
	e.reshape(4, 1);
	e.outPut();

	cout << "����棺" << endl;
	Matrix<double> f(2, 3);
	f.inPut();
	f.outPut();
	a.outPut();
	cout << "����ᣪ�棺" << endl;
	f = a * f;
	f.outPut();
	cout << "������ģ��" << endl;
	cout << f.norm2() << endl << endl;;
	system("pause");
    return 0;
}

