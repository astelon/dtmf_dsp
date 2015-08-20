/*
 * main.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include <iostream>

using namespace std;

#include "FFT.h"
#include <sstream>

#include "Filter.h"
#include "Modulator.h"
#include "Lookup_sin.h"

#include <stdio.h>
#include <stdlib.h>

#include "Audio.h"
#include "Graphics.h"
#include "Plotter.h"
#include "TextPrinter.h"
#include "SignalAdder.h"
#include "DspPipeline.h"
#include "GoertzelDetector.h"

#include "Logger.h"

#define FFT_ZERO_PADDING 16
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER 1024

class DtmfPipeline : public Dsp::DspPipeline
{
	protected:
	inline void configureDetector(float t_freq, Dsp::GoertzelDetector *ptr){
		if (ptr == (Dsp::GoertzelDetector *)0) return;

		ptr->setFramesPerBuffer( FRAMES_PER_BUFFER );
		ptr->setSamplingRate( SAMPLE_RATE );
		ptr->setTargetFrequency(t_freq);
		ptr->setInput(&adder1Output);
		ptr->init();
	}
public:
	static const float DtmfRows[];
	static const float DtmfCols[];

	DtmfPipeline() : Dsp::DspPipeline(), toneGeneratorRow(), toneGeneratorCol(), signalAdder1(), adder1Output(0.0), toneGenRowOut(0.0), toneGenColOut(0.0) {

	}

	void prepare(){
		SETUP_OSCILLATOR(toneGeneratorRow, 1.0, 697, SAMPLE_RATE);
		SETUP_OSCILLATOR(toneGeneratorCol, 0.1, 1209, SAMPLE_RATE);
		toneGeneratorRow.setOutput(&toneGenRowOut);
		toneGeneratorRow.setFrequency(DtmfRows[0]);

		toneGeneratorCol.setOutput(&toneGenColOut);
		toneGeneratorCol.setFrequency(DtmfCols[0]);

		signalAdder1.addInput(&toneGenRowOut);
		signalAdder1.addInput(&toneGenColOut);
		signalAdder1.setOutput(&adder1Output);

		addBlock(&toneGeneratorRow);
		addBlock(&toneGeneratorCol);
		addBlock(&signalAdder1);

		setOutputVarPtr(&adder1Output);

		//Configure detectors
		for (int i=0; i<4; i++) {
			configureDetector(DtmfRows[i],&rowDetectors[i]);
			addBlock(&rowDetectors[i]);
			configureDetector(DtmfCols[i],&colDetectors[i]);
			addBlock(&colDetectors[i]);
		}
	}
//protected:
	Dsp::Oscilator toneGeneratorRow, toneGeneratorCol;
	Dsp::SignalAdder signalAdder1;

	//Create Detector for each row and column

	Dsp::GoertzelDetector rowDetectors[4]; //RowDetectors
	Dsp::GoertzelDetector colDetectors[4]; //ColDetectors

	float adder1Output, toneGenRowOut, toneGenColOut;

};

const float DtmfPipeline::DtmfRows[] = {697,770,852,941};
const float DtmfPipeline::DtmfCols[] = {1209,1336,1477,1633};

int main(int argc, char *argv[]) {

	Logger::logInfo("Starting application...\n");
	DtmfPipeline pipe;

	Graphics::startGraphicsSystem(1200,768);
	Fft::prepareFft();

	pipe.prepare();

	Audio::startAudioSystem(SAMPLE_RATE,FRAMES_PER_BUFFER,&pipe);

	Pa_Sleep(1500);

	if(pipe.rowDetectors[0].detected()) Logger::logInfo("Row1 was detected!!!!");
	else Logger::logError("Row1 not detected!!!!");

	pipe.rowDetectors[0].clearDetectionFlag();

	Fft::CleanupFft();

    Graphics::stopGraphicsSystem();
    Audio::terminatePortAudio();
	return 0;
}

