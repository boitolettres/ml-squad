
//------------------------------------------------------------------------------

template < typename Value, typename ClusterModelType, typename Kernel >
KMeans< Value, ClusterModelType, Kernel >::KMeans()
  : _expectation( 0 )
{
}

//------------------------------------------------------------------------------

template < typename Value, typename ClusterModelType, typename Kernel >
KMeans< Value, ClusterModelType, Kernel >::~KMeans()
{
  if ( _expectation ) {
    delete [] _expectation;
  }
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
template < typename ValueContainer >
const typename KMeans< Value, ClusterModelType, Kernel >::Assignments &
KMeans< Value, ClusterModelType, Kernel >::operator()( 
  const ValueContainer & data, 
  size_t k, 
  size_t iterations,
  const Kernel & kernel 
)
{
  _k      = k;
  _kernel = kernel;
  if ( _expectation ) {
    delete [] _expectation;
  }
  _expectation = new double[data.size() * _k];
  _assignments.resize( data.size() );
  _models.resize( _k );
  
  initialize( data );
  for ( size_t i = 0; i < iterations; ++i ) {
    expectation( data );
    Traits<Value>::normalize( _expectation, data.size(), _k );
    maximization( data );
  }
  expectation( data );
  Traits<Value>::normalize( _expectation, data.size(), _k );
  assign( data );
  return _assignments;
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
const typename KMeans< Value, ClusterModelType, Kernel >::Assignments &
KMeans< Value, ClusterModelType, Kernel >::assignments() const
{
  return _assignments;
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
const typename KMeans< Value, ClusterModelType, Kernel >::ClusterModelList &
KMeans< Value, ClusterModelType, Kernel >::models() const
{
  return _models;
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
template < typename ValueContainer >
void 
KMeans< Value, ClusterModelType, Kernel >::initialize( const ValueContainer & data )
{
  for ( size_t i = 0; i < _k; ++i ) {
    _models[i] = data[i * data.size() / _k];
  }
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
template < typename ValueContainer >
void 
KMeans< Value, ClusterModelType, Kernel >::expectation( const ValueContainer & data )
{
  size_t valuePos = 0;  
  for ( size_t i = 0; i < data.size(); ++i ) {
    for ( size_t j = 0; j < _k; ++j ) {
      _expectation[valuePos++] = _kernel( _models[j], data[i] );
    }
  }
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
template < typename ValueContainer >
void 
KMeans< Value, ClusterModelType, Kernel >::maximization( const ValueContainer & data )
{
  for ( size_t i = 0; i < _k; ++i ) {
    size_t valuePos = 0;
    size_t dataSize = data.size();
    double sum      = 0;
    for ( size_t j = 0; j < dataSize; ++j ) {
      sum      += _expectation[valuePos + i];
      valuePos += _k;
    }
    valuePos = 0;
    Value & model = _models[i];
    model        = Value::Zero();
    for ( size_t j = 0; j < dataSize; ++j ) {
      model    += _expectation[valuePos + i] * data[j] / sum;
      valuePos += _k;
    }
  }
}

//------------------------------------------------------------------------------
  
template < typename Value, typename ClusterModelType, typename Kernel >
template < typename ValueContainer >
void 
KMeans< Value, ClusterModelType, Kernel >::assign( const ValueContainer & data )
{
  size_t valuePos = 0;
  for ( size_t i = 0; i < data.size(); ++i ) {
    double maxExpectation = 0;
    size_t maxCluster     = 0;
    for ( size_t j = 0; j < _k; ++j ) {
      double e = _expectation[valuePos++];
      if ( e > maxExpectation ) {
        maxExpectation = e;
        maxCluster     = j;
      }
    }
    _assignments[i] = maxCluster;
  }
}
