/*
 * Plotter.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Plotter.h"
#include "Logger.h"

namespace Graphics {

Plotter::Plotter() : mXoffset(0), mYoffset(0), mWidth(1), mHeight(1) {
}

Plotter::~Plotter() {
}

void Plotter::plotValues(float *values,unsigned long framesPerBuffer,SDL_Surface *target){
	if(target==NULL) target = Graphics::getScreen();
	double columnWidth, x, nx;
	float  maxValue;
	SDL_Rect barArea = {0,0,0,0};
	columnWidth = (mWidth*(double)area.w/(double)framesPerBuffer);

	framesPerBuffer /= 2;
	framesPerBuffer++;

	Sint16 baseY = area.y+mYoffset + (Sint16)(((double)area.h)*mHeight);
	Uint16 plotAreaWidth = (Uint16)(((double)area.w)*mWidth);

	x = area.x + mXoffset + plotAreaWidth/2;

	nx = area.x + mXoffset + (Sint16)plotAreaWidth/2-(Sint16)columnWidth-1;

	Sint16 baseX = (Sint16)(area.x+mXoffset-(Sint16)1);
	SDL_Rect hLineArea = { (Sint16)baseX,(Sint16)(baseY),plotAreaWidth,(Uint16)1};
	SDL_Rect vLineArea = { (Sint16)((baseX-(Sint16)1)+(Sint16)((Sint16)plotAreaWidth/(Sint16)2)),
			(Sint16)(area.y+mYoffset),(Uint16)1,(Uint16)(((double)area.h)*mHeight)};

	SDL_FillRect(target, &area, SDL_MapRGB(Graphics::getScreen()->format, 255, 255, 255));

	maxValue = getHighestValue(values,framesPerBuffer);

	for(unsigned int i = 0; i < framesPerBuffer; i++){
		float normalizedValue = (values[i]/maxValue)*mHeight;
		barArea.w = (Uint16)(columnWidth);
		barArea.h = (Uint16)(normalizedValue*area.h);
		barArea.y = (Sint16) baseY-barArea.h;
		barArea.x = (Sint16) x;
		x += columnWidth;
		SDL_FillRect(target, &barArea, SDL_MapRGB(Graphics::getScreen()->format, 255, 0, 0));
		barArea.x = (Sint16) nx;
		nx -= columnWidth;
		SDL_FillRect(target, &barArea, SDL_MapRGB(Graphics::getScreen()->format, 255, 0, 0));
	}

	SDL_FillRect(target, &hLineArea, SDL_MapRGB(Graphics::getScreen()->format, 0, 0, 255));
	SDL_FillRect(target, &vLineArea, SDL_MapRGB(Graphics::getScreen()->format, 0, 0, 255));
}

void Plotter::plotChart(float *values, unsigned long framesPerBuffer, SDL_Surface *target){
	if(target==NULL) target = Graphics::getScreen();
	SDL_Rect hLineArea = {area.x,area.y,area.w,1};
	SDL_Rect vLineArea = {area.x,area.y,1,area.h};

	SDL_FillRect(target, &area, SDL_MapRGB(Graphics::getScreen()->format, 255, 255, 255));
	SDL_FillRect(target, &hLineArea, SDL_MapRGB(Graphics::getScreen()->format, 0, 0, 255));
	SDL_FillRect(target, &vLineArea, SDL_MapRGB(Graphics::getScreen()->format, 0, 0, 255));

//	plotValues(values,framesPerBuffer,target,area);
}

inline float Plotter::getHighestValue(float *vals, unsigned long framesPerBuffer){
	float higher = vals[0];
	for(unsigned int i = 0; i< framesPerBuffer; i++) if (vals[i] > higher) higher = vals[i];
	return higher;
}

void Plotter::setWorkingArea(SDL_Rect *rec, double xOffset, double yOffset, double w, double h){
	area.x = rec->x; area.y = rec->y; area.w = rec->w; area.h = rec->h;
	mXoffset = (Sint16) (xOffset * area.w);
	mYoffset = (Sint16) (yOffset * area.h);
	mWidth = w;
	mHeight = h;
}

} /* namespace Graphics */
