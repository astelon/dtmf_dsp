/*
 * Oscilator.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef OSCILATOR_H_
#define OSCILATOR_H_
#include "ProcessingBlock.h"

namespace Dsp {
class Oscilator : public ProcessingBlock {
public:
	Oscilator();
	Oscilator(double frequency);
	float getCurrentValue();
	void increaseTime();

	virtual ~Oscilator();

	double getFrequency() const;
	void setFrequency(double frequency);

	void setSampleRate(double sampleRate);

	double getTime() const;
	void setTime(double time);

	void process();

	double getGain() const;

	void setGain(double gain);

	float* getOutput() const;
	void setOutput(float* output);

	void setTimeOut(unsigned long samples);

protected:
	double mDeltaTime;
	double mFrequency;
	double time;
	double mGain;
	float *output;
	unsigned long sampleTimeout;
};

#define SETUP_OSCILLATOR(name,g,f,s) name.setGain(g); name.setFrequency(f); name.setSampleRate(s);

}
#endif /* OSCILATOR_H_ */
