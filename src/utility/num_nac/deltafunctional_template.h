namespace iquads {

template < class Functional_Type, class Variable_Type >
class DeltaFunctional
{

public:
  DeltaFunctional<Functional_Type, Variable_Type>* 
    operator/= ( Variable_Type variable )
  {
    this->value_.compute_quotient( variable );
    this->quotient_computed_ = true;
    return this;
  }

  DeltaFunctional<Functional_Type, Variable_Type>*
   operator= ( Functional_Type functional_a )
  {
    if( functional_a.value_differenced() == false ){

    }
    this->value_ = functional_a;
    return this;
  }

public:
  friend 
   DeltaFunctional< Functional_Type, Variable_Type >
    operator- ( Functional_Type functional_a, Functional_Type functional_b )
  {
    DeltaFunctional< Functional_Type, Variable_Type > retval;
    {
      functional_a -= functional_b;
      retval = functional_a;
    }
    return retval;
  }

public:
  bool quotient_computed() const { return this->quotient_computed_; }

private:
  Functional_Type value_;
  bool quotient_computed_;

};

} // end of namespace iquads
