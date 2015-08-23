#include "DtmfPipeline.h"
#include "Audio.h"

namespace Dsp {
inline void DtmfPipeline::configureDetector(float *in, float t_freq, unsigned short id, DetectedIdList *list, GoertzelDetector *ptr){
	if (ptr == (GoertzelDetector *)0) return;
	ptr->setId(id);
	ptr->setFramesPerBuffer( Audio::getFramesPerBuffer() );
	ptr->setSamplingRate( Audio::getSampleRate() );
	ptr->setTargetFrequency(t_freq);
	ptr->setInput(in);
	ptr->setDetectedIdList(list);
	ptr->init();
}

DtmfPipeline::DtmfPipeline() : DspPipeline(), toneGeneratorRow(), toneGeneratorCol(), signalAdder1(), adder1Output(0.0),
								toneGenRowOut(0.0), toneGenColOut(0.0), systemInput(0.0) {
	prepare();
}

void DtmfPipeline::prepare(){
	SETUP_OSCILLATOR(toneGeneratorRow, 1.0, 697, Audio::getSampleRate());
	SETUP_OSCILLATOR(toneGeneratorCol, 0.1, 1209, Audio::getSampleRate());
	toneGeneratorRow.setOutput(&toneGenRowOut);
	toneGeneratorRow.setFrequency(DtmfRows[0]);

	toneGeneratorCol.setOutput(&toneGenColOut);
	toneGeneratorCol.setFrequency(DtmfCols[0]);

	signalAdder1.addInput(&toneGenRowOut);
	signalAdder1.addInput(&toneGenColOut);
	signalAdder1.setOutput(&adder1Output);

	addBlock(&toneGeneratorRow);
	addBlock(&toneGeneratorCol);
	addBlock(&signalAdder1);

	window.setInput(&adder1Output);
	window.setOutput(&windowOut);

	addBlock(&window);
	setOutputVarPtr(&windowOut);

//	setOutputVarPtr(&adder1Output);
	setInputVarPtr(&systemInput);

	//Configure detectors...
	for (int i=0; i<4; i++) {
		configureDetector(&systemInput, DtmfRows[i], i, &rowIdsDetected , &rowDetectors[i]);
		addBlock(&rowDetectors[i]);

		configureDetector(&systemInput, DtmfCols[i], i, &colIdsDetected , &colDetectors[i]);
		addBlock(&colDetectors[i]);
	}
}

const float DtmfPipeline::DtmfRows[] = {697,770,852,941};
const float DtmfPipeline::DtmfCols[] = {1209,1336,1477,1633};

void DtmfPipeline::enableOscilators(bool en) {
	toneGeneratorRow.setEnabled(en);
	toneGeneratorCol.setEnabled(en);
}

bool DtmfPipeline::symbolDetected() {
	return !rowIdsDetected.empty();
}

}
