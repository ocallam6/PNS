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
#include<vector>
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
  	if(((x>=4.0*n_*0.1 && x<=7.0*n_*0.1)&&(y==8.0*n_*0.1)) ||((x==8.0*n_*0.1)&&((y>=2.0*n_*0.1) && (y<=8.0*n_*0.1))))
  	{
  		return true;
  	}
  	else{
  		return false;
  	}
  }

  void print_field()
  {
  	for (int i = 0; i<=n_; ++i)
  	{
  		for (int j = 0; j <= n_; ++j)
  		{
  			std::cout<<operator()(j,n_-i)<<",";
  		}
  		std::cout<<"\n";
  	}
  }
  
  void to_csv()
  {
  	std::ofstream myfile;
  	myfile.open("plot1.csv");
  	myfile<<"x,y,f, \n";
  	//not including boundary here
  	
  	for(int i=1; i<n_; ++i)
  		{
  		for(int j=1; j<n_; ++j)
  			{
  				myfile<<i<<","<<j<<","<<operator()(i,j)<<",\n";
  			}
  		
  		}
  	myfile.close(); 
  }


  double partial_y(int x, int y)
  {
    if (x!=0.0 || x!= double(n_) || y!=0.0 || y!= double(n_))
    {
      return 0.5 * double(n_)*(operator()(x,y+1)-operator()(x,y-1));
    }
    else
    {  
      return 0;
    }
  }

  int size() const { return n_; } 
}; 


void update(Grid& field, double x, double y, int n, double w, double& delta)
{
	if (x<double(n) && x>0.0  && y<double(n) && y>0.0 )
	{
		if(field.boundary0(x,y)==true)
		{
			std::cout<<"Error x,y on boundary of grid \n";
		}
		else{ if(field.boundary1(x,y)==true)
			{
				field.operator()(x,y)=2.0;
			}
			else{	if(field.boundary2(x,y)==true)
				{
					field.operator()(x,y)=-1.0;
				}
				else
				{
					double f0=field.operator()(x,y);
					field.operator()(x,y)=0.25*w*(field.operator()(x-1,y)+field.operator()(x+1,y)+field.operator()(x,y-1)+field.operator()(x,y+1))+(1-w)*field.operator()(x,y);
					double df=field.operator()(x,y)-f0;
					delta += df*df;
				}
			    }
		   }
	}
	else
	{
		std::cout<<"Error x,y outside grid \n";
	}
}

void sor(Grid& field, double w, double accuracy)
{
	double n=field.size();
	double delta;
	do
	{
  delta=0.0;
  for (int i = 1; i < n; ++i)
  {
    field.operator()(i,0)=(4.0*field.operator()(i,1)-field.operator()(i,2))/3.0;
    field.operator()(i,n)=(4.0*field.operator()(i,n-1)-field.operator()(i,n-2))/3.0; 
  }
  for (int i = 1; i < n; ++i)
  {
    field.operator()(0,i)=(4.0*field.operator()(1,i)-field.operator()(2,i))/3.0;
    field.operator()(n,i)=(4.0*field.operator()(n-1,i)-field.operator()(n-2,i))/3.0; 
  }



	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j <n ; ++j)
		{
			update(field,i,j,n,w, delta);
		}
	}
	}
	while(sqrt(delta)/double(n) > accuracy);
}


int main()
{
	int size=32*10;   //has to be a multiple of 10 to work 
	double omega=1.97;
	double accuracy=1.0e-10;

	Grid field(size);

	//field.print_field();
	sor(field,omega,accuracy);
	//field.print_field();

	std::cout<<"d/dy phi(3/n,6/n)= "<<field.partial_y(3.0*double(size)*0.1,6.0*double(size)*0.1)<<std::endl;
	
	field.to_csv();
}	


