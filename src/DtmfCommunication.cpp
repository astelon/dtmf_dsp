/*
 * DtmfGenerator.cpp
 *
 *  Created on: Aug 20, 2015
 *      Author: astelon
 */

#include "DtmfCommunication.h"
#include "Audio.h"
#include "Logger.h"

using namespace std;

DtmfCommunication::DtmfCommunication() : dataReady(false), pipeline(), symbolSize(0), timeBetweenSymbols(0.0) {
	// TODO Auto-generated constructor stub
	pipeline.enableOscilators(false);
	setSymbolTimeLapse(0.4);
}

DtmfCommunication::~DtmfCommunication() {
	// TODO Auto-generated destructor stub
}

void DtmfCommunication::send(std::string str) {
}

string DtmfCommunication::read() {
	string str;
	return str;
}

bool DtmfCommunication::inputDataReady() {
	return pipeline.symbolDetected();
}

Dsp::DtmfPipeline &DtmfCommunication::getPipeline(){
	return pipeline;
}

float DtmfCommunication::getSymbolTimeLapse() const {
	return symbolSize;
}

void DtmfCommunication::setSymbolTimeLapse(float symbolTimeLapse) {
	this->symbolSize = symbolTimeLapse * Audio::getSampleRate();
}

float DtmfCommunication::getTimeBetweenSymbols() const {
	return timeBetweenSymbols;
}

void DtmfCommunication::setTimeBetweenSymbols(float timeBetweenSymbols) {
	this->timeBetweenSymbols = timeBetweenSymbols;
}

void DtmfCommunication::sendSymbol(char c) {
	unsigned short row, col;
	switch(c) {
		case '1' : row=0; col=0; break;
		case '2' : row=0; col=1; break;
		case '3' : row=0; col=2; break;
		case '4' : row=1; col=0; break;
		case '5' : row=1; col=1; break;
		case '6' : row=1; col=2; break;
		case '7' : row=2; col=0; break;
		case '8' : row=2; col=1; break;
		case '9' : row=2; col=2; break;
		case '0' : row=3; col=1; break;
		case '*' : row=3; col=0; break;
		case '#' : row=3; col=2; break;
		case 'A' : row=0; col=3; break;
		case 'B' : row=1; col=3; break;
		case 'C' : row=2; col=3; break;
		case 'D' : row=3; col=3; break;
		default: row=4; col=4; break;
	}
	if (row == 4) throw( InvalidSymbolException() );

	pipeline.toneGeneratorRow.setFrequency(Dsp::DtmfPipeline::DtmfRows[row]); pipeline.toneGeneratorCol.setFrequency(Dsp::DtmfPipeline::DtmfCols[col]);
	pipeline.toneGeneratorRow.setTimeOut(symbolSize);
	pipeline.toneGeneratorCol.setTimeOut(symbolSize);
	pipeline.window.setToneDuration(symbolSize);
	pipeline.enableOscilators(true);
	pipeline.window.setEnabled(true);
}

InvalidSymbolException::InvalidSymbolException() : exception() {
}

string InvalidSymbolException::what() {
	return "Invalid Symbol Selected for Communication.";
}

char DtmfCommunication::readSymbol() {
	unsigned short col, row;
	char symbol = '+';

	if(pipeline.rowIdsDetected.empty() || pipeline.colIdsDetected.empty()) throw( InvalidSymbolException() );

	row = pipeline.rowIdsDetected.front();
	col = pipeline.colIdsDetected.front();

	switch(row*10+col) {
		case 00: symbol = '1'; break;
		case 01: symbol = '2'; break;
		case 02: symbol = '3'; break;
		case 10: symbol = '4'; break;
		case 11: symbol = '5'; break;
		case 12: symbol = '6'; break;
		case 20: symbol = '7'; break;
		case 21: symbol = '8'; break;
		case 22: symbol = '9'; break;
		case 31: symbol = '0'; break;
		case 30: symbol = '*'; break;
		case 32: symbol = '#'; break;
		case 03: symbol = 'A'; break;
		case 13: symbol = 'B'; break;
		case 23: symbol = 'C'; break;
		case 33: symbol = 'D'; break;
		default: throw( InvalidSymbolException() ); break;
	}
	//Remove first elements
	pipeline.rowIdsDetected.erase(pipeline.rowIdsDetected.begin());
	pipeline.colIdsDetected.erase(pipeline.colIdsDetected.begin());

	return symbol;
}

void DtmfCommunication::wipePipeBuffers() {
	pipeline.rowIdsDetected.clear();
	pipeline.colIdsDetected.clear();
}
