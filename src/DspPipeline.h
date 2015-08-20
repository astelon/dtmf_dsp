/*
 * DspPipeline.h
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#ifndef DSPPIPELINE_H_
#define DSPPIPELINE_H_

#include <vector>
#include "ProcessingBlock.h"

namespace Dsp {

extern "C" {
	#include <portaudio.h>
}

class DspPipeline {
public:
	typedef std::vector<ProcessingBlock*> ProcessingBlockList;
	DspPipeline();
	virtual ~DspPipeline();
	void addBlock(ProcessingBlock *block);
	void preProcess();
	void process();
	void postProcess();
	void setInput(float val);
	void setInputVarPtr(float* input);
	void setOutputVarPtr(float* output);
	float getOutput();
	bool validInputVar();
	bool validOutputVar();
protected:
	ProcessingBlockList processingBlocks;
	float *input;
	float *output;
};

} /* namespace Dsp */

#endif /* DSPPIPELINE_H_ */
