/*
 * EventProcessor.h
 *
 *  Created on: Aug 20, 2015
 *      Author: astelon
 */

#ifndef EVENTPROCESSOR_H_
#define EVENTPROCESSOR_H_

extern "C" {
	#include <SDL/SDL.h>
}

class EventProcessor {
public:
	EventProcessor();
	bool pollEvents();
	virtual ~EventProcessor();
protected:
	SDL_Event event;
	bool quit;
};

#endif /* EVENTPROCESSOR_H_ */
