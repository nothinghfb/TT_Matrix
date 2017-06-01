// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <math.h>


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <iostream>
using namespace std;

template<typename T> class Matrix
{
private:
	int col;//����
	int row;//����
	T* mat;
public:
	Matrix(int row = 0, int col = 0);
	~Matrix();

public:
	Matrix(Matrix<T>& obj);//

	void inPut(int row, int col,int mode = 0);
	void inPut(int mode = 0);
	void outPut();

	void setRow(int m);// ��������
	void setCol(int n);// ��������

	int getRow();// ��ȡ����
	int getCol();// ��ȡ����

	const T* const getMatPtr();// ��ȡ����ָ��

	T getElement(int m, int n);
	void setElement(int m, int n, T data);

	T* getRowData(int lineNumber);// ȡ��ĳһ�е�ֵ
	void setRowData(T* Data, int length, int Row , int beginInd = 0);//����ĳһ�е�ֵ

	T* getColData(int colNum);// ȡ��ĳһ�е�Ԫ��ֵ
	void setColData(T* Data, int length,int colNum, int beginInd = 0);// ����ĳһ�е�Ԫ��ֵ

	void transpose();// ת��

	long double norm2();// 2������ģ��

	void reshape(int m, int n);// ��m*n�ľ������ų�m1*n1�ľ���m*n == m1*n1

	Matrix<T> operator+(Matrix<T>& obj);
	Matrix<T> operator-(Matrix<T>& obj);
	Matrix<T> operator*(Matrix<T>& obj);

	Matrix<T> operator=(Matrix<T>& obj);

private:

};

template<typename T>
void Matrix<T>::inPut(int mode /*= 0*/)
{
	cout << "Please Input " << row << " * " << col  << " Elements: ";
	if (mode != 0)
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				T data;
				cin >> data;
				mat[j*this->col + i] = data;
			}
		}
	else
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				T data;
				cin >> data;
				mat[i*this->col + j] = data;
			}
		}
	cout << "Input Finished! " << endl;
}

template<typename T>
Matrix<T> Matrix<T>::operator=(Matrix<T>& obj)
{
	col = obj.getCol();
	row = obj.getRow();
	if (mat) 
	{
		delete[] mat;
	}
	if (row <= 0 || col <= 0)
		mat = nullptr;
	mat = new T[row*col];
	memcpy(mat, obj.getMatPtr(), sizeof(T)*row*col);
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& obj)
{
	if (col != obj.row)
	{
		cout << " Error dimension match ...... via *" << endl;
		return *this;
	}
	Matrix<T> *rt = new Matrix<T>(row,obj.col);

	for (int i = 0; i < row; ++i)
	{
		for (int k = 0; k < obj.col; ++k)
		{
			T tem = (T)0;
			for (int j = 0; j < col; ++j)
			{
				tem += mat[i*col + j] * obj.getElement(j, k);
			}
			rt->setElement(i, k, tem);
		}
	}
	return *rt;

}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& obj)
{
	if (obj.col != col || obj.row != row)
	{
		cout << " Error Dimension match .....via operator + " << endl;
		return *this;
	}
	Matrix<T> *rt = new Matrix<T>(row, col);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			rt->setElement(i, j, mat[i*col + j] - obj.getElement(i, j));
		}
	}
	return *rt;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& obj)
{
	if (obj.col != col || obj.row != row)
	{
		cout << " Error Dimension match .....via operator + " << endl;
		return *this;
	}
	Matrix<T> *rt = new Matrix<T>(row,col);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			 rt->setElement(i,j, mat[i*col + j] + obj.getElement(i, j));
		}
	}
	return *rt;
}

template<typename T>
void Matrix<T>::reshape(int m, int n)
{
	if (m*n != row*col)
		return;
	row = m;
	col = n;
}

template<typename T>
long double Matrix<T>::norm2()
{
	long double rt = 0.0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			rt += mat[i*col + j]* mat[i*col + j];
		}
	}
	return sqrtl(rt);
}


template<typename T>
void Matrix<T>::transpose()
{
	if (row <= 0 || col <= 0)
		return;
	T* tem = new T[row*col];
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			tem[row*j + i] = mat[col *i +j];
		}
	}
	delete[] mat;
	mat = tem;
	int t = row;
	row = col;
	col = t;
}

template<typename T>
void Matrix<T>::setColData(T* Data, int length, int colNum , int beginInd /*= 0*/)
{
	if (!Data || length <= 0 || beginInd <0 || beginInd > col)
		return;
	int tLen = col - beginInd;
	for (int j = 0; j < tLen; ++j)
	{
		mat[j*col + colNum] = Data[j];
	}
}

template<typename T>
T* Matrix<T>::getColData(int colNum)
{
	if (colNum< 0 || colNum > col)
		return nullptr;
	T* rt = new T[row];
	for (int i = 0; i < row; ++i)
	{
		rt[i] = mat[i*col  + colNum];
	}
	return rt;
}

template<typename T>
void Matrix<T>::setRowData(T* Data, int length, int Row ,int beginInd /*= 0*/)
{
	if (!data || beginInd < 0 || length < 0)
		return;
	int tLen = col - beginInd;
	memcpy(mat + Row * col + beginInd, Data, sizeof(T)*(tLen < length ? tLen : length));
}

template<typename T>
T* Matrix<T>::getRowData(int lineNumber)
{
	if (lineNumber < 0 || lineNumber > row)
		return nullptr;
	T* rt = new T[col];
	memcpy(rt, mat + col*lineNumber);
	return rt;
}

template<typename T>
void Matrix<T>::setElement(int m, int n, T data)
{
	mat[m*col + n] = data;
}

template<typename T>
T Matrix<T>::getElement(int m, int n)
{
	return mat[m*col + n];
}

template<typename T> const
T*  const Matrix<T>::getMatPtr()
{
	return mat;
}

template<typename T>
int Matrix<T>::getCol()
{
	return col;
}

template<typename T>
int Matrix<T>::getRow()
{
	return row;
}

template<typename T>
void Matrix<T>::setCol(int n)
{
	col = n;
}

template<typename T>
void Matrix<T>::setRow(int m)
{
	row = m;
}

template<typename T>
void Matrix<T>::outPut()
{
	if (row <= 0 || col <= 0)
		return;
	cout << endl;
	for(int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << mat[i*col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>
void Matrix<T>::inPut(int rowN /*= 0*/, int colN /*= 0*/, int mode /*= 0*/)
{
	// mode == 0, �����������.
	// ����,��������
	if (rowN == 0 && colN == 0)
	{
		colN = col;
		rowN = row;
	}
	else if ((rowN < 0 || colN < 0) && row*col != rowN*colN)
		return;
	cout << "Please Input row * col Elements: ";
	if(mode != 0)
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				T data;
				cin >> data;
				mat[j*this->col + i] = data;
			}
		}
	else
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				T data;
				cin >> data;
				mat[i*this->col + j] = data;
			}
		}
	cout << "Input Finished! " << endl;
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>& obj)
{
	row = obj.getRow();
	col = obj.getCol();

	if (row <= 0 || col <= 0)
		mat = nullptr;
	else
	{
		mat = new T[row*col];
		memcpy(mat, obj.getMatPtr(), sizeof(T)*row*col);
	}

}

template<typename T>
Matrix<T>::~Matrix()
{
	if (!mat) delete[] mat;
}

template<typename T>
Matrix<T>::Matrix(int row /*= 0*/, int col /*= 0*/):row(row),col(col)
{
	if (col <= 0 && row <= 0)
		mat = nullptr;
	mat = new T[col*row];

}
