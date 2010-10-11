//------------------------------------------------------------------------------

template < typename Covariance >
Gaussian<Covariance>::Gaussian( const Covariance & covariance )
  : _covariance( covariance )
{
}

//------------------------------------------------------------------------------

template < typename Covariance >
template < typename Op1, typename Op2 >
double
Gaussian<Covariance>::operator()( const Op1 & op1, const Op2 & op2 )
{
  return exp( -0.5 * ( op1 - op2 ) * _covariance.inv() * ( op1 - op2 ) );
}
