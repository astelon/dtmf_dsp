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

#include <stdio.h>
#include <stdlib.h>

#include "Audio.h"
#include "Graphics.h"
#include "Plotter.h"
#include "TextPrinter.h"

#include "Logger.h"
#include "DtmfCommunication.h"
#include <string>

void mainLoop(DtmfCommunication *com){
	SDL_Event event;
	char input_str[2];
	string incomingData;
	Graphics::TextPrinter textPrinter;
	SDL_Rect errorBackground;
	errorBackground.h = 20;
	errorBackground.w = 200;
	errorBackground.x = 295;
	errorBackground.y = 295;

	SDL_Rect inputBackground;
	errorBackground.h = 20;
	errorBackground.w = 200;
	errorBackground.x = 95;
	errorBackground.y = 95;

	textPrinter.font("arial.ttf",16);
	textPrinter.text("Input: ").position(10,100).color(255,255,255).render().blit();
	bool quit=false;
	/*while( com->inputDataReady() ) {
		Logger::logInfo("Incoming Data: ") << com->readSymbol() << endl;
	}*/
	input_str[1] = (char)0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
				if (event.key.keysym.sym == SDLK_KP1) com->sendSymbol('1');
				if (event.key.keysym.sym == SDLK_KP2) com->sendSymbol('2');
				if (event.key.keysym.sym == SDLK_KP3) com->sendSymbol('3');
				if (event.key.keysym.sym == SDLK_KP4) com->sendSymbol('4');
				if (event.key.keysym.sym == SDLK_KP5) com->sendSymbol('5');
				if (event.key.keysym.sym == SDLK_KP6) com->sendSymbol('6');
				if (event.key.keysym.sym == SDLK_KP7) com->sendSymbol('7');
				if (event.key.keysym.sym == SDLK_KP8) com->sendSymbol('8');
				if (event.key.keysym.sym == SDLK_KP9) com->sendSymbol('9');
				if (event.key.keysym.sym == SDLK_KP0) com->sendSymbol('0');
				if (event.key.keysym.sym == SDLK_KP_MULTIPLY) com->sendSymbol('*');
				if (event.key.keysym.sym == SDLK_KP_DIVIDE)   com->sendSymbol('#');
				if (event.key.keysym.sym == SDLK_a) com->sendSymbol('A');
				if (event.key.keysym.sym == SDLK_b) com->sendSymbol('B');
				if (event.key.keysym.sym == SDLK_c) com->sendSymbol('C');
				if (event.key.keysym.sym == SDLK_d) com->sendSymbol('D');
				Graphics::fillRect(NULL,&errorBackground,0,0,0);
					break;
			default: break;
			}
		}
		SDL_Delay(300);
		while( com->inputDataReady() ) {
				try {
				input_str[0] = com->readSymbol();
				incomingData.append(input_str);
				if(incomingData.length()>=10) incomingData.erase(incomingData.begin());
				Logger::logInfo("Reading data") << endl;
				} catch(InvalidSymbolException &e) {
					textPrinter.text("Error reading input, please repeat...").position(300,300).color(180,0,0).render().blit();
					SDL_Delay(300);
					com->wipePipeBuffers();
				}
				Graphics::fillRect(NULL,&inputBackground,0,0,0);
				textPrinter.text(incomingData).position(100,100).color(255,255,255).render().blit();
		}
		Graphics::flipBuffer();
	}
}

int main(int argc, char *argv[]) {

	Logger::logInfo("Starting application...\n");
	//Dsp::DtmfPipeline pipe;

	DtmfCommunication comm;
	Graphics::startGraphicsSystem(1200,768);
	Fft::prepareFft();

	Audio::startAudioSystem(&comm.getPipeline());

	mainLoop(&comm);

    Audio::terminatePortAudio();

	Fft::CleanupFft();

    Graphics::stopGraphicsSystem();
    Audio::terminatePortAudio();
	return 0;
}

