#include <squad/KMeans.h>
#include <Eigen/Core>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using squad::KMeans;
using squad::Gaussian;
using Eigen::Vector2f;
using Eigen::Vector3f;
using namespace std;

//------------------------------------------------------------------------------

template <typename Palette, typename Values, typename Assignments, typename Models>
bool displayResults( 
  sf::RenderWindow & mainWindow, 
  const Palette & palette, 
  const Values & values,
  const Assignments & assignments,
  const Models & models 
)
{
 sf::Event event;
  while ( mainWindow.GetEvent( event ) ) {
    switch ( event.Type ) {
      case sf::Event::Closed:
        mainWindow.Close();
        return false;
        break;
      default:
        break;
    }
  }
  mainWindow.Clear( sf::Color( 255, 255, 255 ) );
  for ( size_t i = 0; i < assignments.size(); ++i ) {
    size_t cluster = assignments[i];
    sf::Color color( palette[cluster][0], palette[cluster][1], palette[cluster][2] );
    sf::Shape point = sf::Shape::Circle( 
      values[i].x(), 
      values[i].y(), 
      6, 
      color
    );
    mainWindow.Draw( point );
  }

  sf::Color color( 255, 255, 255 );
  for ( size_t i = 0; i < models.size(); ++i ) {
    sf::Shape point = sf::Shape::Circle( 
      models[i].x(), 
      models[i].y(), 
      10, 
      color
    );
    mainWindow.Draw( point );
  }

  mainWindow.Display();
  return true;
}

//------------------------------------------------------------------------------

int main() { 
  size_t numValues = 10000;
  size_t k         = 2;
  size_t width     = 800;
  size_t height    = 600;
  
  vector<Vector2f> values( numValues * 2 );
  
  for ( size_t i = 0; i < numValues; i++ ) {
    Vector2f m;
    m << random() % width / 2, random() % height / 2;
    values[i] = m;
  }

  for ( size_t i = 0; i < numValues; i++ ) {
    Vector2f m;
    m << random() % width / 2 + width / 3, random() % height / 2 + height / 3;
    values[numValues + i] = m;
  }
  
  KMeans<Vector2f> kmeans;
  kmeans( values, k, 20, Gaussian<double>( 100 * 100 ) );
  
  float factor = 20;
  size_t limit  = size_t( 255 / factor );
  vector<Vector3f> colorValues( limit * limit * limit );
  size_t colorCount = 0;
  for ( size_t r = 0; r < limit; r++ ) {
    for ( size_t g = 0; g < limit; g++ ) {
      for ( size_t b = 0; b < limit; b++ ) {
        Vector3f m;
        m << r * factor, g * factor, b * factor;
        colorValues[colorCount++] = m;
      }
    }
  }
  KMeans<Vector3f> colorKmeans;
  colorKmeans( colorValues, k, 20, Gaussian<double>( 100 )  );

  sf::RenderWindow mainWindow( sf::VideoMode( width, height, 32 ), "Data Visualization" );
  mainWindow.SetFramerateLimit( 1 );
  
  bool running = true;  
  while ( running ) {
    running = displayResults( mainWindow, colorKmeans.models(), values, kmeans.assignments(), kmeans.models() );
  }
}

