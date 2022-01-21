#pragma once
#include <bits/stdc++.h>
#include "AD.h"
using namespace std;

#define max 500

class stringList;

template <class T1>
class Tstack
{
private:
    T1 arr[2 * max];
    int size;
    int top;
    friend class stringList;

public:
    Tstack<T1>();
    void push(T1);
    T1 pop();
    int getSize();
    T1 getE(int);
    T1 getTopElement();
};

template <class T1>
Tstack<T1>::Tstack()
{
    size = 0;
    top = -1;
}

class stringList
{
private:
    string elements[2 * max];
    int size;
    int maxSize;

public:
    //function prototyping of constructors in stringList
    stringList();
    int OperatorPriority(char);
    int OperatorPriority(string);
    bool IsOperator(char);
    bool IsOperator(string);
    bool IsNumber(char);
    bool IsNumber(string);
    bool IsFunction(char);
    bool IsFunction(string);
    void setE(int, string);
    void deleteE(int);
    string getE(int);
    int getsize();
    stringList infix_to_postfix(string, string *, int);
    AD evaluate(AD*, string*, int, int);
    void display();
};

//define constructor function of stringList here

stringList::stringList()
{
    maxSize = 2 * max;
    size = 0;
}

// define other classes

class mystack
{
private:
    int maxCapacity = 1000;
    int top = -1;

public:
    //function prototyping of constructor of mystack
    mystack();
    //function prototyping member functions of mystack
    bool isEmpty();
    bool isFull();
    int getCurrentSize();
    void incrementTop();
    void decrementTop();
    int getTop();
};

//define the constructor of mystack here

mystack::mystack()
{
    int i = 0;
}

//defining derived class stringStack
class stringStack : public mystack
{
private:
    stringList clist;

public:
    stringStack();
    void push(string);
    string pop();
    int getSize();
    void setE(int, string);
    string getE(int);
    string getTopElement();
    stringList getclist();
};

//define constructor  of stringStack here
stringStack::stringStack()
{
}

// int main()
// {
//     // AD x(3,0,3), y(8,1,3), z(-1,2,3), two(2,0,3,0);
//     // cout<<x<<" "<<endl;
//     // cout<<y<<" "<<endl;
//     // cout<<z<<" "<<endl;
//     // x.setIndVar();
//     // y.setIndVar();
//     // z.setIndVar();
//     // two.setIndVar();
//     // varCount--;
//     // AD f,g,h;
//     // f = x*y*z+sin(x*y)*two+x*y*cos(z);
//     // g = x*x+y*y+z*z+x*y*z;
//     // h = x*y+y*z+z*x;
//     // cout<<f<<" "<<endl;
//     // cout<<g<<" "<<endl;
//     // cout<<h<<" "<<endl;
//     // AD funArray[] = {f,g,h};
//     // cout<<"Gradient of f is: ";
//     // vector<double> vec2 = f.getGradient();
//     // cout<<vec2<<endl;
//     // for(int i=0; i<vec2.size(); i++)
//     // {
//     //     cout<<vec2[i]<<" ";
//     // }
//     // cout<<endl;
//     // matrix J = getJacobian(funArray,3);
//     // cout<<"Jacobian matrix:\n"<<endl;
//     // J.print();
//     // cout<<endl;

//     int no_of_var;
//     // cout << "Enter no of variables " << endl;
//     cin >> no_of_var;
//     string var_names[no_of_var];
//     double var_values[no_of_var];
//     string expressions[no_of_var];
//     // cout << "Enter names of the variables " << endl;
//     for (int i = 0; i < no_of_var; i++)
//     {
//         cin >> var_names[i];
//     }
//     // cout << "Enter values of variables " << endl;
//     for(int i=0; i<no_of_var; i++)
//     {
//         cin>>var_values[i];
//     }
//     // cout << "Enter the expressions " << endl;
//     for (int i = 0; i < no_of_var; i++)
//     {
//         cin >> expressions[i];
//     }
//     AD variables[no_of_var];
//     for(int i=0; i<no_of_var; i++)
//     {
//         AD temp(var_values[i],i,no_of_var);
//         variables[i] = temp;
//     }

