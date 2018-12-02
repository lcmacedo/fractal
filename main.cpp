// Sistemas Operacionais - Trabalho 2
// Autor: Lucas Corrêa Macedo

#include <iostream>
#include <chrono>
#include <complex>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <pthread.h>

#include "Pixel.h"
#include "Image.h"

using namespace std;

struct threadArguments
{
  Image *image;
  unsigned startingX; // Coordinates on the image
  unsigned startingY;
  unsigned endingX; 
  unsigned endingY;  
  double xMin; // Coordinates on the plane
  double xMax; 
  double yMin;  
  double yMax;
};

// Draws the mandelbrot set on an image
// From the point xMin to xMax and from yMin to yMax
void *drawMandelbrot (void *args)
{
  struct threadArguments *threadArgs;
  threadArgs = (struct threadArguments *) args;

  Image *image = threadArgs->image; 
  unsigned startingX = threadArgs->startingX;
  unsigned startingY = threadArgs->startingY;
  unsigned endingX = threadArgs->endingX; 
  unsigned endingY = threadArgs->endingY;  
  double xMin = threadArgs->xMin; 
  double xMax = threadArgs->xMax; 
  double yMin = threadArgs->yMin;  
  double yMax = threadArgs->yMax;

  complex<double> currentPoint (xMin, yMax); // Starting point on the plane
  complex<double> z;

  double xStep = (xMax - xMin) / (endingX - startingX); // Will be added to the real part of currentPoint after each iteration
  double yStep = (yMax - yMin) / (endingY - startingY); // Same as above for the imaginary part
  
  unsigned currentX, currentY; // Coordinates (in pixels) of the point where the sequence is being currently calculated

  unsigned char numIterations = 0;
  unsigned char maxNumberOfIterations = 255;

  Pixel pixel; // For setting the color of a pixel in the image
  
  for (currentX = startingX; currentX < endingX; currentX++)
  {
    // Reset the y value on the beginning of a new column
    if (currentX > startingX)
      currentPoint += (complex<double> (0, 1) * (yMax - yMin));  

    for (currentY = startingY; currentY < endingY; currentY++)
    {
      z = 0;
         
      for (numIterations = 0; numIterations < maxNumberOfIterations && abs(z) < 2.0; numIterations++)
      {
        z = z*z + currentPoint;
      }

      pixel.setColor (numIterations, numIterations, numIterations); // Grayscale
            
      image->setPixel (currentY, currentX, pixel);

      currentPoint -= (complex<double> (0, 1) * yStep);      
    }

    currentPoint += xStep;
  } 

  return 0;
}

int main (int argc, char ** argv)
{
  int width = 0; // Image width
  int height = 0; // Image height

  double xMin, xMax, yMin, yMax; // Boundaries of area where the image will be generated

  int nThreads; // Number of threads

  const string USAGE_MSG = "Usage: mandelbrot width height xmin xmax ymin ymax nthreads";

  if (argc < 8)
  {
    cout << USAGE_MSG << endl;
    exit (0);
  }

  width = atoi (argv [1]);
  height = atoi (argv [2]);
  xMin = atof (argv [3]); 
  xMax = atof (argv [4]);
  yMin = atof (argv [5]);
  yMax = atof (argv [6]);
  nThreads = atoi (argv [7]);

  auto start = chrono::steady_clock::now (); // Start the timing

  Image image (width, height);

  struct threadArguments *threadArgs = (threadArguments *) malloc (nThreads * sizeof (threadArguments));
  static pthread_t *threads = (pthread_t *) malloc (nThreads * sizeof (pthread_t));
  pthread_attr_t *attributes = (pthread_attr_t *) malloc (nThreads * sizeof (pthread_attr_t)); 
     
 	// Initializing attributes and arguments	
  for (int i = 0; i < nThreads; i++)
  {
	  pthread_attr_init (&attributes [i]);
    threadArgs [i].image = &image;
    threadArgs [i].startingX = i * (width / nThreads);
    threadArgs [i].startingY = 0;
    threadArgs [i].endingX = (i + 1) * (width / nThreads);
    threadArgs [i].endingY = height;
    threadArgs [i].xMin = xMin + i * (xMax - xMin) / nThreads;
    threadArgs [i].xMax = xMin + (i + 1) * (xMax - xMin) / nThreads;
    threadArgs [i].yMin = yMin;
    threadArgs [i].yMax = yMax;
  }

 	// Creating the threads
  for (int i = 0; i < nThreads; i++)
    pthread_create (&threads [i], &attributes [i], drawMandelbrot, &threadArgs [i]);
  
	// Calling join to wait for the threads to finish
  for (int i = 0; i < nThreads; i++)
    pthread_join (threads [i], NULL);
  
  ofstream out("mandelbrot.ppm", ios::binary);
  out << image;  

  auto end = chrono::steady_clock::now (); // End the timing

  //cout << "Finished in " << chrono::duration <double> (end - start).count () << " s" << endl;
  cout << chrono::duration <double> (end - start).count () << endl;

  free (threadArgs);
  free (threads);
  free (attributes);

  return 0;
}























