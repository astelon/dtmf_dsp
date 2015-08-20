/*
 * TextPrinter.h
 *
 *  Created on: 26 de jul. de 2015
 *      Author: Asteln
 */

#ifndef GRAPHICS_TEXTPRINTER_H_
#define GRAPHICS_TEXTPRINTER_H_

#include "Graphics.h"
#include <sstream>

namespace Graphics {

class TextPrinter {
public:
	TextPrinter();
	TextPrinter &position(Uint16 x, Uint16 y);
	TextPrinter &color(Uint8 r, Uint8 g, Uint8 b);
	TextPrinter &operator<<(std::string str);
	TextPrinter &operator<<(int i);
	virtual ~TextPrinter();
	operator SDL_Surface*();
	void blit(SDL_Surface *target=NULL);
	TextPrinter &clear();
	TextPrinter &append(std::string str);
	TextPrinter &appendi(int i);
	TextPrinter &appendf(float f);
	TextPrinter &text(std::string str);
	TextPrinter &render();
	TextPrinter &font(const char* font_name,int size);
protected:
	std::stringstream str;
	TTF_Font *mFont;
	SDL_Surface *message;
	SDL_Rect area;
	SDL_Color textColor;
};

} /* namespace Graphics */

#endif /* GRAPHICS_TEXTPRINTER_H_ */
