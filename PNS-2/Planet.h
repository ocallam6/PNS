
class Planet
{
  private:
    double 	mass_;
    double 	v_[2]; 
    double 	x_[2]; 
  public:
    Planet(double m, double x0, double x1, double v0, double v1)
    {
      mass_ = m;
      x_[0] = x0; x_[1] = x1;
      v_[0] = v0; v_[1] = v1;
    }

   double mass() const { return mass_; }   

   double& vel(int k)       { return v_[k]; }
   double  vel(int k) const { return v_[k]; }
   double& pos(int k)       { return x_[k]; }
   double  pos(int k) const { return x_[k]; }
};

