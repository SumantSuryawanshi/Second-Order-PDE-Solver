#pragma once
#include "Matrix.h"
#include <cmath>

// 1) Gauss Elimination Method

template <class T>
vector<T> GaussElimination(Matrix<T> M, vector<T> u)
{
    vector<T> x(u.size());
    T temp;
    int i, j, k;
    for (i = 0; i < u.size(); i++)
    {
        temp = fabs(M(i, i));
        k = i;
        for (j = i + 1; j < u.size(); j++)
            if (temp < fabs(M(j, i)))
            {
                temp = fabs(M(j, i));
                k = j;
            }
        if (fabs(M(k, i)) < 0.00001)
        {
            cout << "The matrix is singular: The system has either no solution or infinitely many solution";
            exit(0);
        }
        if (k != i)
        {
            for (j = 0; j < u.size(); j++)
            {
                temp = M(k, j);
                M(k, j, M(i, j));
                M(i, j, temp);
            }
            temp = u[k];
            u[k] = u[i];
            u[i] = temp;
        }
        for (j = i + 1; j < u.size(); j++)
        {
            temp = M(j, i) / M(i, i);
            for (k = 0; k < u.size(); k++)
                M(j, k, M(j, k) - temp * M(i, k));
            u[j] = u[j] - temp * u[i];
        }
    }
    x[u.size() - 1] = u[u.size() - 1] / M(u.size() - 1, u.size() - 1);
    for (i = u.size() - 2; i >= 0; i--)
    {
        x[i] = u[i];
        for (j = i + 1; j < u.size(); j++)
            x[i] = x[i] - M(i, j) * x[j];
        x[i] = x[i] / M(i, i);
    }
    return x;
}

// 2) LU Decomposition Method

template <class T>
vector<T> LU_Decomposition(Matrix<T> M, vector<T> u)
{
    Matrix<T> l(u.size()), u1(u.size());
    vector<T> x(u.size());
    vector<T> z(u.size());
    int i, j, k;

    for (i = 0; i < u.size(); i++)
        l(i, 0, M(i, 0));
    for (j = 1; j < u.size(); j++)
        u1(0, j, M(0, j) / l(0, 0));
    for (i = 0; i < u.size(); i++)
        u1(i, i, 1);
    for (i = 1; i < u.size(); i++)
        for (j = 1; j < u.size(); j++)
            if (i >= j)
            {
                l(i, j, M(i, j));
                for (k = 0; k <= j - 1; k++)
                {

                    l(i, j, l(i, j) - l(i, k) * u1(k, j));
                }
            }
            else
            {
                u1(i, j, M(i, j));
                for (k = 0; k <= i - 1; k++)
                    u1(i, j, u1(i, j) - l(i, k) * u1(k, j));
                u1(i, j, u1(i, j) / l(i, i));
            }
    cout << "The lower triangular matrix L:" << endl;
    for (i = 0; i < u.size(); i++)
    {
        for (j = 0; j <= i; j++)
            cout << "\t" << l(i, j);
        cout << endl;
    }
    cout << "\nThe upper triangular matrix U:" << endl;
    for (i = 0; i < u.size(); i++)
    {
        for (j = 0; j < i; j++)
            cout << "\t";
        for (j = i; j < u.size(); j++)
            cout << "\t" << u1(i, j);
        cout << endl;
    }
    z[0] = u[0] / l(0, 0);
    for (i = 1; i < u.size(); i++)
    {
        z[i] = u[i];
        for (j = 0; j <= i - 1; j++)
            z[i] -= l(i, j) * z[j];
        z[i] /= l(i, i);
    }
    x[u.size() - 1] = z[u.size() - 1];
    for (i = u.size() - 2; i >= 0; i--)
    {
        x[i] = z[i];
        for (j = i + 1; j < u.size(); j++)
            x[i] -= u1(i, j) * x[j];
    }
    return x;
}

// 3) TriDiagonal Method

template <class T>
vector<T> TriDiagonal(Matrix<T> M, vector<T> u)
{
    vector<T> x(u.size());
    T A[u.size() - 1], B[u.size()], C[u.size() - 1], D[u.size()];
    T C_star[u.size() - 1], D_star[u.size()];
    int i, j;

    for (i = 0; i < u.size() - 2; i++)
        for (j = i; j < u.size() - 2; j++)
        {
            if (M(i, j + 2) != 0)
            {
                cout << "Method can't be applied";
                exit(0);
            }
        }
    for (i = u.size() - 1; i > 1; i--)
        for (j = i; j > 1; j--)
        {
            if (M(i, j - 2) != 0)
            {
                cout << "Method can't be applied";
                exit(0);
            }
        }
    for (i = 0; i < u.size(); i++)
    {
        B[i] = M(i, i);
        D[i] = u[i];
    }
    for (i = 1; i < u.size(); i++)
    {
        A[i] = M(i, i - 1);
    }
    for (i = 0; i < u.size() - 1; i++)
    {
        C[i] = M(i, i + 1);
    }

    C_star[0] = C[0] / B[0];
    D_star[0] = D[0] / B[0];
    for (i = 1; i < u.size(); i++)
    {
        C_star[i] = C[i] / (B[i] - A[i] * C_star[i - 1]);
        D_star[i] = (D[i] - A[i] * D_star[i - 1]) / (B[i] - A[i] * C_star[i - 1]);
    }
    x[u.size() - 1] = D_star[u.size() - 1];
    for (i = u.size() - 2; i >= 0; i--)
    {
        x[i] = D_star[i] - C_star[i] * x[i + 1];
    }
    return x;
}

