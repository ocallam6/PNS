/*
============================================================================
					Practical Numerical Simulations
							Assignment 1
							 Question 1
					Matthew O'Callaghan: 16317515
============================================================================
*/

#include <iostream>
#include<cmath>
#include<iomanip>
#include<fstream> //Create CSV file with all the values for plotting.
//============================================================================
double f(double t, double x);
double runge(int step,double x,double step_size,double t_0,double (*func)(double,double));
double g(double t,double x);
void question1_1();
void question1_2();
//============================================================================

int main()
{
	question1_1();
	question1_2();
	return 0;
}

//============================================================================
//QUESTION 1
//PART 1
//============================================================================

void question1_1()
{

	std::ofstream myfile;

	int step_numbers=2;
	int accuracy=6;
	double precision=(1.0/(pow(10.0,accuracy)));
	std::cout<<"Question1: (i)."<<std::endl;
	double t_1=2.0;
	double t_0=0.0;
	double x=1.0; //initialise x
	double x_test=2.0;
	double dt=t_1-t_0;

	while(fabs((x-x_test)/x)>double(precision))
	{
		double step_size= dt/double(step_numbers);
		x_test=x;
		x=1.0;
		
		myfile.open("q1.csv");
		myfile<<"t,x,\n";
		myfile<<t_0<<",";
		myfile<<x<<",\n";
		
		for(int step=1;step<=step_numbers;step++)
		{
			x=runge(step,x,step_size,t_0,f);
			
			myfile<<t_0+step*step_size<<",";
			myfile<<x<<",\n";
		}
		myfile.close();
		
		std::cout<<"n= "<<step_numbers<<"   x= "<<std::setprecision(6)<<x<<"   xold= "<<std::setprecision(accuracy+4)<<x_test<<std::endl;
		step_numbers=step_numbers*2;

	}
}
//============================================================================
//QUESTION 1
//PART 2
//============================================================================
void question1_2()
{
	std::ofstream myfile;

	int step_numbers=2;
	int accuracy=6;
	double precision=pow(10.0,-double(accuracy));
	std::cout<<"Question1: (ii)."<<std::endl;
	double t_1=1.0;
	double t_0=-1.0;
	double x=-1.0; //initialise x
	double x_test=0.0;
	double dt=t_1-t_0;
	while(fabs((x-x_test)/x)>precision)
	{
		x_test=x;
		x=-1.0;
		double step_size= dt/double(step_numbers);
		
		myfile.open("q2.csv");
		myfile<<"t,x,\n";
		myfile<<t_0<<",";
		myfile<<x<<",\n";
		
		for(int step=1;step<=step_numbers;step++)
		{
			x=runge(step,x,step_size,t_0,g);
		
			myfile<<t_0+step*step_size<<",";
			myfile<<x<<",\n";
		}
		myfile.close();
		
		std::cout<<"n= "<<step_numbers<<"   x= "<<std::setprecision(6)<<x<<"   xold= "<<std::setprecision(accuracy+4)<<x_test<<std::endl;
		step_numbers=step_numbers*2;

	}
}

//============================================================================
//							FUNCTIONS AND R-K
//============================================================================
double f(double t, double x)
{
	return -3.0/2.0*(pow(x,3))*(pow(t,2.0));
}

double g(double t,double x)
{
	return pow(x,2)+2*x*t+pow(t,2);
}

double runge(int step,double x,double h,double t_0,double (*func)(double,double))
{
	double t=t_0+(step*h);

	double k_1=h*func(t,x);
	double k_2=h*func(t+(h/2.0),x+(k_1/2.0));
	double k_3=h*func(t+(h/2.0),x+(k_2/2.0));
	double k_4=h*func(t+h,x+k_3);
	return x+(1.0/6.0)*(k_1+(2.0*k_2)+(2.0*k_3)+k_4);
}
