/*
 * Graphics.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

extern "C" {
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>
}

namespace Graphics {
	void startGraphicsSystem(int width, int height);
	void stopGraphicsSystem();
	void blitToScreen(SDL_Surface *source, SDL_Rect *src_rect, SDL_Rect *textLocation );
	void flipBuffer();
	void fillRect(SDL_Surface *target, SDL_Rect *area, Uint8 r, Uint8 g, Uint8 b );
	SDL_Surface *getScreen();
}

#endif /* GRAPHICS_H_ */
