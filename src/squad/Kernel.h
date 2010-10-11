#ifndef SQUAD_KERNEL_H
#define SQUAD_KERNEL_H


namespace squad
{


template < typename Covariance >
class Gaussian
{
public:
  Gaussian( const Covariance & covariance );
  
  template < typename Op1, typename Op2 >
  double operator()( const Op1 & op1, const Op2 & op2 );
private:
  Covariance _covariance;
};

template <>
class Gaussian<double>
{
public:
  Gaussian() : _covariance( 1 )
  {
  }

  Gaussian( double covariance ) : _covariance( covariance )
  {
  }

  template < typename Op1, typename Op2 >
  double operator()( const Op1 & op1, const Op2 & op2 )
  {
    return exp( -0.5 * ( op1 - op2 ).dot( op1 - op2 ) / _covariance );
  }
private:
  double _covariance;
};

#include "Kernel.tpp"


}

#endif //SQUAD_KERNEL_H