//     AD sol_vars[no_of_var];
//     // cout<<"going in for loop"<<endl;
//     // cout<<"1 varCount ="<<varCount<<endl;
//     for (int i = 0; i < no_of_var; i++)
//     {
//         stringList infix;
//         stringList postfix = infix.infix_to_postfix(expressions[i], &var_names[0], no_of_var);
//         // cout<<"_________________________________"<<endl;
//         // infix.display();
//         // postfix.display();
//         sol_vars[i] = postfix.evaluate(&variables[0], &var_names[0], no_of_var );
//         // cout<<"varCount ="<<varCount<<endl;
//         // sol_vars[i].print();
//     }

//     matrix J = getJacobian(&sol_vars[0],no_of_var);
//     // cout<<"Jacobian matrix:\n"<<endl;
//     J.print();
//     // cout<<endl;

//     return 0;
// }

//########################### class mystack: Function Definitons ##################################

// code here for mystack

template <class T1>
void Tstack<T1>::push(T1 val)
{
    top++;
    size++;
    arr[top] = val;
}

template <class T1>
T1 Tstack<T1>::pop()
{
    top--;
    size--;
    return arr[size];
}

template <class T1>
int Tstack<T1>::getSize()
{
    return size;
}

template <class T1>
T1 Tstack<T1>::getE(int i)
{
    return arr[i];
}

template <class T1>
T1 Tstack<T1>::getTopElement()
{
    return arr[top];
}

//########################### class stringList: Function Definitons ##################################

// A = sin
// B = cos
// C = tan
// D = cosec
// E = sec
// F = cot
// G = arcsin
// H = arccos
// I = arctan
// J = sinh
// K = cosh
// L = tanh
// M = log
// N = exp
// O = abs

// code here for stringList

