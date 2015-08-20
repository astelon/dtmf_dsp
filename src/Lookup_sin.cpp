/*
 * Oscilator.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Lookup_sin.h"
#include "sin_array.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Dsp;

lookup_sin::lookup_sin(double f) : Oscilator() {
	mFrequency = f; time = 0; mDeltaT = 1; mGain = 1;Phase = 0;
}

lookup_sin::lookup_sin() : Oscilator() {
	mFrequency = 0; time = 0; mDeltaT = 1; mGain = 1;Phase = 0;
}

lookup_sin::~lookup_sin() {
}

float lookup_sin::getCurrentValue(){

	int phase_i = (int)Phase;
	double out = sin_LU[phase_i];
	Phase += mFrequency;
			if (Phase >= (float)LU_lenght)    // handle wraparound
				Phase -= (float)LU_lenght;
	return (out);
}

void lookup_sin::increaseTime(){
}


