/*
============================================================================
					Practical Numerical Simulations
							Assignment 1
							 Question 2
					Matthew O'Callaghan: 16317515
============================================================================
*/
#include<iostream>
#include<vector>
#include<iomanip>
#include <cmath>
#include<fstream> //Create CSV file with all the values for plotting.

//============================================================================

std::vector<double> vec_add(std::vector<double> x,std::vector<double> y);
std::vector<double> vec_times_const(std::vector<double> x,double y);
std::vector<double> func(std::vector<double> x);
std::vector<double> runge(int step,std::vector<double> x,double h,double t_0);
void question1();
void question2();

//============================================================================

int main()
{
	question1();
	question2();
	return 0;
}

//============================================================================
//QUESTION 2
//PART 1
//============================================================================
void question1()
{
	std::ofstream myfile;

	int step_numbers=100;
	int accuracy=6;
	double precision=(1.0/(pow(10.0,accuracy)));
	std::cout<<"Question2: (i)."<<std::endl;
	std::vector<double> x(3);

	x[0]=0.02;
	x[1]=0;
	x[2]=0;

	double t_1=60.0;
	double t_0=0.0;
	double x_test=1.0;
	double dt=t_1-t_0;

	while(fabs((x[0]-x_test)/x[0])>double(precision))
	{
		x_test=x[0];
		x[0]=0.02;
		x[1]=0;
		x[2]=0;
		double step_size= dt/double(step_numbers);

		myfile.open("q2q1.csv");
		myfile<<"t,x0,x1,x2, \n";
		myfile<<t_0<<","<<x[0]<<","<<x[1]<<","<<x[0]<<",\n";

		for(int step=1;step<=step_numbers;step++)
		{
			x=runge(step,x,step_size,t_0);
		
			myfile<<t_0+step*step_size<<","<<x[0]<<","<<x[1]<<","<<x[0]<<",\n";
		}
		myfile.close();
		
		for (int i = 0; i < 3; ++i)
		{
			std::cout<<"x"<<i<<"  =  "<<std::setprecision(3)<<x[i]<<std::endl;
		}
		step_numbers=step_numbers*2;
	}
}

//============================================================================
//QUESTION 2
//PART 2
//============================================================================
void question2()
{
	std::ofstream myfile;
	
	int step_numbers=100;
	int accuracy=3.0;
	double precision=(1.0/(pow(10.0,accuracy)));
	std::cout<<"Question2: (ii)."<<std::endl;
	std::vector<double> x(3);

	x[0]=0.02;
	x[1]=0;
	x[2]=0;

	double t_1=60.0;
	double t_0=0.0;
	double x_test=1.0;
	double dt=t_1-t_0;

	while(fabs((x[0]-x_test)/x[0])>double(precision))
	{
		x_test=x[0];
		x[0]=0.0205;
		x[1]=0;
		x[2]=0;
		double step_size= dt/double(step_numbers);

		myfile.open("q2q2.csv");
		myfile<<"t,x0,x1,x2, \n";
		myfile<<t_0<<","<<x[0]<<","<<x[1]<<","<<x[0]<<",\n";

		for(int step=1;step<=step_numbers;step++)
		{
			x=runge(step,x,step_size,t_0);
	
			myfile<<t_0+step*step_size<<","<<x[0]<<","<<x[1]<<","<<x[0]<<",\n";
		}
		myfile.close();

		for (int i = 0; i < 3; ++i)
		{
			std::cout<<"x"<<i<<"  =  "<<std::setprecision(3)<<x[i]<<std::endl;
		}
		step_numbers=step_numbers*2;
	}
}

//============================================================================
//                         FUNCTION DEFINITON & R-K
//============================================================================
std::vector<double> func(std::vector<double> x)
{
	if (x.size()==3)
	{
		std::vector<double> variable(3);

		variable[0]=x[1];
		variable[1]=x[2];
		variable[2]=-x[0]+x[1]*x[1]-2.017*x[2];
		return variable;
	}
	else
	{
		std::cout<<"ERROR ON VECTOR DIMENSION \n";
	}
}

std::vector<double> runge(int step,std::vector<double> x,double h,double t_0)
{
	double t=t_0+(step*h);
	std::vector<double> k_1=vec_times_const(func(x),h);
	std::vector<double> k_2=vec_times_const(func(vec_add(x,(vec_times_const(k_1,0.5)))),h);
	std::vector<double> k_3=vec_times_const(func(vec_add(x,(vec_times_const(k_2,0.5)))),h);
	std::vector<double> k_4=vec_times_const(func(vec_add(x,k_3)),h);

	std::vector<double> sum1=vec_times_const(vec_add(k_2,k_3),2.0);
	std::vector<double> sum2=vec_add(k_1,k_4);
	std::vector<double> res1=vec_times_const(vec_add(sum1,sum2),(1.0/6.0));
	return vec_add(x,res1);
}
//============================================================================
//						VECTOR OPERATIONS
//============================================================================
std::vector<double> vec_add(std::vector<double> x,std::vector<double> y)
{	if (x.size()==y.size())
	{
		std::vector<double> result(3);
		for (int i = 0; i < x.size(); ++i)
		{
			result[i]=x[i]+y[i];
		}
	return result;
	}
	else {std::cout<<"ERROR";}
}

std::vector<double> vec_times_const(std::vector<double> x,double y)
{
	std::vector<double> result(3);
	for (int i = 0; i < x.size(); ++i)
	{
		result[i]=x[i]*y;
	}
	return result;
}

//============================================================================