/*
 * Logger.cpp
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#include "Logger.h"
#include <iostream>

namespace Logger {
	std::ostream *os = &std::cout;

	std::ostream &getLogger(){
		return *os;
	}
	void setLogger(std::ostream &nlog){
		os = &nlog;
	}
	std::ostream &logInfo(std::string str){
		(*os) << "-I-  " << str;
		return (*os);
	}
	std::ostream &logError(std::string str){
		(*os) << "-E-  " << str;
		return (*os);
	}
}
