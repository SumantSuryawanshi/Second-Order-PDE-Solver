#pragma once
// #include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include "Matrix.h"
using namespace std;


class AD;

class AD
{
private:
	double f;
	vector<double> df;
    int id;
	friend ostream &operator<<(ostream &, AD &);
	friend istream &operator>>(istream &, AD &);
public:
	// Constructor functions
    AD();
	AD(int);
	AD(double,int,int);
    AD(double,int,int,double);
    void setIndVar(int);
	// Access functions
	double get_f();
    void set_f(double);
	double get_Df(int);
    vector<double> getGradient();
    friend Matrix<double> getJacobian(AD*,int);
	// (f,g) functions
	AD operator+(AD); // f + g
	AD operator-(AD); // f - g
	AD operator*(AD); // f * g
	AD operator/(AD); // f / g
	AD operator^(AD); // f^g
	void print();
	// sin(f), cos(f), tan(f), cosec(f), sec(f), cot(f).
	// arcsin(f), arccos(f), arctan(f), sinh(f), cosh(f), tanh(f).
	// log(f), exp(f), abs(f)
	friend AD sin(AD);
	friend AD cos(AD);
	friend AD tan(AD);
	friend AD cosec(AD);
	friend AD sec(AD);
	friend AD cot(AD);
	friend AD arcsin(AD);
	friend AD arccos(AD);
	friend AD arctan(AD);
	friend AD sinh(AD);
	friend AD cosh(AD);
	friend AD tanh(AD);
	friend AD log(AD);
	friend AD exp(AD);
	friend AD abs(AD);
};

/////*******************  Constructor Functions *********************************////

AD::AD()
{
    this->f = 0;
}

AD::AD(int iden)
{
	this->f = 0;
    this->id = iden;
}

AD::AD(double x, int iden, int n)
{
	this->f = x;
	this->id = iden;
    this->df = vector<double>(n);
    for(int i=0; i<this->id; i++)
    {
        this->df[i] = 0;
    }
    this->df[this->id] = 1;
    for(int i=this->id+1; i<n; i++)
    {
        this->df[i] = 0;
    }
}

AD::AD(double x, int iden, int n, double dx)
{
	this->f = x;
	this->id = iden;
    this->df = vector<double>(n);
    for(int i=0; i<this->id; i++)
    {
        this->df[i] = 0;
    }
    this->df[this->id] = dx;
    for(int i=this->id+1; i<n; i++)
    {
        this->df[i] = 0;
    }
}

// AD::AD(double x, double dx)
// {
// 	this->f = x;
//     this->id = varCount;
// 	for(int i=0; i<this->id; i++)
//     {
//         df[i] = 0;
//     }
//     df[this->id] = dx;
//     varCount++;
// }

ostream &operator<<(ostream &out, AD &N)
{
    out << N.f;
    return out;
}

istream &operator>>(istream &in, AD &N)
{
    in >> N.f;
    return in;
}

void AD::print()
{
	cout << " f : "<< this->f<<endl;
	// cout << " df : "<< this->df <<endl;
    // cout<<this->df<<endl;
    cout<<" df : ";
    for(int i=0; i<df.size(); i++)
    {
        cout<<df[i]<<" ";
    }
    cout<<endl;
}

void AD:: setIndVar(int n)
{
    this->df = vector<double>(n);
    for(int i=0; i<this->id; i++)
    {
        this->df[i] = 0;
    }
    this->df[this->id] = 1;
    for(int i=this->id+1; i<n; i++)
    {
        this->df[i] = 0;
    }
}
// Access functions
double AD:: get_f()
{
    return this->f;
}

void AD:: set_f(double value)
{
    this->f = value;
}

double AD:: get_Df(int i)
{
    return this->df[i];
}

vector<double> AD:: getGradient()
{
    int n = this->df.size();
    vector<double> gradient(n);
    for(int i =0 ; i<n; i++)
    {
        gradient[i] = this->df[i];
    }
    return gradient;
}

Matrix<double> getJacobian(AD* funList, int n)
{
    Matrix<double> Mat(n,n);
    for(int i=0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            Mat(i, j, funList[i].get_Df(j));
        }
    }
    return Mat;
}


