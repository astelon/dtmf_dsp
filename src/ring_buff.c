#include "ring_buff.h"
#include <stdlib.h>

ringBuf *createRingBuffer(int len){
	ringBuf *mbuf = (ringBuf*) calloc(1,sizeof(ringBuf));
	mbuf->lenght = len;
	mbuf->end = len-1;
	mbuf->start = 0;
	mbuf->buffer = (float *) calloc(len,sizeof(float));
	mbuf->current = 0;
	return mbuf;
}

void destroyRingBuffer(ringBuf *b){
	free(b->buffer);
	free(b);
}

inline int calculate_relative_position(ringBuf *b, int pos){
	pos += b->current;	
	if(pos >= 0){
		pos = b->start + (pos % b->lenght); 
	} else {
		pos = b->end - (pos % b->lenght); 
	}
	return pos;
}

float relative_read(ringBuf *b, int pos) {
	pos = calculate_relative_position(b,pos);
	return b->buffer[pos];
}

void write_buf(ringBuf *b,float v) {
	b->buffer[b->current] = v;
}

void incr_ptr(ringBuf *b){
	b->current = calculate_relative_position(b,1);
}

void set_ptr(ringBuf *b, int pos){
	b->current = calculate_relative_position(b,pos);
}



