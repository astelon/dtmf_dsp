/*
 * DspPipeline.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#include "DspPipeline.h"
#include "Logger.h"

namespace Dsp {

DspPipeline::DspPipeline() : processingBlocks(), input(0), output(0) {
	// TODO Auto-generated constructor stub

}

DspPipeline::~DspPipeline() {
	// TODO Consider freeing all elements in the pipeline or using references instead of pointers
}

void DspPipeline::addBlock(ProcessingBlock* block) {
	if (block == (ProcessingBlock*)0) return;
	processingBlocks.push_back(block);
}

void DspPipeline::process() {
	ProcessingBlockList::iterator itr;
	for(itr=processingBlocks.begin(); itr!=processingBlocks.end(); itr++)
		(*itr)->process();
}


void DspPipeline::setInputVarPtr(float *in) {
	this->input = in;
}

bool DspPipeline::validInputVar() { return (input != (float*)0); }
bool DspPipeline::validOutputVar() { return (output != (float*)0); }

void DspPipeline::setOutputVarPtr(float *out) {
	this->output = out;
}

void DspPipeline::setInput(float val) {
	*input = val;
}

float DspPipeline::getOutput() {
	return *output;
}

void DspPipeline::preProcess() {
	ProcessingBlockList::iterator itr;
	for(itr=processingBlocks.begin(); itr!=processingBlocks.end(); itr++)
		(*itr)->preProcess();
}

void DspPipeline::postProcess() {
	ProcessingBlockList::iterator itr;
	for(itr=processingBlocks.begin(); itr!=processingBlocks.end(); itr++)
		(*itr)->postProcess();
}

} /* namespace Dsp */

void Dsp::DspPipeline::prepare() {
}