// 4) Gauss Jacobi Method

template <class T>
vector<T> Gauss_Jacobi(Matrix<T> M, vector<T> u)
{
    vector<T> x, xn;
    int i, j, flag;
    T sum, eps;

    x = vector<T>(u.size());
    xn = vector<T>(u.size());
    cout << "Enter the accuracy u want\n";
    cin >> eps;
    for (i = 0; i < u.size(); i++)
        x[i] = 0;
    flag = 0;
    for (i = 0; i < u.size(); i++)
    {
        sum = 0;
        for (j = 0; j < u.size(); j++)
            if (i != j)
                sum += fabs(M(i, j));
        if (sum > fabs(M(i, i)))
            flag = 1;
    }
    if (flag == 1)
    {
        flag = 0;
        for (j = 0; j < u.size(); j++)
        {
            sum = 0;
            for (i = 0; i < u.size(); i++)
                if (i != j)
                    sum += fabs(M(i, j));
            if (sum > fabs(M(j, j)))
                flag = 1;
        }
    }
    if (flag == 1)
    {
        cout << "The co-efficient matrix is not diagonally dominant\n";
        cout << "The Gauss-Jacobi method doesn't converge surely\n";
        exit(0);
    }
    do
    {
        for (i = 0; i < u.size(); i++)
        {
            sum = u[i];
            for (j = 0; j < u.size(); j++)
                if (j != i)
                    sum -= M(i, j) * x[j];
            xn[i] = sum / M(i, i);
        }
        flag = 0;
        for (i = 0; i < u.size(); i++)
            if (fabs(x[i] - xn[i]) > eps)
                flag = 1;
        if (flag == 1)
            for (i = 0; i < u.size(); i++)
                x[i] = xn[i];
    } while (flag == 1);
    return xn;
}

// 5) Gauss Seidal Method

template <class T>
vector<T> Gauss_Seidal(Matrix<T> M, vector<T> u)
{
    vector<T> x, xn;
    int test, i, j;
    T g, sum, eps = 0.0001;
    //cout<<"SATYA";
    for (i = 0; i < u.size(); i++)
    {
        for (j = 0; j < u.size(); j++)
        {
            cout << M(i, j) << " ";
        }
        cout << "\n";
    }

    x = vector<T>(u.size());
    xn = vector<T>(u.size());
    for (i = 0; i < u.size(); i++)
    {
        x[i] = 0;
    }

    for (i = 0; i < u.size(); i++)
        x[i] = 0;

    test = 0;
    for (i = 0; i < u.size(); i++)
    {
        sum = 0;
        for (j = 0; j < u.size(); j++)
            if (i != j)
                sum += fabs(M(i, j));
        if (sum > fabs(M(i, i)))
            test = 1;
    }
    // Diagonally dominance verification by columns.
    if (test == 1)
    {
        test = 0;
        for (j = 0; j < u.size(); j++)
        {
            sum = 0;
            for (i = 0; i < u.size(); i++)
                if (i != j)
                    sum += fabs(M(i, j));
            if (sum > fabs(M(j, j)))
                test = 1;
        }
    }

    if (test == 1)
    {
        cout << "The co-efficient matrix is not diagonally dominant\n";
        cout << "The Gauss-Seidel method doesn't converge surely\n";
        exit(0);
    }
    do
    {
        for (i = 0; i < u.size(); i++)
        {
            sum = u[i];
            for (j = 0; j < u.size(); j++)
            {
                if (j < i)
                    sum -= M(i, j) * xn[j];
                else if (j > i)
                    sum -= M(i, j) * x[j];
            }
            xn[i] = sum / M(i, i);
        }
        test = 0;
        for (i = 0; i < u.size(); i++)
            if (fabs(x[i] - xn[i]) > eps)
                test = 1;
        if (test == 1)
            for (i = 0; i < u.size(); i++)
                x[i] = xn[i];
    } while (test == 1);
    return xn;
}

// 6) Successive Over Relaxation Method

template <class T>
vector<T> SOR(Matrix<T> M, vector<T> u)
{
    vector<T> x, xn;
    int i, j, flag;
    T sum, eps = 0.001, w = 1;

    x = vector<T>(u.size());
    xn = vector<T>(u.size());

    for (i = 0; i < u.size(); i++)
        x[i] = 0;
    do
    {
        for (i = 0; i < u.size(); i++)
        {
            sum = u[i] * w + M(i, i) * x[i];
            for (j = 0; j < u.size(); j++)
            {
                if (j < i)
                    sum -= M(i, j) * xn[j] * w;
                else if (j >= i)
                    sum -= M(i, j) * x[j] * w;
                xn[i] = sum / M(i, i);
            }
        }
        flag = 0;
        for (i = 0; i < u.size(); i++)
            if (fabs(x[i] - xn[i]) > eps)
                flag = 1;
        if (flag == 1)
            for (i = 0; i < u.size(); i++)
                x[i] = xn[i];
    } while (flag == 1);
    return xn;
}