stringList stringList::infix_to_postfix(string myelements, string *var_names, int no_of_var)
{
    stringStack postfix, temp;
    // string myelements;
    // cout<<"Enter the expression"<<endl;
    // cin >> myelements;
    int len = myelements.size();

    for (int i = 0; i < len; i++)
    {
        bool checknum = IsNumber(myelements[i]);
        bool checkopr = (IsOperator(myelements[i + 1]) || myelements[i + 1] == '(' || myelements[i + 1] == ')');
        bool checkfun = IsFunction(myelements[i]);
        bool found_var = false;
        int var_index = 0;
        for (var_index = 0; var_index < no_of_var; var_index++)
        {
            for (int k = 0; k < var_names[var_index].size(); k++)
            {
                if (myelements[i + k] != var_names[var_index][k])
                {
                    break;
                }
                if (k == (var_names[var_index].size() - 1) && (IsOperator(myelements[i + k + 1]) || myelements[i + k + 1] == '(' || myelements[i + k + 1] == ')' || (i + k) == (len - 1)))
                {
                    found_var = true;
                }
            }
            if (found_var)
            {
                break;
            }
        }
        if (found_var)
        {
            string str1 = var_names[var_index];
            setE(size, str1);
            i = i + var_names[var_index].size() - 1;
            continue;
        }
        else if (checknum)
        {
            string num = "";
            for (; ((IsNumber(myelements[i]) || myelements[i] == '.') && i < len); i++)
            {
                num.push_back(myelements[i]);
            }
            i--;
            setE(size, num);
        }
        // if (checknum && checkopr && i < (len - 1))
        // {
        //     setE(size, myelements[i]);
        //     setE(size, '$');
        // }
        // else if (checknum && i == (len - 1))
        // {
        //     setE(size, myelements[i]);
        //     setE(size, '$');
        // }
        else if (checkfun)
        {
            if (myelements[i] == 'a' && myelements[i + 1] == 'r' && myelements[i + 2] == 'c')
            {
                if (myelements[i + 3] == 's' && myelements[i + 4] == 'i' && myelements[i + 5] == 'n')
                {
                    setE(size, "arcsin");
                    i += 5;
                }
                else if (myelements[i + 3] == 'c' && myelements[i + 4] == 'o' && myelements[i + 5] == 's')
                {
                    setE(size, "arccos");
                    i += 5;
                }
                else if (myelements[i + 3] == 't' && myelements[i + 4] == 'a' && myelements[i + 5] == 'n')
                {
                    setE(size, "arctan");
                    i += 5;
                }
            }
            else if (myelements[i] == 's' && myelements[i + 1] == 'i' && myelements[i + 2] == 'n')
            {
                if (myelements[i + 3] == 'h')
                {
                    setE(size, "sinh");
                    i += 3;
                }
                else
                {
                    setE(size, "sin");
                    i += 2;
                }
            }
            else if (myelements[i] == 'c' && myelements[i + 1] == 'o' && myelements[i + 2] == 's')
            {
                if (myelements[i + 3] == 'e' && myelements[i + 4] == 'c')
                {
                    setE(size, "cosec");
                    i += 4;
                }
                else if (myelements[i + 3] == 'h')
                {
                    setE(size, "cosh");
                    i += 3;
                }
                else
                {
                    setE(size, "cos");
                    i += 2;
                }
            }
            else if (myelements[i] == 't' && myelements[i + 1] == 'a' && myelements[i + 2] == 'n')
            {
                if (myelements[i + 3] == 'h')
                {
                    setE(size, "tanh");
                    i += 3;
                }
                else
                {
                    setE(size, "tan");
                    i += 2;
                }
            }
            else if (myelements[i] == 's' && myelements[i + 1] == 'e' && myelements[i + 2] == 'c')
            {
                setE(size, "sec");
                i += 2;
            }
            else if (myelements[i] == 'c' && myelements[i + 1] == 'o' && myelements[i + 2] == 't')
            {
                setE(size, "cot");
                i += 2;
            }
            else if (myelements[i] == 'l' && myelements[i + 1] == 'o' && myelements[i + 2] == 'g')
            {
                setE(size, "log");
                i += 2;
            }
            else if (myelements[i] == 'e' && myelements[i + 1] == 'x' && myelements[i + 2] == 'p')
            {
                setE(size, "exp");
                i += 2;
            }
            else if (myelements[i] == 'a' && myelements[i + 1] == 'b' && myelements[i + 2] == 's')
            {
                setE(size, "abs");
                i += 2;
            }
        }
        else
        {
            string str = "";
            str.push_back(myelements[i]);
            setE(size, str);
        }
    }
    for (int i = 0; i < getsize(); i++)
    {
        // cout<<" elements["<<i<<"]="<<elements[i]<<endl;
        // if (!(IsOperator(elements[i])) && elements[i] != '(' && elements[i] != ')')
        if (!IsOperator(elements[i]) && !IsFunction(elements[i]) && elements[i] != "(" && elements[i] != ")")
        {
            postfix.push(elements[i]);
        }
        else if (elements[i] == "(" || IsFunction(elements[i]))
        {
            temp.push(elements[i]);
        }
        else if (elements[i] == ")")
        {
            while (temp.getTopElement() != "(" && !(temp.isEmpty()))
            {
                string op = temp.pop();
                postfix.push(op);
            }
            if (temp.getTopElement() == "(")
            {
                string op = temp.pop();
            }
            if (IsFunction(temp.getTopElement()))
            {
                string op = temp.pop();
                postfix.push(op);
            }
        }
        else
        {
            if (temp.isEmpty())
            {
                temp.push(elements[i]);
            }
            else
            {
                if (elements[i] == "^")
                {
                    if (temp.getTopElement() == "^")
                    {
                        temp.push(elements[i]);
                    }
                    else
                    {
                        temp.push(elements[i]);
                    }
                }
                else
                {
                    if (OperatorPriority(elements[i]) <= OperatorPriority(temp.getTopElement()))
                    {
                        while (OperatorPriority(elements[i]) <= OperatorPriority(temp.getTopElement()) && temp.getTopElement() != "(")
                        {
                            string op = temp.pop();
                            postfix.push(op);
                        }
                    }
                    temp.push(elements[i]);
                }
            }
        }
    }
    while (!(temp.isEmpty()))
    {
        string op = temp.pop();
        postfix.push(op);
    }
    return (postfix.getclist());
}

