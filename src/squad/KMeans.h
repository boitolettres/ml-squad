#ifndef SQUAD_KMEANS_H
#define SQUAD_KMEANS_H


#include "Kernel.h"
#include "Traits.h"
#include <eigen2/Eigen/Array>
#include <vector>
#include <cstdio>

namespace squad
{


template < typename Value, typename ClusterModelType = Value, typename Kernel = Gaussian<double> >
class KMeans
{
public:
  typedef std::vector< size_t > Assignments;
  typedef ClusterModelType ClusterModel;
  typedef std::vector< ClusterModel > ClusterModelList;
  
  KMeans();
  ~KMeans();

  template < typename ValueContainer >
  const Assignments & operator()( const ValueContainer & values, size_t k, size_t iterations = 20, const Kernel & kernel = Kernel( 1 ) );
  
  const Assignments & assignments() const;
  const ClusterModelList & models() const;
  
private: 
  template < typename ValueContainer >
  void initialize( const ValueContainer & data );
  
  template < typename ValueContainer >
  void expectation( const ValueContainer & data );
  
  template < typename ValueContainer >
  void maximization( const ValueContainer & data );
  
  template < typename ValueContainer >
  void assign( const ValueContainer & data );

  size_t           _k;
  Kernel           _kernel;
  Assignments      _assignments;
  ClusterModelList _models;
  double *         _expectation;
};


#include "KMeans.tpp"


}

#endif //SQUAD_KMEANS_H
