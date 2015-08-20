/*
 * Filter.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Filter.h"

using namespace Dsp;

Filter::Filter() {
	filterOrder = 6;
	filterGain = 154.3897897;
	mRingBufferInput = createRingBuffer(2*filterOrder);
	mRingBufferOutput = createRingBuffer(2*filterOrder);
	outputCoefficients = (double *)0;
	inputCoefficients = (double *)0;
}

Filter::~Filter() {
	destroyRingBuffer(mRingBufferInput);
	destroyRingBuffer(mRingBufferOutput);
}

void Filter::applyTo(float *in,float *out,unsigned long elements){
	for(unsigned long i=0; i<elements; i++ ) {
		write_buf(mRingBufferInput,in[i]/filterGain);
		out[i] = inputCoefficients[6] * relative_read(mRingBufferInput,-6) + inputCoefficients[5]*relative_read(mRingBufferInput,-5) +
				 inputCoefficients[4] * relative_read(mRingBufferInput,-4) + inputCoefficients[3]*relative_read(mRingBufferInput,-3) +
				 inputCoefficients[2] * relative_read(mRingBufferInput,-2) + inputCoefficients[1]*relative_read(mRingBufferInput,-1) +
				 inputCoefficients[0] * relative_read(mRingBufferInput,0) +
				( outputCoefficients[6] * relative_read(mRingBufferOutput,-6)) + (outputCoefficients[5] * relative_read(mRingBufferOutput,-5))+
				( outputCoefficients[4] * relative_read(mRingBufferOutput,-4))+ (outputCoefficients[3] * relative_read(mRingBufferOutput,-3)) +
				( outputCoefficients[2] * relative_read(mRingBufferOutput,-2)) + (outputCoefficients[1] * relative_read(mRingBufferOutput,-1));
		write_buf(mRingBufferOutput,out[i]);
		incr_ptr(mRingBufferInput);
		incr_ptr(mRingBufferOutput);
	}
}


/*
 // input  = {1,6,15,20,15,6,1}
 // output = {0,1.6301910568,-1.7736710308,1.0651269487,-0.4175206041,0.0901268112,0.0087883666 }
void Filter::applyTo(float *in,float *out,unsigned long elements){
	for(unsigned long i=0; i<elements; i++ ) {
		write_buf(mRingBufferInput,in[i]/filterGain);
		out[i] = relative_read(mRingBufferInput,-6) + 6*relative_read(mRingBufferInput,-5) + 15*relative_read(mRingBufferInput,-4) +
				20*relative_read(mRingBufferInput,-3) + 15*relative_read(mRingBufferInput,-2) + 6*relative_read(mRingBufferInput,-1) +
				relative_read(mRingBufferInput,0) +
				( -0.0087883666 * relative_read(mRingBufferOutput,-6)) + (0.0901268112 * relative_read(mRingBufferOutput,-5))+
				( -0.4175206041 * relative_read(mRingBufferOutput,-4))+ (1.0651269487 * relative_read(mRingBufferOutput,-3)) +
				( -1.7736710308 * relative_read(mRingBufferOutput,-2)) + (1.6301910568 * relative_read(mRingBufferOutput,-1));
		write_buf(mRingBufferOutput,out[i]);
		incr_ptr(mRingBufferInput);
		incr_ptr(mRingBufferOutput);
	}
}
*/

float Filter::getGain() const {
	return filterGain;
}

void Filter::setGain(float filterGain) {
	this->filterGain = filterGain;
}

void Filter::setInputCoefficients(double inputCoefficients[]) {
	this->inputCoefficients = inputCoefficients;
}

void Filter::setOutputCoefficients(double outputCoefficients[]) {
	this->outputCoefficients = outputCoefficients;
}
