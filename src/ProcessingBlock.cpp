/*
 * ProcessingBlock.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#include "ProcessingBlock.h"

namespace Dsp {

ProcessingBlock::ProcessingBlock() : enabled(true) {
	// TODO Auto-generated constructor stub

}

ProcessingBlock::~ProcessingBlock() {
	// TODO Auto-generated destructor stub
}

void ProcessingBlock::preProcess() {
}

void ProcessingBlock::postProcess() {
}

bool ProcessingBlock::isEnabled() const {
	return enabled;
}

void ProcessingBlock::setEnabled(bool enabled) {
	this->enabled = enabled;
}

} /* namespace Dsp */


