/*
 * DtmfPipeline.h
 *
 *  Created on: Aug 20, 2015
 *      Author: astelon
 */

#ifndef DTMFPIPELINE_H_
#define DTMFPIPELINE_H_

#include "DspPipeline.h"
#include "GoertzelDetector.h"
#include "Oscilator.h"
#include "SignalAdder.h"
#include "TriangleDspWindow.h"

namespace Dsp {

class DtmfPipeline : public DspPipeline
{
	protected:
	inline void configureDetector(float *in, float t_freq, unsigned short id, DetectedIdList *list, GoertzelDetector *ptr);

public:
	static const float DtmfRows[];
	static const float DtmfCols[];

	DtmfPipeline();

	void prepare();
	void enableOscilators(bool en=true);
	bool symbolDetected();

//protected:
	Oscilator toneGeneratorRow, toneGeneratorCol;
	TriangleDspWindow window;
	SignalAdder signalAdder1;

	//Create Detector for each row and column
	GoertzelDetector rowDetectors[4]; //RowDetectors
	GoertzelDetector colDetectors[4]; //ColDetectors

	DetectedIdList rowIdsDetected;
	DetectedIdList colIdsDetected;

	float adder1Output, toneGenRowOut, toneGenColOut, windowOut;
	float systemInput;
};

}

#endif /* DTMFPIPELINE_H_ */
