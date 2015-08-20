/*
 * Modulator.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Modulator.h"

using namespace Dsp;

Modulator::Modulator() : mOscilator(0) {
	// TODO Auto-generated constructor stub

}

Modulator::~Modulator() {
	// TODO Auto-generated destructor stub
}

void Modulator::setOscilator(Oscilator* oscilator) {
	mOscilator = oscilator;
}

void Modulator::applyTo(float *in, float *out, unsigned long elements){
	for(unsigned long i=0; i<elements; i++ ) {
		mOscilator->increaseTime();
		out[i] = in[i] * mOscilator->getCurrentValue();
	}
}
