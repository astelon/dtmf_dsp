/*
 * GoertzelFilter.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#include "GoertzelDetector.h"

#include "Logger.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Dsp {

GoertzelDetector::GoertzelDetector() : detectionCount(0), N(0), f(0), input(0), samplingRate(0.0),  targetFrequency(0.0),  detection(false), coeff(0.0), Q1(0.0), Q2(0.0), sine(0.0), cosine(0.0) {
	// TODO Auto-generated constructor stub

}

GoertzelDetector::~GoertzelDetector() {
	// TODO Auto-generated destructor stub
}

float GoertzelDetector::getMagnitudeSquared(void)
{
  float result;

  result = Q1 * Q1 + Q2 * Q2 - Q1 * Q2 * coeff;
  return result;
}

void GoertzelDetector::init(void)
{
  int	k;
  float	floatN;
  float	omega;

  floatN = (float) N;
  k = (int) (0.5 + ((floatN * targetFrequency) / samplingRate));
  omega = (2.0 * M_PI * k) / floatN;
  sine = sin(omega);
  cosine = cos(omega);
  coeff = 2.0 * cosine;

#ifdef DEBUG_INFO
  Logger::logInfo("At GoertzelDetector::Init") << std::endl;
  Logger::logInfo("For SAMPLING_RATE = ") << samplingRate <<
  " N = " << N << " and FREQUENCY = " << targetFrequency << std::endl;
  Logger::logInfo("k = ") << k << " and coeff = " << coeff << std::endl << std::endl;
#endif

  detection = false;
  preProcess();
}

void GoertzelDetector::preProcess(void)
{
  Q2 = 0;
  Q1 = 0;
}

void GoertzelDetector::setFramesPerBuffer(int n) {
	N=n;
}

void GoertzelDetector::setSamplingRate(float samplingRate) {
	this->samplingRate = samplingRate;
}

void GoertzelDetector::setTargetFrequency(float targetFrequency) {
	this->targetFrequency = targetFrequency;
}

void GoertzelDetector::setInput(float* input) {
	this->input = input;
}

void GoertzelDetector::process() {
	  float Q0;
	  Q0 = coeff * Q1 - Q2 + (float) *input;
	  Q2 = Q1;
	  Q1 = Q0;
}

void GoertzelDetector::postProcess() {
	float magnitude = sqrt( getMagnitudeSquared() );
	if (magnitude >= DETECTION_THRESHOLD) detectionCount++;
	if (detectionCount >= DETECTION_COUNT_TARGET) detection = true;
	//Logger::logInfo("Magnitude = ") << magnitude << " detCount = " << detectionCount << std::endl;
}

bool GoertzelDetector::detected() {
	return detection;
}

void GoertzelDetector::clearDetectionFlag() {
	detection = false;
	detectionCount = 0;
}

} /* namespace Dsp */
