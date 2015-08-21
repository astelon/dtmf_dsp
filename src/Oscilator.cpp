/*
 * Oscilator.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Oscilator.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Dsp;

Oscilator::Oscilator(double f) : output(0), mGain(1), sampleTimeout(0) {
	mFrequency = f; time = 0; mDeltaTime = 1;
}

Oscilator::Oscilator() : output(0), mGain(1), sampleTimeout(0) {
	mFrequency = 0; time = 0; mDeltaTime = 1;
}

Oscilator::~Oscilator() {
}

float Oscilator::getCurrentValue(){
	return (mGain * sin(time*2*M_PI*mFrequency));
}

double Oscilator::getFrequency() const {
	return mFrequency;
}

void Oscilator::setFrequency(double frequency) {
	mFrequency = frequency;
}

void Oscilator::setSampleRate(double sampleRate) {
	mDeltaTime = 1/sampleRate;
}

void Oscilator::increaseTime(){
	time += mDeltaTime;
	if (sampleTimeout == 0) return;
	sampleTimeout -= 1;
	if (sampleTimeout == 0) setEnabled(false);
}

double Oscilator::getTime() const {
	return time;
}

void Oscilator::setTime(double time) {
	this->time = time;
}

void Oscilator::process(){
	if (!enabled) {
		*output = 0.0;
		return;
	}
		*output = getCurrentValue();
		increaseTime();
}

double Oscilator::getGain() const {
	return mGain;
}

void Oscilator::setGain(double gain) {
	mGain = gain;
}

float* Oscilator::getOutput() const {
	return output;
}

void Oscilator::setOutput(float* output) {
	this->output = output;
}

void Oscilator::setTimeOut(unsigned long samples) {
	sampleTimeout = samples;
}
