// Sistemas Operacionais - Trabalho 2
// Autor: Lucas Corrêa Macedo

#include <vector>
#include <iostream>

#include "Pixel.h"

using namespace std;

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
  friend ostream &operator<< (ostream &, const Image &);

	public:
		Image (unsigned, unsigned);

		void setPixel (unsigned, unsigned, Pixel &);

    Pixel getPixel (unsigned, unsigned) const;

    unsigned getWidth () const;

    unsigned getHeight () const; 

	private:
		unsigned width, height; // Image dimensions (pixels)

    vector<Pixel> pixels; 
};

#endif