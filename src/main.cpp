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
#include "DtmfPipeline.h"
#include "Logger.h"

#define FFT_ZERO_PADDING 16
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER 1024

int main(int argc, char *argv[]) {

	Logger::logInfo("Starting application...\n");
	Dsp::DtmfPipeline pipe;

	Graphics::startGraphicsSystem(1200,768);
	Fft::prepareFft();

	pipe.prepare(SAMPLE_RATE,FRAMES_PER_BUFFER);

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

