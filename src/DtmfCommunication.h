/*
 * DtmfGenerator.h
 *
 *  Created on: Aug 20, 2015
 *      Author: astelon
 */

#ifndef DTMFCOMMUNICATION_H_
#define DTMFCOMMUNICATION_H_

#include <ctime>
#include <string>
#include "DtmfPipeline.h"
#include <exception>

class DtmfCommunication {
public:
	DtmfCommunication();
	void send(std::string str);
	std::string read();

	bool inputDataReady();
	virtual ~DtmfCommunication();
	Dsp::DtmfPipeline &getPipeline();
	float getSymbolTimeLapse() const;
	void setSymbolTimeLapse(float symbolTimeLapse);
	float getTimeBetweenSymbols() const;
	void setTimeBetweenSymbols(float timeBetweenSymbols);
	void sendSymbol(char c);
	char readSymbol();
	void wipePipeBuffers();

protected:
	Dsp::DtmfPipeline pipeline;
	bool dataReady;
	unsigned long symbolSize;
	float timeBetweenSymbols;
	bool error;
};

class InvalidSymbolException : public std::exception {
	public:
	InvalidSymbolException();

	std::string what();
};

#endif /* DTMFCOMMUNICATION_H_ */
