/*
 * Texture.cpp
 * Copyright (c) 2012 HanoiLabs
 *
 */

#include "Texture.h"
#include "../Utils.h"

Texture::Texture(char *name) {
	this->target = GL_TEXTURE_2D;
	strcpy(this->name, name);
}

Texture::~Texture() {
	freePixel();
	deleteId();
}

void Texture::create(char *name, char *filename, unsigned char relativePath, unsigned int flags,
		unsigned char filter, float anisotropicFilter) {
	strcpy(this->name, name);
	DataBuffer *dataBuffer = new DataBuffer();
	dataBuffer->read(filename, relativePath);
	if (dataBuffer->getSize()) {
		load(dataBuffer);
		generateId(flags, filter, anisotropicFilter);
		freePixel();
		delete dataBuffer;
	}
}

void Texture::load(DataBuffer *dataBuffer) {
	char ext[ MAX_CHAR ] = {""};
	Utils::getFileName(dataBuffer->getFilename(), this->name);

	Utils::getFileExtension(dataBuffer->getFilename(), ext, 1);

	if(!strcmp(ext, "PNG"))
		loadPNG(dataBuffer);
	else if(!strcmp(ext, "PVR"))
		loadPVR(dataBuffer);
}

void png_memory_read( png_structp structp, png_bytep bytep, png_size_t size )
{
	// CHECK, SO IMPORTANT!
	DataBuffer *m = (DataBuffer *) png_get_io_ptr(structp);
//	mread( m, bytep, size );
}

void Texture::loadPNG(DataBuffer *dataBuffer) {

}

void Texture::loadPVR(DataBuffer *dataBuffer) {

}

void Texture::convert16Bits(unsigned char use5551) {

}

void Texture::generateId(unsigned int flags, unsigned char filter, float anisotropicFilter) {

}

void Texture::deleteId() {

}

void Texture::freePixel() {

}

void Texture::draw() {

}
