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

#include <stdio.h>
#include <stdlib.h>

#include "PortAudio.h"
#include "Graphics.h"
#include "Graphics/Plotter.h"

#include "Logger.h"

#define SAMPLE_RATE (44100)
//#define SAMPLE_RATE (96000)
#define FRAMES_PER_BUFFER 128

typedef struct
{
    int N;

	Filter firstFilter;
	float system_in[FRAMES_PER_BUFFER];
	float system_out[FRAMES_PER_BUFFER];
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
	Fft *fft_in;
	Fft *fft_out;
} DspPipeline;

//   This routine will be called by the PortAudio engine when audio is needed.
//   It may called at interrupt level on some machines so don't do anything
//   that could mess up the system like calling malloc() or free().

static int dspPipelineCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
						   PaStreamCallbackFlags statusFlags,
                           void *userData ) {
	DspPipeline *mdata = (DspPipeline *) userData;

	//mdata->mockOsc.applyTo((float *)outputBuffer,framesPerBuffer);

	mdata->firstFilter.applyTo((float *)inputBuffer,(float *)mdata->tempBuffer1,framesPerBuffer);
	mdata->firstModulator.applyTo((float *)mdata->tempBuffer1,(float *)mdata->tempBuffer2,framesPerBuffer);
	mdata->secondFilter.applyTo((float *)mdata->tempBuffer2,(float *)mdata->tempBuffer3,framesPerBuffer);

	mdata->thirdFilter.applyTo((float *)mdata->tempBuffer3,(float *)mdata->tempBuffer4,framesPerBuffer);
	mdata->secondModulator.applyTo((float *)mdata->tempBuffer4,(float *)mdata->tempBuffer5,framesPerBuffer);
	mdata->fourthFilter.applyTo((float *)mdata->tempBuffer5,(float *)outputBuffer,framesPerBuffer);

	for(unsigned long i = 0; i<framesPerBuffer; i++) {
		mdata->system_in[i] = ((float*)inputBuffer)[i];
		mdata->system_out[i] = ((float*)outputBuffer)[i];
	}

	return 0;
}

#define SETUP_FILTER(name,inputs,outputs,gain) name.setInputCoefficients(inputs); name.setOutputCoefficients(outputs); name.setGain(gain)

int main(int argc, char *argv[]) {
	DspPipeline data;
	float outputFftBuffer[FRAMES_PER_BUFFER+2];
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

	PortAudio::runMicToSpeakerStream(SAMPLE_RATE,FRAMES_PER_BUFFER,&data,dspPipelineCallback);
	Graphics::startGraphicsSystem(1200,768);
	Fft::prepareFft();

	data.fft_in = new Fft(SAMPLE_RATE,FRAMES_PER_BUFFER,data.system_in);
	data.fft_out = new Fft(SAMPLE_RATE,FRAMES_PER_BUFFER,data.system_out);

	bool quit=false;
	double frequencyOsc1=8000, frequencyOsc2=8000;
	SDL_Rect textLocation = { 100, 100, 0, 0 };
	SDL_Rect fourierLocation =  { 5, 40, 590, 400 };
	SDL_Rect fourierLocation2 = { 600, 40, 590, 400 };

	stringstream ss("",ios_base::app | ios_base::out);
	SDL_Color textColor = { 255, 255, 255 };
	TTF_Font *font = TTF_OpenFont( "arial.ttf", 20 );

	if(font == NULL) Logger::logError("Font is currently NULL!!!!!!!") << endl;

	SDL_Surface *message = NULL;

	SDL_Event event;
	Graphics::Plotter plotter;
	plotter.setWorkingArea(&fourierLocation, 0.05, 0.05, 0.9, 0.9);

	Graphics::Plotter plotter2;
	plotter2.setWorkingArea(&fourierLocation2, 0.05, 0.05, 0.9, 0.9);

	while(!quit)
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
						break;
					}
					if(event.key.keysym.sym == SDLK_UP)
					{
						if(frequencyOsc2<16000) {

							frequencyOsc2 += 500;
							data.secondOscilator.setFrequency(frequencyOsc2);
							ss.str("Freq2: ");
							ss << frequencyOsc2;
							message = TTF_RenderText_Solid( font, ss.str().c_str(), textColor );
						}
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						if(frequencyOsc2>500) {
							frequencyOsc2 -= 500;
							data.secondOscilator.setFrequency(frequencyOsc2);
							ss.str("Freq2: ");
							ss << frequencyOsc2;
							message = TTF_RenderText_Solid( font, ss.str().c_str(), textColor );
						}
					}
					if(event.key.keysym.sym == SDLK_q)
					{
						if(frequencyOsc1<16000) {

							frequencyOsc1 += 500;
							data.firstOscilator.setFrequency(frequencyOsc1);
							ss.str("Freq1: ");
							ss << frequencyOsc1;
							message = TTF_RenderText_Solid( font, ss.str().c_str(), textColor );
						}
					}
					if(event.key.keysym.sym == SDLK_a)
					{
						if(frequencyOsc1>500) {
							frequencyOsc1 -= 500;
							data.firstOscilator.setFrequency(frequencyOsc1);
							ss.str("Freq1: ");
							ss << frequencyOsc1;
							message = TTF_RenderText_Solid( font, ss.str().c_str(), textColor );
						}
					}
					if(event.key.keysym.sym == SDLK_f)
					{
						data.fft_in->getRealTransform(outputFftBuffer);
						plotter.plotValues(outputFftBuffer,FRAMES_PER_BUFFER,NULL);
						data.fft_out->getRealTransform(outputFftBuffer);
						plotter2.plotValues(outputFftBuffer,FRAMES_PER_BUFFER,NULL);
						Graphics::flipBuffer();
					}
					break;
				default : break;
			}
            if(message!=NULL) {
            	Graphics::fillRect(NULL,&textLocation,0,0,0);
            	Graphics::blitToScreen(message,NULL,&textLocation);

            	Graphics::flipBuffer();
				SDL_FreeSurface(message);
				message = NULL;

			}
		}

	delete data.fft_in;
	delete data.fft_out;

	Fft::CleanupFft();
    Graphics::stopGraphicsSystem();
    PortAudio::terminatePortAudio();

	return 0;
}



