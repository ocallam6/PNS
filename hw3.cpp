/*
============================================================================
					Practical Numerical Simulations
							Assignment 3
							 Question 1
					Matthew O'Callaghan: 16317515
============================================================================
*/

#include <iostream>
#include<cmath>
#include<iomanip>
#include<fstream> //Create CSV file with all the values for plotting.
//============================================================================
class Grid
{
  private:
    int 		n_;
    std::vector<double>	data_; 

    int index_(int x, int y) const 
   {
     return x + n_ * y;
   }
  public:		 
   Grid(int n) : n_(n), data_((n+1)*(n+1)) 
  {
    for (int i=0;i<(n+1)*(n+1);i++) data_[i] = 0.0;
  }

  double& operator() (int x, int y) 
  {
    return data_[index_(x,y)];
  }
  double  operator() (int x, int y) const 
  {
    return data_[index_(x,y)];
  }

  bool boundary0(int x, int y)
  {
  	if((x==0.0 || x==double(n_) || y==0.0 || y== double(n_) ))
  	{
  		return true;
  	}
  	else{
  		return false;
  	}
  }

  bool boundary1(int x, int y)
  {
  	if((x>=2.0*n_*0.1 && x<=4.0*n_*0.1)&&(y==2.0*n_*0.1 || y==3.0*n_*0.1))
  	{
  		return true;
  	}
  	else{
  		return false;
  	}
  }
   bool boundary2(int x, int y)
  {
  	if(((x>=4.0*n_*0.1 && x<=7.0*n_*0.1)&&(y==8.0*n_*0.1)) ||((x==8.0*n_*0.1)&&(y>=2.0*n_*0.1&&y<=8.0*n_*0.1)))
  	{
  		return true;
  	}
  	else{
  		return false;
  	}
  }

  void print_field()
  {
  	for (int i = 0; i <=n_; ++i)
  	{
  		for (int j = 0; j <= n_; ++j)
  		{
  			std::cout<<operator(n_-i,j)<<",";
  		}
  		std::cout<<"\n";
  	}
  }
  double partial_y(int x, int y)
  {
    if (x!=0.0 || x!= double(n_) || y!=0.0 || y!= double(n_))
    {
      return 0; //neumann condintions
    }
    else
    {  
      return 0.5 * double(n_)*(operator()(x,y+1)-operator(x,y-1));
    }
  }

  int size() const { return n_; } 
}; 


void update(Grid& field, double x, double y, int n, double w, double& delta)
{
	if (x<=double(n) && x>=0.0  && y<=double(n) && y>=0.0 )
	{
		if(field.boundary0(x,y)==true)
		{
			field.operator()(x,y)=0.0;
		}
		if(field.boundary1(x,y)==true)
		{
			field.operator(x,y)=2.0;
		}
		if(field.boundary2(x,y)==true)
		{
			field.operator(x,y)==-1.0;
		}
		else
		{
			double f0=field.operator(x,y);
			field.operator(x,y)=0.25*w*(field.operator(x-1,y)+field.operator(x+1,y)+field.operator(x,y-1)+field.operator(x,y+1))+(1-w)*field.operator(x,y);
			double df=field.operator(x,y)-f0;
			delta += df*df;
		}
	else
	{
		std::cout<<"Error x,y outside grid \n";
	}
}

void update(Grid& field, double w, double accuracy)
{
	double n=field.size();
	double delta;
	do
	{
	delta=0.0;
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <=n ; ++j)
		{
			update(field,i,j,w, delta);
		}
	}
	}
	while(sqrt(delta)/double(n) > accuracy);
}


int main()
{
	int size=1*10;   //has to be a multiple of 10 to work 
	double omega=1.97;
	double accuracy=1.0e-10;

	Grid field(size);

	field.print_field();
	update(field,omega,accuracy);
	field.print_field();

}	




