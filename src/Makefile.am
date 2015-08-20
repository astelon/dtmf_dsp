bin_PROGRAMS=dtmf_dsp
dtmf_dsp_SOURCES=main.cpp Audio.cpp FFT.cpp Modulator.cpp Filter.cpp Graphics.cpp Input.cpp Logger.cpp Lookup_sin.cpp Oscilator.cpp Plotter.cpp ring_buff.c SignalAdder.cpp TextPrinter.cpp ProcessingBlock.cpp DspPipeline.cpp GoertzelDetector.cpp
dtmf_dsp_LDADD=-lfftw3f_threads -lfftw3f -lportaudio -lSDL_ttf -lSDL -lpthread -lm -lrt
dtmf_dsp_LDFLAGS=-L/usr/lib/x86_64-linux-gnu -Wl,-rpath,/usr/lib/x86_64-linux-gnu