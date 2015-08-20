/*
 * PortAudio.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <ostream>
	extern "C" {
		#include <portaudio.h>
	}

namespace Audio {
	void initPortAudio();

	void terminatePortAudio();

	void startAudioSystem(unsigned long sampleRate, unsigned long framesPerBuffer,void *data);

	PaStream* openDefaultStream(unsigned long sampleRate, unsigned long framesPerBuffer, void* data,int callback(const void *, void *,unsigned long, const PaStreamCallbackTimeInfo*,PaStreamCallbackFlags,void *));

	void startStream(PaStream* stream);

	void stopStream(PaStream* stream);

	float getSampleRate();

	float getFramesPerBuffer();

};



#endif /* AUDIO_H_ */
