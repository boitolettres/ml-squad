#ifndef SQUAD_TRAITS_H
#define SQUAD_TRAITS_H


#include <list>
#include <vector>
#include <cmath>
#include <cstdio>

namespace squad
{
  

template < typename Value >
class Traits
{
public:
  typedef Value ClusterModel;
  
  template < typename ClusterType, typename ValueType >
  static double kernel( const ClusterType & cluster, const ValueType & value );
 
  static void normalize( 
    double * expectation, 
    size_t valueSize,
    size_t k );
};

#include "Traits.tpp"
  
}

#endif //SQUAD_TRAITS_H
