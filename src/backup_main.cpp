/*
 * main.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include <iostream>

using namespace std;


extern "C" {
#include <complex.h>
#include <fftw3.h>
#include <portaudio.h>
}

#include "Filter.h"
#include "Modulator.h"

#include <stdio.h>
#include <stdlib.h>

fftwf_complex *in, *out;
fftwf_plan traf_plan;

#define SAMPLE_RATE (44100)
//#define SAMPLE_RATE (96000)
#define FRAMES_PER_BUFFER 1024
#define ZERO_PADDING 0
#define FFT_THREADS 4
#define FFT_SIZE ((2*((FRAMES_PER_BUFFER/2)+1)) + ZERO_PADDING)


typedef struct
{
    int N;
    float timeData[FFT_SIZE];
	fftwf_complex *freqData;
	fftwf_plan plan_rfw;
	fftwf_plan plan_rbw;
	Filter firstFilter;
	float tempBuffer1[2*FRAMES_PER_BUFFER];
	float tempBuffer2[2*FRAMES_PER_BUFFER];
	Filter secondFilter;
	Modulator firstModulator;
	Oscilator firstOscilator;
	Oscilator mockOsc;

	Filter thirdFilter;
	float tempBuffer3[2*FRAMES_PER_BUFFER];
	float tempBuffer4[2*FRAMES_PER_BUFFER];
	float tempBuffer5[2*FRAMES_PER_BUFFER];
	Filter fourthFilter;
	Modulator secondModulator;
	Oscilator secondOscilator;
}
paTestData;


//   This routine will be called by the PortAudio engine when audio is needed.
//   It may called at interrupt level on some machines so don't do anything
//   that could mess up the system like calling malloc() or free().

static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData ) {
	paTestData *mdata = (paTestData *) userData;

	//mdata->mockOsc.applyTo((float *)outputBuffer,framesPerBuffer);

	mdata->firstFilter.applyTo((float *)inputBuffer,(float *)mdata->tempBuffer1,framesPerBuffer);
	mdata->firstModulator.applyTo((float *)mdata->tempBuffer1,(float *)mdata->tempBuffer2,framesPerBuffer);
	mdata->secondFilter.applyTo((float *)mdata->tempBuffer2,(float *)mdata->tempBuffer3,framesPerBuffer);

	mdata->thirdFilter.applyTo((float *)mdata->tempBuffer3,(float *)mdata->tempBuffer4,framesPerBuffer);
	mdata->secondModulator.applyTo((float *)mdata->tempBuffer4,(float *)mdata->tempBuffer5,framesPerBuffer);
	mdata->fourthFilter.applyTo((float *)mdata->tempBuffer5,(float *)outputBuffer,framesPerBuffer);

	return 0;
}

void initPortAudio() {
	//Create port audio
	PaError err = Pa_Initialize();
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	//fftwf_init_threads();
	//fftwf_plan_with_nthreads(FFT_THREADS);
}

PaStream* openDefaultStream(paTestData* data) {
	PaStream* stream;

	// Open an audio I/O stream.
	PaError err = Pa_OpenDefaultStream(&stream, 1, // no input channels
	1, // mono output
	paFloat32, // 32 bit floating point output
	SAMPLE_RATE,
	FRAMES_PER_BUFFER,//paFramesPerBufferUnspecified,
	patestCallback, // this is your callback function
	data);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));

	return stream;
}

void startStream(PaStream* stream) {
	PaError err = Pa_StartStream(stream);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
}

void stopStream(PaStream* stream) {
	PaError err = Pa_StopStream(stream);
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
	Pa_CloseStream(stream);
}

void terminatePortAudio() {
	//Done with port audio, terminate it

	PaError err = Pa_Terminate();
	if (err != paNoError)
		printf("PortAudio error: %s\n", Pa_GetErrorText(err));
}

#define SETUP_FILTER(name,inputs,outputs,gain) name.setInputCoefficients(inputs); name.setOutputCoefficients(outputs); name.setGain(gain)

int main() {
	PaStream *stream;
	paTestData data;

	data.N = FRAMES_PER_BUFFER;
	data.firstOscilator.setGain(2.0);
	data.firstOscilator.setFrequency(8000);
	data.firstOscilator.setSampleRate(SAMPLE_RATE);
	data.firstModulator.setOscilator(&data.firstOscilator);

 	 // SAMPLING_FREQ 44100
	double input_coefficients[] = {1,6,15,20,15,6,1};
	double output_coefficients[] = {0,1.6301910568,-1.7736710308,1.0651269487,-0.4175206041,0.0901268112,0.0087883666 };
	double filter_gain = 154.3897897;

	 // SAMPLING_FREQ 96000
	/*double input_coefficients[] = {1,6,15,20,15,6,1};
	double output_coefficients[] = {0,3.9811884901,-6.8452604203,6.4498289230,-3.4951386513,1.0292502263,-0.1283545133 };
	double filter_gain =  7541.882169e+03;*/


	SETUP_FILTER(data.firstFilter,input_coefficients,output_coefficients,filter_gain);
	SETUP_FILTER(data.secondFilter,input_coefficients,output_coefficients,filter_gain);
	SETUP_FILTER(data.thirdFilter,input_coefficients,output_coefficients,filter_gain);
	SETUP_FILTER(data.fourthFilter,input_coefficients,output_coefficients,filter_gain);

	data.secondOscilator.setGain(2.0);
	data.secondOscilator.setFrequency(8000);
	data.secondOscilator.setSampleRate(SAMPLE_RATE);
	data.secondModulator.setOscilator(&data.secondOscilator);

	data.mockOsc.setGain(4.0);
	data.mockOsc.setFrequency(440);
	data.mockOsc.setSampleRate(SAMPLE_RATE);

	initPortAudio();

	stream = openDefaultStream(&data);

    startStream(stream);

    getchar();
	stopStream(stream);

	//Done with port audio, terminate it
	terminatePortAudio();
	/*fftwf_destroy_plan(data.plan_rbw);
	fftwf_destroy_plan(data.plan_rfw);

	fftwf_free(data.freqData);
	fftwf_cleanup_threads();
	fftwf_cleanup();*/


	printf("Done!\n");
	return 0;
}



