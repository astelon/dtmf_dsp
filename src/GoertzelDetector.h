/*
 * GoertzelDetector.h
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#ifndef GOERTZELDETECTOR_H_
#define GOERTZELDETECTOR_H_

#include "ProcessingBlock.h"
#include <vector>
namespace Dsp {

typedef std::vector<unsigned short> DetectedIdList;

class GoertzelDetector : public ProcessingBlock {
public:
	GoertzelDetector();
	virtual ~GoertzelDetector();

	void init();
	void setFramesPerBuffer(int n);
	void preProcess(void);
	void setSamplingRate(float samplingRate);
	void setTargetFrequency(float targetFrequency);
	void setInput(float* input);
	void process();
	float getMagnitudeSquared(void);
	void postProcess();
	bool detected();
	void clearDetectionFlag();
	void setDetectedIdList(DetectedIdList *dList);
	void setId(unsigned short n);

protected:
	DetectedIdList *detectedIdList;
	unsigned short id;
	unsigned long N;
	float f;
	float *input;
	float samplingRate;
	float targetFrequency;
	bool detection;
	unsigned long detectionCount;
	unsigned long clearCount;
	static const unsigned long DETECTION_COUNT_TARGET = 8;
	static const float DETECTION_THRESHOLD = 45;
	float coeff;
	float Q1;
	float Q2;
	float sine;
	float cosine;
};

} /* namespace Dsp */

#endif /* GOERTZELDETECTOR_H_ */
