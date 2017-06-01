// TT_Matrix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



int main()
{
	cout << "矩阵ａ：" << endl;
	Matrix<double> a(2, 2);
	a.inPut();
	a.outPut();

	cout << "矩阵ｂ：" << endl;
	Matrix<double> b(2, 2);
	b.inPut();
	b.outPut();

	cout << "矩阵ｃ：" << endl;
	Matrix<double> c = a + b;
	c.outPut();

	cout << "矩阵Ｄ：" << endl;
	Matrix<double> D = a;
	D.outPut();

	cout << "矩阵ａ转置：" << endl;
	a.outPut();
	a.transpose();
	a.outPut();

	cout << "矩阵ｅ　＝　ｂ－ａ：" << endl;
	Matrix<double> e = b - a;
	e.outPut();

	cout << "矩阵ｅ重排：" << endl;
	e.reshape(1, 4);
	e.outPut();
	e.reshape(4, 1);
	e.outPut();

	cout << "矩阵ｆ：" << endl;
	Matrix<double> f(2, 3);
	f.inPut();
	f.outPut();
	a.outPut();
	cout << "矩阵ａ＊ｆ：" << endl;
	f = a * f;
	f.outPut();
	cout << "矩阵ｆ的模：" << endl;
	cout << f.norm2() << endl << endl;;
	system("pause");
    return 0;
}