int stringList::OperatorPriority(char c)
{
    string str = "";
    str.push_back(c);
    return OperatorPriority(str);
}

int stringList::OperatorPriority(string c)
{
    if (c == "+" || c == "-")
    {
        return 1;
    }
    else if (c == "*" || c == "/")
    {
        return 2;
    }
    else if (c == "^")
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

bool stringList::IsFunction(string str)
{
    if (str == "sin" || str == "cos" || str == "tan" || str == "sec" || str == "cosec" || str == "cot")
    {
        return true;
    }
    else if (str == "arcsin" || str == "arccos" || str == "arctan")
    {
        return true;
    }
    else if (str == "sinh" || str == "cosh" || str == "tanh")
    {
        return true;
    }
    else if (str == "log" || str == "exp" || str == "abs")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool stringList::IsFunction(char c)
{
    if (c == 's' || c == 'c' || c == 't' || c == 'a' || c == 'l' || c == 'e')
    {
        return true;
    }
    // else if('A'<=c && c<='O'){
    //     return true;
    // }
    else
    {
        return false;
    }
}

bool stringList::IsOperator(char c)
{
    string str = "";
    str.push_back(c);
    return IsOperator(str);
}

bool stringList::IsOperator(string c)
{
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool stringList::IsNumber(char c)
{
    int zero = '0';
    int digit = c - zero;
    if (0 <= digit && digit <= 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool stringList::IsNumber(string str)
{
    int decimal = 0;
    for (int ind = 0; ind < str.size(); ind++)
    {
        if (!IsNumber(str[ind]))
        {
            if(str[ind]=='.' &&  decimal==0)
            {
                decimal++;
                continue;
            }
            return false;
        }
    }
    return true;
}

void stringList::setE(int i, string c)
{
    if (i > (size - 1))
    {
        if (i == size)
        {
            elements[i] = c;
            size++;
        }
    }
    else
    {
        elements[i] = c;
    }
}

void stringList::deleteE(int i)
{
    if (0 <= i && i < size)
    {
        for (int j = (i + 1); j < size; j++)
        {
            elements[j - 1] = elements[j];
        }
        size--;
    }
    else
    {
        cout << "index of deletion is more than size" << endl;
    }
}

string stringList::getE(int i)
{
    return elements[i];
}

int stringList::getsize()
{
    return size;
}

AD stringList::evaluate(AD *variables, string *vars, int vars_size, int var_count)
{
    Tstack<AD> myADs;
    int length = getsize();
    for (int i = 0; i < length; i++)
    {
        // cout<<"elements["<<i<<"]="<<elements[i]<<" , pf: ";
        // this->display();
        // cout<<endl;
        // int prt=myADs.top;
        // cout<<"Stack : "<<endl;
        // for(;prt>=0;prt--)
        // {
        //     myADs.getE(prt).print();
        // }
        bool isVar = false;
        for (int i1 = 0; i1 < vars_size; i1++)
        {
            if (vars[i1] == elements[i])
            {
                myADs.push(variables[i1]);
                isVar = true;
                break;
            }
        }
        if (isVar)
        {
            continue;
        }
        else if (IsNumber(elements[i]))
        {
            double sum1 = stod(elements[i]);
            // int decimal = 0;
            // int zero = '0';
            // double sum1 = 0;
            // for (int j = 0; j < elements[i].size(); j++)
            // {
            //     if (elements[i][j]!='.' )
            //     {
            //         if (decimal == 0)
            //         {
            //             sum1 = sum1 * 10 + (elements[i][j] - zero);
            //         }
            //         else if (decimal >= 1)
            //         {
            //             sum1 = sum1 + (elements[i][j] - zero) * pow(10, -decimal);
            //             decimal++;
            //         }
            //     }
            //     else if (elements[i][j] == '.')
            //     {
            //         decimal++;
            //     }
            // }
            // // cout<<sum1<<endl;
            AD temp1(sum1,0, var_count,0);
            myADs.push(temp1);
        }
        else if (IsOperator(elements[i]))
        {
            AD var1 = myADs.pop();
            AD var2;
            if (myADs.top != -1)
            {
                AD m = myADs.pop();
                var2 = m;
            }
            else
            {
                AD m(0,0, var_count,0);
                var2 = m;
            }

            if (elements[i] == "+")
            {
                myADs.push(var2 + var1);
            }
            else if (elements[i] == "-")
            {
                myADs.push(var2 - var1);
            }
            else if (elements[i] == "*")
            {
                myADs.push(var2 * var1);
            }
            else if (elements[i] == "/")
            {
                myADs.push(var2 / var1);
            }
            else if (elements[i] == "^")
            {
                myADs.push(var2 ^ var1);
            }
            continue;
        }
        else if (IsFunction(elements[i]))
        {
            AD var = myADs.pop();
            if (elements[i] == "sin")
            {
                myADs.push(sin(var));
            }
            else if (elements[i] == "cos")
            {
                myADs.push(cos(var));
            }
            else if (elements[i] == "tan")
            {
                myADs.push(tan(var));
            }
            else if (elements[i] == "cosec")
            {
                myADs.push(cosec(var));
            }
            else if (elements[i] == "sec")
            {
                myADs.push(sec(var));
            }
            else if (elements[i] == "cot")
            {
                myADs.push(cot(var));
            }
            else if (elements[i] == "arcsin")
            {
                myADs.push(arcsin(var));
            }
            else if (elements[i] == "arccos")
            {
                myADs.push(arccos(var));
            }
            else if (elements[i] == "arctan")
            {
                myADs.push(arctan(var));
            }
            else if (elements[i] == "sinh")
            {
                myADs.push(sinh(var));
            }
            else if (elements[i] == "cosh")
            {
                myADs.push(cosh(var));
            }
            else if (elements[i] == "tanh")
            {
                myADs.push(tanh(var));
            }
            else if (elements[i] == "log")
            {
                myADs.push(log(var));
            }
            else if (elements[i] == "exp")
            {
                myADs.push(exp(var));
            }
            else if (elements[i] == "abs")
            {
                myADs.push(abs(var));
            }
            continue;
        }
    }
    AD sol_value = myADs.pop();
    return sol_value;
}

void stringList::display()
{
    int length = getsize();
    for (int i = 0; i < length; i++)
    {
        // if (elements[i] != '$')
        {
            cout << elements[i];
        }
    }
    cout << endl;
}

//########################### class mystack: Function Definitons ##################################

// code here for mystack

bool mystack::isEmpty()
{
    if ((top + 1) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool mystack::isFull()
{
    if ((top + 1) == maxCapacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int mystack::getCurrentSize()
{
    return (top + 1);
}

void mystack::incrementTop()
{
    top++;
}

void mystack::decrementTop()
{
    top--;
}

int mystack::getTop()
{
    return top;
}

//########################### class stringStack: Function Definitons ##################################

// code here for stringStack

void stringStack ::push(string c)
{
    incrementTop();
    clist.setE((getTop()), c);
}

string stringStack ::pop()
{
    int t = getTop();
    string TopElem = clist.getE(t);
    clist.deleteE(t);
    decrementTop();
    return TopElem;
}

int stringStack::getSize()
{
    return (clist.getsize());
}

void stringStack::setE(int i, string c)
{
    clist.setE(i, c);
}

string stringStack::getE(int i)
{
    return (clist.getE(i));
}

string stringStack ::getTopElement()
{
    int t = getTop();
    string TopElem = clist.getE(t);
    return TopElem;
}

stringList stringStack ::getclist()
{
    return clist;
}




