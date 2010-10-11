//------------------------------------------------------------------------------

template < typename Value >
template < typename ClusterType, typename ValueType >
inline
double
Traits<Value>::kernel( const ClusterType & cluster, const ValueType & value )
{
  return exp( -0.5 * ( cluster - value ).dot( cluster - value ) / ( 100 ) );
}

//------------------------------------------------------------------------------

template < typename Value >
void 
Traits<Value>::normalize( 
  double * expectation,
  size_t valueSize,
  size_t k 
)
{
  size_t valuePos = 0;
  for ( size_t valueIdx = 0; valueIdx < valueSize; ++valueIdx ) {
    double sum = 0;
    for ( size_t clusterIdx = 0; clusterIdx < k; ++clusterIdx ) {
      sum += expectation[valuePos + clusterIdx];
    }
    if ( sum == 0.0 ) {
      fprintf( stderr, "pedos batman!\n" );
    }
    for ( size_t clusterIdx = 0; clusterIdx < k; ++clusterIdx ) {
      expectation[valuePos + clusterIdx] /= sum;
    }
    valuePos += k;
  }
}
  
