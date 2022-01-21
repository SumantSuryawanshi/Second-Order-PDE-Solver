#pragma once
#include "Discretizer.h"
#include "AD.h"
#include "Matrix.h"
#include "LinearSolver2.h"

Discretize NewtonsMethod(Discretize &, int );
Discretize BroydensMethod(Discretize &, int );




Discretize  NonLinearMethod(Discretize &D1, int LinearMethod, int i)
{
    if(i==1)
    {
        D1 = NewtonsMethod(D1, LinearMethod);
        return D1;
    }
    else
    {
        D1 = BroydensMethod(D1, LinearMethod);
        return D1;
    }
}

bool ContinueIterations(vector<double> &Y, double epsilon)
{
    double sum_of_sqrs = 0;
    for (int i = 0; i < Y.size(); i++)
    {
        // cout<<"in cost loop i="<<i<<" & sum_of_sqrs = "<<sum_of_sqrs<<endl;
        sum_of_sqrs = sum_of_sqrs + Y[i]*Y[i];
    }
    double cost = pow(sum_of_sqrs,0.5);
    if (cost <= epsilon)
    {
        cout << "cost = " << cost << endl;
        return false;
    }
    else
    {
        return true;
    }
}

Discretize NewtonsMethod(Discretize &D1, int LinearMethod)
{
    cout<<"Inside Newtons Method"<<endl;
    double epsilon = 0.00001;

    vector<double> (*Linear_Solver)(Matrix<double>, vector<double>);
    if (LinearMethod == 1)
    {
        Linear_Solver = &GaussElimination;
    }
    else if (LinearMethod == 2)
    {
        Linear_Solver = &LU_Decomposition;
    }
    else if (LinearMethod == 3)
    {
        Linear_Solver = &TriDiagonal;
    }
    else if (LinearMethod == 4)
    {
        Linear_Solver = &Gauss_Jacobi;
    }
    else if (LinearMethod == 5)
    {
        Linear_Solver = &Gauss_Seidal;
    }
    else if (LinearMethod == 6)
    {
        Linear_Solver = &SOR;
    }

    int no_of_indi_var = D1.variables.size();
    // cout << "We are in NewtonsMethod" << endl;
    AD *Y_AD, *F_AD;
    vector<DiscretePoint> X0(no_of_indi_var);

    F_AD = new AD[no_of_indi_var];
    Matrix<double> J(no_of_indi_var);
    vector<double> F(no_of_indi_var);
    vector<double> Y(no_of_indi_var);

    int itr = 0;
    do
    {
        itr++;
        // cout << "itr = " << itr << endl;
        X0 = D1.variables;
        F_AD = D1.EvaluateEquation(); // F[x0]
        for (int i = 0; i < no_of_indi_var; i++)
        {
            F[i] = F_AD[i].get_f();
        }
        J = getJacobian(F_AD, no_of_indi_var);
        // cout<<"Jacobian at itr="<<itr<<endl;
        // J.print();
        Y = (*Linear_Solver)(J, F);
        for (int i = 0; i < no_of_indi_var; i++)
        {
            // cout<<"Y["<<i<<"] = "<<Y[i]<<endl;
            double x1 = X0[i].Uij.get_f() - Y[i];
            D1.variables[i].Uij.set_f(x1);
            // cout<<"D1.variables[i].Uij.get_f() = "<<D1.variables[i].Uij.get_f()<<endl;
        }
    } while (ContinueIterations(Y, epsilon));
    cout << "No of iterations = " << itr << endl;
    return D1;
}

Matrix<double> getTranspose(Matrix<double> Mat)
{
    int r = Mat.getRow();
    int c = Mat.getCol();
    Matrix<double> TrpsMat(c, r);
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            TrpsMat[i][j] = Mat[j][i];
        }
    }
    return TrpsMat;
}

Matrix<double> getInverse(Matrix<double> Mat, int LinearMethod)
{
    vector<double> (*Linear_Solver)(Matrix<double>, vector<double>);
    
    if (LinearMethod == 1)
    {
        Linear_Solver = &GaussElimination;
    }
    else if (LinearMethod == 2)
    {
        Linear_Solver = &LU_Decomposition;
    }
    else if (LinearMethod == 3)
    {
        Linear_Solver = &TriDiagonal;
    }
    else if (LinearMethod == 4)
    {
        Linear_Solver = &Gauss_Jacobi;
    }
    else if (LinearMethod == 5)
    {
        Linear_Solver = &Gauss_Seidal;
    }
    else if (LinearMethod == 6)
    {
        Linear_Solver = &SOR;
    }


    Matrix<double> InvMat(Mat.getRow(), Mat.getCol());
    vector<vector<double>> Col_vec;
    if (Mat.getRow() == Mat.getCol())
    {
        int n = Mat.getRow();
        for (int i = 0; i < n; i++)
        {
            vector<double> Y(n, 0);
            Y[i] = 1;
            vector<double> X = Linear_Solver(Mat, Y);
            Col_vec.push_back(X);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                InvMat[i][j] = Col_vec[j][i];
            }
        }
    }
    else
    {
        cout << "Inverse of Matrix cannot be computed because it is not a Square Matrix" << endl;
        exit(0);
    }
    return InvMat;
}

