/*
 * TriangleDspWindow.cpp
 *
 *  Created on: Aug 21, 2015
 *      Author: astelon
 */

#include "TriangleDspWindow.h"
#include "Audio.h"

using namespace Dsp;

TriangleDspWindow::TriangleDspWindow() : sampleIdx(0), toneLenght(1), coeficient(0), input(0), output(0), increment(0.0), halfWay(0.0) {
	// TODO Auto-generated constructor stub
	enabled = false;
}

TriangleDspWindow::~TriangleDspWindow() {
	// TODO Auto-generated destructor stub
}

void TriangleDspWindow::preProcess() {
}

void TriangleDspWindow::process() {
	if(!enabled) {
		(*output) = 0.0; //Change to 0 later
	}

	(*output) = (*input) * coeficient;

	if(sampleIdx < halfWay)
		coeficient+=increment;
	else
		coeficient-=increment;

	if(coeficient < 0.0) {
		coeficient = 0.0;
		enabled = false;
	}

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

void Dsp::TriangleDspWindow::setToneDuration(unsigned long duration) {
	toneLenght = duration;
	increment = 2.0f/toneLenght;
	halfWay = toneLenght/2;
}

void Dsp::TriangleDspWindow::setEnabled(bool en) {
	enabled = true;
	coeficient = 0;
	sampleIdx=0;
}


