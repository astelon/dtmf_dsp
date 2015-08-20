/*
 * SignalAdder.h
 *
 *  Created on: 16 de ago. de 2015
 *      Author: Asteln
 */

#ifndef SIGNALADDER_H_
#define SIGNALADDER_H_

#include "ProcessingBlock.h"
#include <vector>

namespace Dsp {
typedef std::vector<float *> BufferList;

class SignalAdder : public ProcessingBlock {
public:
	SignalAdder();
	void addInput(float *buff);

	void process();
	virtual ~SignalAdder();

	float* getOutput() const;
	void setOutput(float* output);

protected:
	BufferList inputs;
	int addInputValues();
	float *output;
};
}

#endif /* SIGNALADDER_H_ */
