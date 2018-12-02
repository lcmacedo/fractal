// Sistemas Operacionais - Trabalho 2
// Autor: Lucas Corrêa Macedo

#include "Pixel.h"
#include "Image.h"

Image::Image (unsigned _width, unsigned _height)
  : width (_width), height (_height), pixels (_width * _height)
{ }

void Image::setPixel (unsigned row, unsigned col, Pixel &pixel)
{
  pixels.at (row * width + col) = pixel;
}

Pixel Image::getPixel (unsigned row, unsigned col) const
{
  return pixels.at (row * width + col);
}

unsigned Image::getWidth () const { return width; }

unsigned Image::getHeight () const { return height; }

ostream &operator<< (ostream &out, const Image &image)
{
  unsigned x, y;

  out << "P6" << endl << image.getWidth () << " " << image.getHeight () << endl << 255 << endl; // Header

  for (y = 0; y < image.getHeight (); y++)
    for (x = 0; x < image.getWidth (); x++) 
        out << image.getPixel (y, x).getRed () << image.getPixel (y, x).getGreen () << image.getPixel (y, x).getBlue ();
      
  return out;
}