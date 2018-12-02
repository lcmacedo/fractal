// Sistemas Operacionais - Trabalho 2
// Autor: Lucas Corrêa Macedo

#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
	public:
    Pixel ();

		Pixel (unsigned char, unsigned char, unsigned char);

		unsigned char getRed () const;

    unsigned char getGreen () const;

    unsigned char getBlue () const;

    void setRed (unsigned char );

    void setGreen (unsigned char );

    void setBlue (unsigned char );

    void setColor (unsigned char, unsigned char, unsigned char);

	private:
		unsigned char red, green, blue; // Color components
};

#endif