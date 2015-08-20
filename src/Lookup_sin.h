/*
 * Oscilator.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef LOOKUP_SIN_H_
#define LOOKUP_SIN_H

#include "Oscilator.h"

namespace Dsp {
class lookup_sin : public Oscilator {
public:
	lookup_sin();
	lookup_sin(double frequency);
	float getCurrentValue();
	void increaseTime();

	virtual ~lookup_sin();
protected:
	double mDeltaT;
	double Phase;
};
}
#endif /* LOOKUP_SIN_H */
