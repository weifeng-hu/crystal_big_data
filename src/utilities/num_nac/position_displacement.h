

namespace iquads {

class PositionDisplacement
{
public:
  PositionDisplacement(){
   this->store = 0.0e0;
  }
  PositionDisplacement( double x ){
   this->store = x;
  }

public:
  friend 
   PositionDisplacement 
    operator* ( double lhs, position_displacment rhs ){
     PositionDisplacement retval;
     retval.set_store() = lhs * rhs.set_store();
     return retval;
   }

   PositionDisplacement* operator*= ( double rhs ){
    this->set_store() = this->set_store() * rhs;
    return this;
   }

public:
  double& set_store() return { this->store; }

private:
  double store_;

}; // end of class PositionDisplacement

} // end of namespace iquads
