/*
 * Logger.h
 *
 *  Created on: 25 de jul. de 2015
 *      Author: Asteln
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>

namespace Logger {
	std::ostream &getLogger();
	std::ostream &logInfo(std::string str);
	std::ostream &logError(std::string str);
	void setLogger(std::ostream &nlog);
}

#endif /* LOGGER_H_ */
