#pragma once
#include <bits/stdc++.h>
using namespace std;


template<class U>
ostream &operator<<(ostream &out, vector<U> &N)
{
    for(int i=0; i<N.size(); i++)
    {
        out<<N[i]<<" ";
    }
    return out;
}

template<class T>
class Matrix
{
    private:
        vector<vector<T>> M;
        int row = 0;
        int col = 0;
    public:
        Matrix();
        Matrix(int);
        Matrix(int,int);
        T operator()(int,int);
        void operator()(int,int, T);
        vector<T>& operator[](int);
        int getRow();
        int getCol();
        void print();
        Matrix<T> operator+(Matrix<T>);
        Matrix<T> operator-(Matrix<T>);
        Matrix<T> operator*(Matrix<T>);
        Matrix<T> operator+(double);
        Matrix<T> operator-(double);
        Matrix<T> operator*(double);
        template<class T1>
        friend Matrix<T1> operator+(double, Matrix<T1>);
        template<class T1>
        friend Matrix<T1> operator-(double, Matrix<T1>);
        template<class T1>
        friend Matrix<T1> operator*(double, Matrix<T1>);
        template<class T1>
        friend ostream &operator<<(ostream &, Matrix<T1> &);
        template<class T1>
        friend istream &operator>>(istream &, Matrix<T1> &);
};

template<class T>
Matrix<T> :: Matrix()
{
    vector<T> v1;
    row = 1;
    col = 1;
    for(int j=0; j<1; j++)
    {
        v1.push_back(0);
    }

    for(int i=0; i<1; i++)
    {
        M.push_back(v1);
    }
}

template<class T>
Matrix<T> :: Matrix(int r)
{
    vector<T> v1;
    row = r;
    col = r;
    for(int j=0; j<r; j++)
    {
        v1.push_back(0);
    }

    for(int i=0; i<r; i++)
    {
        M.push_back(v1);
    }
}

template<class T>
Matrix<T> :: Matrix(int r, int c)
{
    vector<T> v1;
    row = r;
    col = c;
    for(int j=0; j<c; j++)
    {
        v1.push_back(0);
    }

    for(int i=0; i<r; i++)
    {
        M.push_back(v1);
    }
}

template<class T>
T Matrix<T>:: operator()(int i, int j)
{
    return this->M[i][j];
}

template<class T>
void Matrix<T>:: operator()(int i, int j, T value)
{
    this->M[i][j] = value;
}

template<class T>
vector<T>& Matrix<T>:: operator[](int i)
{
    return M[i];
}

template<class T>
int Matrix<T>:: getRow()
{
    return row;
}

template<class T>
int Matrix<T>:: getCol()
{
    return col;
}

template<class T>
void Matrix<T>:: print()
{
    for(int i=0; i<this->row; i++)
    {
        for(int j=0; j<this->col; j++)
        {
            // cout.precision(4);
            // cout<<fixed;
            cout<<this->M[i][j]<<" ";
        }
        cout<<endl;
    }
}

////**************************  class Matrix member functions  *********************//

template<class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> A)
{
    Matrix<T> P(row,col);
    if (row != A.row || col != A.col)
    {
        cout << "Invalid\n";
        exit(0);
    }
    else
    {
        P = Matrix<T>(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                P.M[i][j] = M[i][j] + A.M[i][j];
        return P;
    }
}

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> A)
{
    Matrix<T> P(row,col);
    if (row != A.row || col != A.col)
    {
        cout << "Invalid\n";
        exit(0);
    }
    else
    {
        P = Matrix<T>(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                P.M[i][j] = M[i][j] - A.M[i][j];
        return P;
    }
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> A)
{
    Matrix<T> P;
    if (col != A.row)
    {
        cout << "Invalid\n";
        exit(0);
    }
    else
    {
        P = Matrix<T>(row, A.col);
        T zero = 0;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < A.col; j++)
            {
                P.M[i][j] = zero;
                for (int k = 0; k < col; k++)
                    P.M[i][j] = P.M[i][j] + M[i][k] * A.M[k][j];
            }
        return P;
    }
}

template<class T>
Matrix<T> Matrix<T>::operator+(double a)
{
    Matrix<T> P(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            P.M[i][j] = M[i][j] + a;
    return P;
}

template<class T>
Matrix<T> Matrix<T>::operator-(double a)
{
    Matrix<T> P(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            P.M[i][j] = M[i][j] - a;
    return P;
}

template<class T>
Matrix<T> Matrix<T>::operator*(double a)
{
    Matrix<T> P(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            P.M[i][j] = M[i][j] * a;
    return P;
}

template<class T>
Matrix<T> operator+(double a, Matrix<T> A)
{
    Matrix<T> P(A.row, A.col);
    for (int i = 0; i < A.row; i++)
        for (int j = 0; j < A.col; j++)
            P.M[i][j] = a + A.M[i][j];
    return P;
}

template<class T>
Matrix<T> operator-(double a, Matrix<T> A)
{
    Matrix<T> P(A.row, A.col);
    for (int i = 0; i < A.row; i++)
        for (int j = 0; j < A.col; j++)
            P.M[i][j] = a - A.M[i][j];
    return P;
}

template<class T>
Matrix<T> operator*(double a, Matrix<T> A)
{
    Matrix<T> P(A.row, A.col);
    for (int i = 0; i < A.row; i++)
        for (int j = 0; j < A.col; j++)
            P.M[i][j] = a * A.M[i][j];
    return P;
}

template<class T>
ostream &operator<<(ostream &out, Matrix<T> &Mat){
    for(int i=0; i<Mat.row; i++){
        for(int j=0; j<Mat.col; j++){
            out<<Mat.M[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}

template<class T>
istream &operator>>(istream &in, Matrix<T> &Mat){
    // cout<<"We are in &in function"<<endl;
    for(int i=0; i<Mat.row; i++){
        for(int j=0; j<Mat.col; j++){
            // cout<<"Enter Mat.M["<<i<<"]"<<"["<<j<<"]"<<endl;
            in>>Mat.M[i][j];
        }
    }
    return in;
}





