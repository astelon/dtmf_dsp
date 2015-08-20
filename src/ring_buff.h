/*
*	Buffer circular para almacenar los valores anteriores.
*/

#ifndef _RING_BUFF_H_
#define _RING_BUFF_H_
typedef struct {
	float *buffer;
	unsigned int start, end, lenght;
	int current;
} ringBuf;

ringBuf *createRingBuffer(int len);

void destroyRingBuffer(ringBuf *b);

int calculate_relative_position(ringBuf *b, int pos);

float relative_read(ringBuf *b, int pos);

void write_buf(ringBuf *b,float v);

void incr_ptr(ringBuf *b);

void set_ptr(ringBuf *b, int pos);
#endif
