/*
 * Filter.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef FILTER_H_
#define FILTER_H_

extern "C" {
	#include "ring_buff.h"
}

#include <vector>

namespace Dsp {
class Filter {
public:
	typedef std::vector<double> CoefficientList;

	Filter();
	virtual ~Filter();
	void applyTo(float *in,float *out,unsigned long elements);
	void setOutputCoefficients(double outputCoefficients[]);
	void setInputCoefficients(double inputCoefficients[]);
	float getGain() const;
	void setGain(float filterGain);

	protected:
	double *outputCoefficients;
	double *inputCoefficients;

	ringBuf *mRingBufferInput;
	ringBuf *mRingBufferOutput;
	unsigned long filterOrder;
	float filterGain;
};

#define SETUP_FILTER(name,inputs,outputs,gain) name.setInputCoefficients(inputs); name.setOutputCoefficients(outputs); name.setGain(gain)

}
#endif /* FILTER_H_ */
