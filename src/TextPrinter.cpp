/*
 * TextPrinter.cpp
 *
 *  Created on: 26 de jul. de 2015
 *      Author: Asteln
 */

#include "TextPrinter.h"
#include "Logger.h"

extern "C" {
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>
}

namespace Graphics {

TextPrinter &TextPrinter::color(Uint8 r, Uint8 g, Uint8 b){
	textColor.r = r; textColor.g = g; textColor.b = b;
	return *this;
}

TextPrinter &TextPrinter::appendi(int i){
	str << i;
	return *this;
}
TextPrinter &TextPrinter::appendf(float f){
	str << f;
	return *this;
}

TextPrinter::TextPrinter() : str("",std::ios_base::app | std::ios_base::out) {
	// TODO Auto-generated constructor stub
	textColor.r = 255; textColor.g = 255; textColor.b = 255;
	area.x = 0;	area.y = 0;
	area.h = 0;
	area.w = 0;
	message = NULL;
	mFont = NULL;
	font("arial.ttf",14);
}

TextPrinter::~TextPrinter() {
	// TODO Auto-generated destructor stub
	SDL_FreeSurface(message);
	message = 0;
}

TextPrinter &TextPrinter::position(Uint16 x, Uint16 y){
	area.x = x;	area.y = y;
	return *this;
}

TextPrinter &TextPrinter::operator<<(std::string s){
	str << s;
	return *this;
}

TextPrinter &TextPrinter::operator<<(int i){
	str << i;
	return *this;
}

TextPrinter::operator SDL_Surface*(){
	SDL_Surface* tmp = message;
	message = NULL;
	return tmp;
}

TextPrinter &TextPrinter::render(){
	if(message != NULL) SDL_FreeSurface(message);
	message = TTF_RenderText_Solid( mFont, str.str().c_str(), textColor );
	return *this;
}

TextPrinter &TextPrinter::append(std::string st){
	str << st;
	return *this;
}

TextPrinter &TextPrinter::text(std::string st){
	str.str(st);
	return *this;
}

TextPrinter &TextPrinter::clear(){
	str.str("");
	if(message != NULL) SDL_FreeSurface(message);
	return *this;
}

void TextPrinter::blit(SDL_Surface *target){
	if(message==NULL) return;
	if(target==NULL) target = Graphics::getScreen();
	SDL_BlitSurface(message, NULL, target, &area );
}

TextPrinter &TextPrinter::font(const char* font_name,int size) {
	if(mFont != 0) TTF_CloseFont(mFont);
	mFont =  TTF_OpenFont( font_name, size );
	if(mFont == NULL) Logger::logError("Font is currently NULL!!!!!!!") << std::endl;
	return *this;
}

} /* namespace Graphics */


