#include <math/matrix.h>
#include <complex>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

//#define USE_VECTORS

void convert_to_rgb(std::size_t min, std::size_t max, const int& cmax, const int& v, int& r, int& g, int& b)
{
   double ratio = 2*(v-min)/(max-min);
   b = int(std::max(0.0,cmax*(1-ratio)));
   r = int(std::max(0.0,cmax*(ratio-1)));
   g = cmax - b - r;
}

int main(int argc, char** argv)
{
   double _incx = 0.001;
   double _incy = 0.001;
   std::size_t _maxit = 100;
   std::string _file = "Mandelbrot";
   
   int narg = 0;
   while( narg < argc )
   {
      if( std::strcmp(argv[narg],"-incx") == 0 )
      {
         if(++narg < argc)
         {
            _incx = std::atof(argv[narg]);
         }
      }
      else if( std::strcmp(argv[narg],"-incy") == 0 )
      {
         if(++narg < argc)
         {
            _incy = std::atof(argv[narg]);
         }
      }
      else if( std::strcmp(argv[narg],"-maxit") == 0 )
      {
         if(++narg < argc)
         {
            _maxit = std::atoi(argv[narg]);
         }
      }
      else if( std::strcmp(argv[narg],"-filename") == 0 )
      {
         if(++narg < argc)
         {
            _file = std::string(argv[narg]);
         }
      }
      ++narg;
   }
   double xmin = -2.0;
   double xmax = 1.0;
   double ymin = -1.0;
   double ymax = 1.0;
   std::size_t nx = std::floor((xmax - xmin) / _incx);
   std::size_t ny = std::floor((ymax - ymin) / _incy);

   // Create the image file
   int maxc = 255;
   _file += ".ppm";
   std::ofstream img(_file.c_str());
   img << "P3" << std::endl;
   img << ny << " " << nx << std::endl;
   img << maxc << std::endl;
   
   std::cout << "**** Generating the Mandelbrot set ****" << std::endl;
   std::cout << "      Number of X values: " << nx << std::endl;
   std::cout << "      Number of Y values: " << ny << std::endl;
   std::cout << "Max number of iterations: " << _maxit << std::endl;
   // Compute the mandelbrot set
   std::complex<double> p;
   for(std::size_t i=0; i<nx; ++i)
   {
      p.imag( xmin + _incx * i );
      for(std::size_t j=0; j<ny; ++j)
      {
         p.real( ymin + _incy * j );
         std::complex<double> k(0.0,0.0);
         std::size_t n =0;
         for(; n<_maxit; ++n)
         {
            k = k*k + p;
            if( 2.0 < std::abs(k) )
            {
               break;
            }
         }
         int r = 0;
         int g = 0;
         int b = 0;
         convert_to_rgb(0,_maxit,maxc,n,r,g,b);
         img << r << " " << g << " " << b << std::endl;
      }
   }
}
