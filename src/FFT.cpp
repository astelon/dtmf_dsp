/*
 * DFT.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "FFT.h"
#include "Logger.h"
#include <math.h>

Fft::Fft() : freqData(NULL),
plan(), mFramesPerBuffer(0) {

}

Fft::Fft(unsigned long sampleRate, unsigned long framesPerBuffer, float *inputBuffer) {
	freqData = (fftwf_complex *) fftwf_malloc(sizeof(fftw_complex)*FFT_SIZE(sampleRate));
	memset((void *)freqData,0,sizeof(fftw_complex)*FFT_SIZE(sampleRate));
	plan = fftwf_plan_dft_r2c_1d(framesPerBuffer, inputBuffer, freqData, FFTW_MEASURE);
	mFramesPerBuffer = framesPerBuffer;
}

Fft::~Fft(){
	fftwf_destroy_plan(plan);
	fftwf_free(freqData);
}

void Fft::prepareFft(){
	fftwf_init_threads();
	fftwf_plan_with_nthreads(FFT_THREADS);
}

void Fft::CleanupFft(){
	fftwf_cleanup_threads();
	fftwf_cleanup();
}

void Fft::getRealTransform(float *outputBuffer){
	fftwf_execute(plan);
	for(unsigned long i=0; i < mFramesPerBuffer; i++) outputBuffer[i] = fabs(freqData[i][0]);
}