/////*******************  (f,g) Functions  *************************/////

 //  f+g //
AD AD::operator+(AD g)
{
	AD h;
	h.f = this->f + g.f;
    h.df = vector<double>((this->df.size()));
    for(int i=0; i<(this->df.size()); i++)
	    h.df[i] = this->df[i] + g.df[i];
	return h;
}
 //  f-g //
AD AD::operator-(AD g)
{
	AD h;
	h.f = this->f - g.f;
    h.df = vector<double>((this->df.size()));
    for(int i=0; i<(this->df.size()); i++)
	    h.df[i] = this->df[i] - g.df[i];
	return h;
}
 //  f*g //
AD AD::operator*(AD g)
{
	AD h;
	h.f = this->f * g.f;
    h.df = vector<double>((this->df.size()));
    for(int i=0; i<(this->df.size()); i++)
	    h.df[i] = this->f * g.df[i] + g.f * this->df[i];
	return h;
}
 //  f/g  //
AD AD::operator/(AD g)
{
	AD h;
	h.f = (this->f) / g.f;
    h.df = vector<double>((this->df.size()));
    for(int i=0; i<(this->df.size()); i++)
	    h.df[i] = (this->df[i] * g.f - g.df[i] * this->f) / (g.f * g.f);
	return h;
}
 //   f^g  //
AD AD::operator^(AD g)
{
	AD h;
	h.f = pow((this->f), (g.f));
    h.df = vector<double>((this->df.size()));
    for(int i=0; i<(this->df.size()); i++)
	    h.df[i] = (pow(this->f, g.f) * log(abs(this->f)) * g.df[i] + pow(this->f, g.f) * (g.f / this->f) * this->df[i]);
	    // h.df[i] = (u^v)           *  log( |u| )      *  v'  + (u^v)             * (v/u)           * (u')
	return h;
}


//////****************  more complex friend functions  **********//////

AD sin(AD g){
	AD h;
	h.f = sin(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (g.df[i])*cos(g.f);
	return h;
}

AD cos(AD g){
	AD h;
	h.f = cos(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (g.df[i])*(-1)*(sin(g.f));
	return h;
}

AD tan(AD g){
	AD h;
	h.f = tan(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (1/cos(g.f)) * (1/cos(g.f)) * (g.df[i]) ;
	return h;
}

AD cosec(AD g){
	AD h;
	h.f = 1/sin(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = -(1/tan(g.f)) * (1/sin(g.f)) * (g.df[i]);
	return h;
}

AD sec(AD g){
	AD h;
	h.f = 1/cos(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = tan(g.f)/cos(g.f) * (g.df[i]);
	return h;
}

AD cot(AD g){
	AD h;
	h.f = 1/tan(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = -1/sin(g.f)/sin(g.f)*(g.df[i]);
	return h;
}

AD arcsin(AD g){
	AD h;
	h.f = asin(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = pow((1-g.f*g.f),(-0.5))*(g.df[i]);
	return h;
}

AD arccos(AD g){
	AD h;
	h.f = acos(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (-1)*pow((1-g.f*g.f),(-0.5))*(g.df[i]);
	return h;
}

AD arctan(AD g){
	AD h;
	h.f = atan(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (1/(1+g.f*g.f))*(g.df[i]);
	return h;
}

AD sinh(AD g){
	AD h;
	h.f = sinh(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = cosh(g.f)*(g.df[i]);
	return h;
}

AD cosh(AD g){
	AD h;
	h.f = cosh(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = sinh(g.f)*(g.df[i]);
	return h;
}

AD tanh(AD g){
	AD h;
	h.f = tanh(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = 1/cosh(g.f)*1/cosh(g.f)*(g.df[i]);
	return h;
}

AD log(AD g){
	AD h;
	h.f = log(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = (1/g.f)*(g.df[i]);
	return h;
}

AD exp(AD g){
	AD h;
	h.f = exp(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = exp(g.f)*(g.df[i]);
	return h;
}

AD abs(AD g){
	AD h;
	h.f = abs(g.f);
    h.df = vector<double>((g.df.size()));
    for(int i=0; i<(g.df.size()); i++)
	    h.df[i] = g.f/abs(g.f)*(g.df[i]);
	return h;
}






