// Sistemas Operacionais - Trabalho 2
// Autor: Lucas Corrêa Macedo

#include "Pixel.h"

using namespace std; 

Pixel::Pixel ()
{
  setColor (0, 0, 0);
}

Pixel::Pixel (unsigned char _red, unsigned char _green, unsigned char _blue)
{
  setColor (_red, _green, _blue);
}

unsigned char Pixel::getRed () const { return red; }

unsigned char Pixel::getGreen () const { return green; }

unsigned char Pixel::getBlue () const {  return blue; }

void Pixel::setRed (unsigned char r) { red = (r > 255) ? 255 : r; }

void Pixel::setGreen (unsigned char g) { green = (g > 255) ? 255 : g; }

void Pixel::setBlue (unsigned char b) { blue = (b > 255) ? 255 : b; }
 
void Pixel::setColor (unsigned char r, unsigned char g, unsigned char b)
{
  setRed (r);
  setGreen (g);
  setBlue (b);
}
