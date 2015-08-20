/*
 * PortAudio.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Audio.h"
#include "Logger.h"
#include "DspPipeline.h"

using namespace std;

namespace Audio {
	PaStream *stream = NULL;

	void initPortAudio() {
		//Create port audio
		Logger::logInfo("Starting PortAudio...") << std::endl;
		PaError err = Pa_Initialize();
		if (err != paNoError)
			Logger::logError("PortAudio error:") << Pa_GetErrorText(err) << endl;
	}

	PaStream* openDefaultStream(unsigned long sampleRate, unsigned long framesPerBuffer, void* data,int callback(const void *, void *,unsigned long, const PaStreamCallbackTimeInfo*,PaStreamCallbackFlags,void *)) {
		PaStream* stream;

		// Open an audio I/O stream.
		PaError err = Pa_OpenDefaultStream(&stream, 1, // no input channels
		1, // mono output
		paFloat32, // 32 bit floating point output
		sampleRate,
		framesPerBuffer,//paFramesPerBufferUnspecified,
		callback, // this is your callback function
		data);
		if (err != paNoError)
			Logger::logError("PortAudio error:") << Pa_GetErrorText(err) << endl;

		return stream;
	}

	void startStream(PaStream* stream) {
		if(!stream) return;
		PaError err = Pa_StartStream(stream);
		if (err != paNoError)
			Logger::logError("PortAudio error:") << Pa_GetErrorText(err) << endl;
	}

	void stopStream(PaStream* stream) {
		if(!stream) return;
		PaError err = Pa_StopStream(stream);
		if (err != paNoError)
			Logger::logError("PortAudio error:") << Pa_GetErrorText(err) << endl;
		Pa_CloseStream(stream);
	}

	void terminatePortAudio() {
		//Done with port audio, terminate it
		stopStream(stream);

		PaError err = Pa_Terminate();
		if (err != paNoError)
			Logger::logError("PortAudio error:") << Pa_GetErrorText(err) << endl;
	}

	//   This routine will be called by the PortAudio engine when audio is needed.
	//   It may called at interrupt level on some machines so don't do anything
	//   that could mess up the system like calling malloc() or free().
	static int audioDspPipelineCallback(const void* inputBuffer,
			void* outputBuffer, unsigned long framesPerBuffer,
			const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags, void* userData) {
		Dsp::DspPipeline *pipe = (Dsp::DspPipeline *) userData;

		pipe->preProcess();

		for(unsigned long i = 0; i<framesPerBuffer; i++) {
			if(pipe->validInputVar()) pipe->setInput( ((float*)inputBuffer)[i] );
			pipe->process();
			if(pipe->validOutputVar()) ((float*)outputBuffer)[i] = pipe->getOutput();
		}

		pipe->postProcess();

		return 0;
	}

	void startAudioSystem(unsigned long sampleRate, unsigned long framesPerBuffer,void *data) {
		initPortAudio();
		stream = Audio::openDefaultStream(sampleRate,framesPerBuffer,data,audioDspPipelineCallback);
		Audio::startStream(stream);
	}
}
