/*
 * Plotter.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_
#include "Graphics.h"

namespace Graphics {

class Plotter {
public:
	Plotter();
	virtual ~Plotter();

	void plotChart(float *values,unsigned long framesPerBuffer,SDL_Surface *target);
	void setWorkingArea(SDL_Rect *rec,double xOffset, double yOffset, double w, double h);
	void plotValues(float *values,unsigned long framesPerBuffer,SDL_Surface *target);
protected:
	inline float getHighestValue(float *vals, unsigned long framesPerBuffer);
	Sint16 mXoffset; Sint16 mYoffset; double mWidth; double mHeight;
	SDL_Rect area;
};

} /* namespace Graphics */

#endif /* PLOTTER_H_ */
