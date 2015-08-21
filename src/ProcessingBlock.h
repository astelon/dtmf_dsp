/*
 * ProcessingBlock.h
 *
 *  Created on: Aug 19, 2015
 *      Author: astelon
 */

#ifndef PROCESSINGBLOCK_H_
#define PROCESSINGBLOCK_H_

namespace Dsp {

class ProcessingBlock {
public:
	ProcessingBlock();
	virtual ~ProcessingBlock();
	virtual void preProcess();
	virtual void process() = 0;
	virtual void postProcess();
	bool isEnabled() const;
	void setEnabled(bool enabled);

protected:
	bool enabled;
};

} /* namespace Dsp */

#endif /* PROCESSINGBLOCK_H_ */
