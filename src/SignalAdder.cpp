/*
 * SignalAdder.cpp
 *
 *  Created on: 16 de ago. de 2015
 *      Author: Asteln
 */

#include "SignalAdder.h"

using namespace Dsp;
SignalAdder::SignalAdder() : output(0) {
	// TODO Auto-generated constructor stub

}

SignalAdder::~SignalAdder() {
	// TODO Auto-generated destructor stub
}

void SignalAdder::addInput(float *buff){
	inputs.push_back(buff);
}

float* SignalAdder::getOutput() const {
	return output;
}

void SignalAdder::setOutput(float* output) {
	this->output = output;
}

int SignalAdder::addInputValues(){
	BufferList::iterator itr;
	float result = 0.0;
	for ( itr = inputs.begin(); itr != inputs.end(); itr++ ) {
		result += *(*itr);
	}
	return result;
}

void SignalAdder::process(){
	*output = addInputValues();
}
