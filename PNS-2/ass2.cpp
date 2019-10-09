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
//============================================================================

std::vector<double> vec_add(std::vector<double> x,std::vector<double> y);
std::vector<double> vec_times_const(std::vector<double> x,double y);
std::vector<double> func(std::vector<double> x);
std::vector<double> runge(int step,std::vector<double> x,double h,double t_0);
double b(double c);

int main()
{
	double c_lo=-1000.0;
	double c_hi=1000.0;
	double b_lo=b(c_lo);
	double b_hi=b(c_hi);
	double tol=1.0e-10;
	double c;
	do
	{
		c = 0.5 * (c_hi+c_lo);
	    double b_c = b(c); 
	    if (b_c*b_lo > 0.0)
	    {
	      c_lo=c;b_lo=b_c;
	    }
	    else 
	    {
	      c_hi=c;b_hi=b_c;
	    }
	std::cout << "c_lo="<<  c_lo << " -- " <<"c_hi="<< c_hi << "\n";
	}
	while(c_hi-c_lo>tol);
	std::cout<< "b(c)="<<b(c)<<"\n"<<"c="<<c<<std::endl;
}



double b(double c)
{
	std::ofstream myfile;

	int step_numbers=100;
	int accuracy=3;
	double precision=(1.0/(pow(10.0,accuracy)));
	std::cout<<"Iteration for c="<<c<<std::endl;
	std::vector<double> x(2);

	x[0]=0.0;
	x[1]=c;


	double t_1=10.0;
	double t_0=0.0;
	double x_test=1.0;
	double dt=t_1-t_0;

	while(fabs((x[0]-x_test)/x[0])>double(precision)&& step_numbers<10000)
	{
		x_test=x[0];
		x[0]=0.00;
		x[1]=c;
		double step_size= dt/double(step_numbers);

		myfile.open("ass2.csv");
		myfile<<"t,x0,x1, \n";
		myfile<<t_0<<","<<x[0]<<","<<x[1]<<",\n";

		for(int step=1;step<=step_numbers;step++)
		{
			x=runge(step,x,step_size,t_0);
		
			myfile<<t_0+step*step_size<<","<<x[0]<<","<<x[1]<<",\n";
		}
		myfile.close();
		
		for (int i = 0; i < 2; ++i)
		{
			std::cout<<"x"<<i<<"  =  "<<std::setprecision(6)<<x[i]<<std::endl;
		}
		std::cout<<"^------n="<<step_numbers<<"-------^ \n";
		step_numbers=step_numbers*2;
	}
	return x[0]-1;
}




//============================================================================
//                         FUNCTION DEFINITON & R-K
//============================================================================
std::vector<double> func(std::vector<double> x, double t)
{
	if (x.size()==2)
	{
		std::vector<double> variable(2);

		variable[0]=x[1];
		variable[1]=-pow(x[0],3)*exp(-pow(x[0],2))*3*t;
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
	std::vector<double> k_1=vec_times_const(func(x,t),h); //k_1=h*func(x)
	std::vector<double> k_2=vec_times_const(func(vec_add(x,(vec_times_const(k_1,0.5))),t+0.5*h),h); //k_2=h*func(x+(k_1/2.0))
	std::vector<double> k_3=vec_times_const(func(vec_add(x,(vec_times_const(k_2,0.5))),t+0.5*h),h); //k_3=h*func(x+(k_2/2.0))
	std::vector<double> k_4=vec_times_const(func(vec_add(x,k_3),t+h),h);  //k_4=h*func(x+k_3)

	std::vector<double> sum1=vec_times_const(vec_add(k_2,k_3),2.0); 
	std::vector<double> sum2=vec_add(k_1,k_4); 
	std::vector<double> res1=vec_times_const(vec_add(sum1,sum2),(1.0/6.0)); 
	return vec_add(x,res1); //=x+(1.0/6.0)*(k_1+(2.0*k_2)+(2.0*k_3)+k_4)
}
//============================================================================
//						VECTOR OPERATIONS
//============================================================================
std::vector<double> vec_add(std::vector<double> x,std::vector<double> y)
{	if (x.size()==y.size())
	{
		std::vector<double> result(2);
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
	std::vector<double> result(2);
	for (int i = 0; i < x.size(); ++i)
	{
		result[i]=x[i]*y;
	}
	return result;
}

//============================================================================