Discretize BroydensMethod(Discretize &D1, int LinearMethod)
{
    cout<<"Inside Broydens Method"<<endl;
    double epsilon = 0.00001;

    int no_of_indi_var = D1.variables.size();
    // cout << "We are in NewtonsMethod" << endl;
    AD *AF_AD, *F_AD;
    vector<DiscretePoint> X0(no_of_indi_var);
    vector<DiscretePoint> X1(no_of_indi_var);

    F_AD = new AD[no_of_indi_var];
    Matrix<double> Ainv0(no_of_indi_var, 1);
    Matrix<double> Ainv1(no_of_indi_var, 1);
    Matrix<double> F0_Mat(no_of_indi_var, 1);
    Matrix<double> F1_Mat(no_of_indi_var, 1);
    Matrix<double> AiF(no_of_indi_var, 1);
    vector<double> vec_AiF(no_of_indi_var);
    

    int itr = 0;
    do
    {
        itr++;
        // cout << "itr = " << itr << endl;

        if (itr == 1)
        {
            X1 = D1.variables; // D1.variables = vector<DiscretePoint>
            F_AD = D1.EvaluateEquation();
            for (int i = 0; i < no_of_indi_var; i++)
            {
                F1_Mat(i, 0, F_AD[i].get_f());
            }
            Matrix<double> A1 = getJacobian(F_AD, no_of_indi_var);
            // cout<<"Printing Jacobian "<<endl;
            // A1.print();
            Ainv1 = getInverse(A1,LinearMethod);
            // cout<<"Printing Inverse of Jacobian "<<endl;
            // Ainv1.print();
            AiF = Ainv1 * F1_Mat;
            // cout<<"itr = 1 , Multiplication done"<<endl;
        }
        else
        {
            X0 = X1;
            X1 = D1.variables;
            F0_Mat = F1_Mat;
            Ainv0 = Ainv1;
            // cout<<"F0_Mat = F1_Mat"<<endl;

            F_AD = D1.EvaluateEquation();
            for (int i = 0; i < no_of_indi_var; i++)
            {
                F1_Mat(i, 0, F_AD[i].get_f());
            }

            // cout<<"F1_Mat(i, 0, F_AD->get_f())"<<endl;

            Matrix<double> y1(no_of_indi_var, 1);
            Matrix<double> s1(no_of_indi_var, 1);

            // cout<<"before-> y1 = F1_Mat - F0_Mat;"<<endl;

            y1 = F1_Mat - F0_Mat;

            // cout<<"after-> y1 = F1_Mat - F0_Mat;"<<endl;

            for (int i = 0; i < no_of_indi_var; i++)
            {
                // cout<<"X1-X0 = "<<X1[i].Uij.get_f()<<" - "<<X0[i].Uij.get_f()<<endl;

                double val = X1[i].Uij.get_f() - X0[i].Uij.get_f();
                s1(i, 0, val);
            }

            // cout<<"s1(i, 0, val);"<<endl;

            Matrix<double> s1A0y1_Mat(1,1);
            Matrix<double> s1t(1,no_of_indi_var);
            s1t = getTranspose(s1);
            // cout<<"s1t = ["<<s1t.getRow()<<"]["<<s1t.getCol()<<"]"<<endl;
            // cout<<"s1t = "<<endl;
            // s1t.print();
            // cout<<"Ainv0 = ["<<Ainv0.getRow()<<"]["<<Ainv0.getCol()<<"]"<<endl;
            // cout<<"Ainv0 = "<<endl;
            // Ainv0.print();
            // cout<<"y1 = ["<<y1.getRow()<<"]["<<y1.getCol()<<"]"<<endl;
            // cout<<"y1 = "<<endl;
            // y1.print();
            // cout<<"calculated s1t"<<endl;
            s1A0y1_Mat = (s1t * Ainv0) * y1;
            // cout<<"s1A0y1_Mat = s1 * Ainv0 * y1;"<<endl;
            double s1A0y1 = s1A0y1_Mat(0, 0);

            // cout<<"going for matrix operations"<<endl;

            // Matrix<double> temp1;
            // temp1 = Ainv0*y1;
            // Matrix<double> temp2;
            // temp2 = s1-temp1;

            // cout<<"Printing s1"<<endl;
            // s1.print();
            // cout<<"Printing Ainv0*y1"<<endl;
            // temp1.print();
            // cout<<"Printing (s1 - (Ainv0 * y1))"<<endl;
            // temp2.print();

            Ainv1 = Ainv0 + (1 / s1A0y1) * (((s1 - (Ainv0 * y1)) * getTranspose(s1)) * Ainv0);
            AiF = Ainv1 * F1_Mat;
        }

        for (int i = 0; i < no_of_indi_var; i++)
        {
            // cout<<"x1 - Aif = "<<X1[i].Uij.get_f()<<" - "<<AiF(i,0)<<endl;
            double x1 = X1[i].Uij.get_f() - AiF(i, 0);
            D1.variables[i].Uij.set_f(x1);
        }

        for (int i = 0; i < no_of_indi_var; i++)
        {
            vec_AiF[i] = AiF(i, 0);
        }

    } while (ContinueIterations(vec_AiF, epsilon));
    cout << "No of iterations = " << itr << endl;
    return D1;
}


