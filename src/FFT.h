/*
 * DFT.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef FFT_H_
#define FFT_H_

extern "C" {
	#include <fftw3.h>
}
#include <string.h>


#define FFT_THREADS 4

#define FFT_SIZE(x) ((2*((x/2)+1)))

class Fft {
private:
	fftwf_complex *freqData;
	fftwf_plan plan;
	unsigned long mFramesPerBuffer;

public:
	Fft();
	Fft(unsigned long sampleRate, unsigned long framesPerBuffer, float *inputBuffer);
	~Fft();

	void getRealTransform(float *outputBuffer);

	static void prepareFft();
	static void CleanupFft();
};



#endif /* FFT_H_ */
