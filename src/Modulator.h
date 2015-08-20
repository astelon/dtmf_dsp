/*
 * Modulator.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef MODULATOR_H_
#define MODULATOR_H_

#include "Oscilator.h"

namespace Dsp {

class Modulator {
public:
	Modulator();
	virtual ~Modulator();
	void setOscilator(Oscilator* oscilator);
	void applyTo(float *in,float *out,unsigned long elements);

protected:
	Oscilator *mOscilator;
};

}
#endif /* MODULATOR_H_ */
