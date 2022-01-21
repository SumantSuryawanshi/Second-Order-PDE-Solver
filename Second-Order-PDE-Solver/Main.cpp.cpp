#include <fstream>
#include <iomanip>
#include "NonLinearSolver.h"
using namespace std;

int main()
{
    vector<string> coeff(5);
    vector<string> bound_condi(4);
    vector<double> region(4);
    int divix, diviy;
    cout << "Enter the values of A, B, C, D, E" << endl;
    cin >> coeff[0] >> coeff[1] >> coeff[2] >> coeff[3] >> coeff[4];
    cout << "Enter the values of a,b,c,d " << endl;
    cin >> region[0] >> region[1] >> region[2] >> region[3];
    cout << "Enter the values of f1(y), f2(y), g1(x), g2(x) " << endl;
    cin >> bound_condi[0] >> bound_condi[1] >> bound_condi[2] >> bound_condi[3];
    cout << "Enter the values of m & n" << endl;
    cin >> divix >> diviy;

    int NonLinearindex;
    cout<<"Available Methods to solve Non Linear Equations"<<endl;
    cout<<" 1.Newtons Method"<<endl;
    cout<<" 2.Broydens Method"<<endl;
    cout << "Enter method no. of Non Linear Solver : ";
    cin>>NonLinearindex;

    int Linearindex;
    cout<<"Available methods of solve Linear Equations:"<<endl;
    cout<<"    1. Guass Elimination Method"<<endl;
    cout<<"    2. LU Decomposition Method"<<endl;
    cout<<"    3. Tridiagonal Method"<<endl;
    cout<<"    4. Guass Jacobi Method"<<endl;
    cout<<"    5. Guass Seidal Method"<<endl;
    cout<<"    6. Successive Over Relaxation Method"<<endl;
    cout << "Enter method no. of Linear Solver : ";
    cin >> Linearindex;

    Discretize equ1(coeff, region, bound_condi, divix, diviy);
    
    equ1.CreateDiscretePoints();

    

    equ1 = NonLinearMethod(equ1, Linearindex, NonLinearindex );

    cout << "Surface of U will be " << endl;
    for (int i = 0; i <= divix; i++)
    {
        for (int j = 0; j <= diviy; j++)
        {
            cout<<equ1.get_U(i, j).get_f()<<" ";
        }
        cout << endl;
    }

    // ofstream myFile;
    // myFile.open("BroydenQ1_plot.csv");

    // for (int i = 0; i <= divix; i++)
    // {
    //     for (int j = 0; j <= diviy; j++)
    //     {
    //         myFile << equ1.get_Point(i, j).x_coordinate << "," << equ1.get_Point(i, j).y_coordinate << "," << equ1.get_U(i,j).get_f() << endl;
    //     }
    // }
    // myFile.close();

    return 0;
}



