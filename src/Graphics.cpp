/*
 * Graphics.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Graphics.h"
#include "Logger.h"

namespace Graphics {
	SDL_Surface* screen = NULL;

	SDL_Surface *getScreen(){
		return screen;
	}

	void startGraphicsSystem(int w, int h){
		screen = NULL;
		Logger::logInfo("Starting SDL...") << std::endl;
		SDL_Init( SDL_INIT_EVERYTHING );
		screen = SDL_SetVideoMode( w, h, 32, SDL_SWSURFACE );
		SDL_WM_SetCaption("Proyecto PDS", "Proyecto PDS");
		if (screen == NULL){
			Logger::logError("Screen is NULL -> SDL Error: ") << SDL_GetError() << std::endl;
		}
		TTF_Init();

	}

	void stopGraphicsSystem(){
		 TTF_Quit();
		 SDL_Quit();
	}
	void blitToScreen(SDL_Surface *source, SDL_Rect *src_rect, SDL_Rect *dest_location ){
		SDL_BlitSurface(source, src_rect, screen, dest_location );
	}
	void flipBuffer(){
		SDL_Flip( screen );
	}
	void fillRect(SDL_Surface *target, SDL_Rect *area, Uint8 r, Uint8 g, Uint8 b){
		if (target==NULL) target = screen;
		if (screen==NULL) Logger::logError("Screen is null in fillRect") << std::endl;
		SDL_FillRect(target, area, SDL_MapRGB(screen->format, r, g, b));
	}
}
