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

typedef enum {
	ROW1=697,
	ROW2=770,
	ROW3=852,
	ROW4=941
} DtmfRows;

typedef enum {
	COL1=1209,
	COL2=1336,
	COL3=1477,
	COL4=1633
} DtmfCols;


typedef struct
{
    int N;

	float system_in[FRAMES_PER_BUFFER+FFT_ZERO_PADDING];
	float system_out[FRAMES_PER_BUFFER+FFT_ZERO_PADDING];
	float toneGen1Out, toneGen2Out, adder1Output;

	Dsp::Oscilator toneGenerator1;
	Dsp::Oscilator toneGenerator2;
	Dsp::SignalAdder signalAdder1;
	Dsp::DspPipeline pipeline1;
	Dsp::GoertzelDetector row1Detector;

//	Fft *fft_in;
//	Fft *fft_out;
} DspPipeline_s;

void setDtmfOutput(DtmfRows row,DtmfCols col, DspPipeline_s *pipe){
	pipe->toneGenerator1.setFrequency(row);
	pipe->toneGenerator2.setFrequency(col);
}

#define SETUP_FILTER(name,inputs,outputs,gain) name.setInputCoefficients(inputs); name.setOutputCoefficients(outputs); name.setGain(gain)
#define SETUP_OSCILLATOR(name,g,f,s) name.setGain(g); name.setFrequency(f); name.setSampleRate(s);

void prepareDspPipeline(DspPipeline_s& data) {
	data.N = FRAMES_PER_BUFFER;

	SETUP_OSCILLATOR(data.toneGenerator1, 1.0, 697, SAMPLE_RATE);
	SETUP_OSCILLATOR(data.toneGenerator2, 0.1, 1209, SAMPLE_RATE);
	data.toneGenerator1.setOutput(&data.toneGen1Out);
	data.toneGenerator2.setOutput(&data.toneGen2Out);
	setDtmfOutput(ROW1,COL3,&data);

	data.signalAdder1.addInput(&data.toneGen1Out);
	data.signalAdder1.addInput(&data.toneGen2Out);
	data.signalAdder1.setOutput(&data.adder1Output);

	data.row1Detector.setFramesPerBuffer(FRAMES_PER_BUFFER);
	data.row1Detector.setSamplingRate(SAMPLE_RATE);
	data.row1Detector.setTargetFrequency(ROW1);
	data.row1Detector.setInput(&data.adder1Output);
	data.row1Detector.init();

	//PREPARE FFT variables
/*	memset((void *)data.system_in,0,sizeof(float)*FRAMES_PER_BUFFER+FFT_ZERO_PADDING+1);
	memset((void *)data.system_out,0,sizeof(float)*FRAMES_PER_BUFFER+FFT_ZERO_PADDING+1);

	data.fft_in = new Fft(SAMPLE_RATE, FRAMES_PER_BUFFER+FFT_ZERO_PADDING, data.system_in);
	data.fft_out = new Fft(SAMPLE_RATE, FRAMES_PER_BUFFER+FFT_ZERO_PADDING, data.system_out);*/

	data.pipeline1.addBlock(&data.toneGenerator1);
	data.pipeline1.addBlock(&data.toneGenerator2);
	data.pipeline1.addBlock(&data.signalAdder1);
	data.pipeline1.setOutputVarPtr(&data.adder1Output);
	data.pipeline1.addBlock(&data.row1Detector);
}

int main(int argc, char *argv[]) {

	Logger::logInfo("Starting application...\n");
	DspPipeline_s data;

	Graphics::startGraphicsSystem(1200,768);
	Fft::prepareFft();

	prepareDspPipeline(data);

	Audio::startAudioSystem(SAMPLE_RATE,FRAMES_PER_BUFFER,&(data.pipeline1));

	Pa_Sleep(1500);

	if(data.row1Detector.detected()) Logger::logInfo("Row1 was detected!!!!");
	else Logger::logError("Row1 not detected!!!!");

	data.row1Detector.clearDetectionFlag();

//	delete data.fft_in;
//	delete data.fft_out;

	Fft::CleanupFft();

    Graphics::stopGraphicsSystem();
    Audio::terminatePortAudio();
	return 0;
}



