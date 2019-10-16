#include "Planet.h"
#include<vector>
#include<cmath>
#include<fstream>
#include <iostream>
using namespace std;

double kinetic_energy(const Planet& p)
{
  return 0.5 * p.mass() * (
     p.vel(0) * p.vel(0) + p.vel(1) * p.vel(1) );
}

void update_position(double h, Planet& p)
{	
	for (int k = 0; k < 2; ++k)
	{
		p.pos(k)+= 0.5*h*p.mass()*p.vel(k);
	}
}

void update_position(double h, vector<Planet> &vp)
{
	for (int i = 0; i < vp.size(); ++i)
	{
		update_position(h,vp[i]);
	}
}


void update_velocity(double h, vector<Planet>& vp)
{	
	for (int p1 = 0; p1 < vp.size(); ++p1)
	{
		for (int p2 = 0; p2 < vp.size(); ++p2)
		{
		double r_ij[2];
		double r_ij2;
			if(p1==p2) continue;
			else
			{
		
				for (int x = 0; x < 2; ++x)
				{	
					r_ij[x]=vp[p1].pos(x)-vp[p2].pos(x);

				}
			r_ij2=pow((r_ij[0]*r_ij[0]+r_ij[1]*r_ij[1]),1.5);
			}
		for (int i = 0; i < 2; ++i)
		{
			vp[p1].vel(i)-=h*vp[p2].mass()*r_ij[i]/r_ij2;
		}

		}	
	}	
}


void update(double h,vector<Planet>& planets)
{
	update_position(h,planets);
	update_velocity(h,planets);
	update_position(h,planets);
}



vector<Planet> solar_system()
{
	Planet a(2.2,-0.5,0.1,-0.84,0.65);
	Planet b(0.8,-0.6,-0.2,2.86,0.7);
	Planet c(0.9,0.5,0.1,-0.44,-1.5);
	Planet d(0.4,0.5,0.4,1.15,-1.6);
	vector<Planet> planets;
	planets.push_back(a);
	planets.push_back(b);
	planets.push_back(c);
	planets.push_back(d);
	return planets;
}


int main()
{

  ofstream myfile;
  myfile.open("planets.csv");
  myfile<<"t,x00,x10,v00,v10,x01,x11,v01,v11,x02,x12,v02,v12,x03,x13,v03,v13,\n";

  vector<Planet> planets=solar_system();
  double t1=4.0;
  double t0=0.0;
  int step_numbers=10000;
  double step_size=(t1-t0)/double(step_numbers);

  cout<<"Initial ----------------- \n";
  


  for (int i = 0; i < planets.size(); ++i)
  {
  	cout <<"Planet "<<i<<" position=("<< planets[i].pos(0) <<","<< planets[i].pos(1)<<")\n";
  	cout <<"Planet "<<i<<" velocity=("<< planets[i].vel(0) <<","<< planets[i].vel(1)<<")\n";
  }
  


  for (int i = 0; i < step_numbers; ++i)
  {
  myfile<<i*step_size<<",";
  for (int j = 0; j < planets.size(); ++j)
	  {
	  	myfile<<planets[j].pos(0)<<","<< planets[j].pos(1)<<",";
	  	myfile <<planets[j].vel(0)<<","<< planets[j].vel(1)<<",";
	  } 
  myfile<<"\n"; 	
  update(step_size,planets);
  }




  cout<<"Final ----------------- \n";

  myfile<<t1<<",";
  for (int j = 0; j < planets.size(); ++j)
  {
  	myfile<<planets[j].pos(0)<<","<< planets[j].pos(1)<<",";
  	myfile<<planets[j].vel(0)<<","<< planets[j].vel(1)<<",";
  }
  for (int i = 0; i < planets.size(); ++i)
  {
  	cout <<"Planet "<<i<<" position=("<< planets[i].pos(0) <<","<< planets[i].pos(1)<<")\n";
  	cout <<"Planet "<<i<<" velocity=("<< planets[i].vel(0) <<","<< planets[i].vel(1)<<")\n";
  }

  

}

