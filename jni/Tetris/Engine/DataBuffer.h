/*
 * DataBuffer.h
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef DATABUFFER_H 
#define DATABUFFER_H

#include "../Engine.h"
 
class DataBuffer {
private:
	char	filename[MAX_PATH];
	unsigned int size;
	unsigned int position;
	unsigned char *buffer;

public:
	DataBuffer();
	DataBuffer(DataBuffer *dataBuffer, unsigned int size);

	~DataBuffer();
	void read(char *filename, unsigned char relativePath);
	unsigned int write(void *buffer, unsigned int size);
	void insert(char *str, unsigned int position);

	unsigned int getSize();
	unsigned int getPosition();
	char *getFilename();
};


#endif
