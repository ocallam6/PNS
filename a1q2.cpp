#include<iostream>
#include<vector>
#include <cmath>
std::vector<double> func(std::vector<double> x);
std::vector<double> runge(int step,std::vector<double> x,double h,double t_0);
int main()
{
int step_numbers=20;
int accuracy=5;
double precision=(1.0/(pow(10.0,accuracy)));
std::cout<<precision;
//QUESTION 2
//PART 1
std::cout<<"Question2: (i)."<<std::endl;
std::vector<double> x;
x.push_back(0.02);
x.push_back(0);
x.push_back(0);

double t_1=60.0;
double t_0=0.0;

double dt=t_1-t_0;

double step_size= dt/double(step_numbers);

for(int step=0;step<step_numbers;step++)
{
x=runge(step,x,step_size,t_0);
}
return 0;
}



std::vector<double> func(std::vector<double> x)
{
if (x.size()==3)
{
std::vector<double> variable;

variable.push_back(x[0]);
variable.push_back(x[1]);
variable.push_back(-x[0]+pow(x[1],2)-2.017*x[2]);
return variable;
else
{
cout<<"ERROR ON VECTOR DIMENSION \n";
}
}
}

std::vector<double> runge(int step,std::vector<double> x,double h,double t_0)
{

double t=t_0+(step*h);
std::vector<double> k_1=h*func(x);
std::vector<double> k_2=h*func(x+(k_1/2.0));
std::vector<double> k_3=h*func(x+(k_2/2.0));
std::vector<double> k_4=h*func(x+k_3);
return x+(1.0/6.0)*(k_1+(2.0*k_2)+(2.0*k_3)+k_4);

}
