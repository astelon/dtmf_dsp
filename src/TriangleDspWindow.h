/*
 * TriangleDspWindow.h
 *
 *  Created on: Aug 21, 2015
 *      Author: astelon
 */

#ifndef TRIANGLEDSPWINDOW_H_
#define TRIANGLEDSPWINDOW_H_

#include "ProcessingBlock.h"

namespace Dsp {

class TriangleDspWindow : public ProcessingBlock {
public:
	TriangleDspWindow();
	void preProcess();
	void process();
	void postProcess();
	virtual ~TriangleDspWindow();
	void setInput(float* input);
	void setOutput(float* output);
	void setToneDuration(unsigned long duration);
	void setEnabled(bool en);
protected:
	unsigned long sampleIdx;
	unsigned long toneLenght;
	unsigned long halfWay;
	float increment;
	float coeficient;
	float *input;
	float *output;

};

}

#endif /* TRIANGLEDSPWINDOW_H_ */
