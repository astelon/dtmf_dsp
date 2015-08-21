/*
 * TriangleDspWindow.cpp
 *
 *  Created on: Aug 21, 2015
 *      Author: astelon
 */

#include "TriangleDspWindow.h"
#include "Audio.h"

using namespace Dsp;

TriangleDspWindow::TriangleDspWindow() : sampleIdx(0), samplesPerFrame(1), coeficient(0), input(0), output(0) {
	// TODO Auto-generated constructor stub
	samplesPerFrame = Audio::getFramesPerBuffer();
	increment = 2.0f/samplesPerFrame;
	halfWay = samplesPerFrame/2;
}

TriangleDspWindow::~TriangleDspWindow() {
	// TODO Auto-generated destructor stub
}

void TriangleDspWindow::preProcess() {
	coeficient = 0;
	sampleIdx=0;
}

void TriangleDspWindow::process() {
	(*output) = (*input) * coeficient;

	if(sampleIdx < halfWay)
		coeficient+=increment;
	else
		coeficient-=increment;

	if(coeficient < 0.0) coeficient = 0.0;

	sampleIdx++;
}

void TriangleDspWindow::postProcess() {
}

void Dsp::TriangleDspWindow::setInput(float* input) {
	this->input = input;
}

void Dsp::TriangleDspWindow::setOutput(float* output) {
	this->output = output;
}
