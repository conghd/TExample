/*
 * Texture.h
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Engine.h"
#include "DataBuffer.h"

enum
{
	TEXTURE_CLAMP			= ( 1 << 0 ),
	TEXTURE_MIPMAP			= ( 1 << 1 ),
	TEXTURE_16_BITS			= ( 1 << 2 ),
	TEXTURE_16_BITS_5551	= ( 1 << 3 )
};

enum
{
	TEXTURE_FILTER_0X = 0,
	TEXTURE_FILTER_1X = 1,
	TEXTURE_FILTER_2X = 2,
	TEXTURE_FILTER_3X = 3
};

typedef struct
{
	unsigned int headersize;

	unsigned int height;

	unsigned int width;

	unsigned int n_mipmap;

	unsigned int flags;

	unsigned int datasize;

	unsigned int bpp;

	unsigned int bitred;

	unsigned int bitgreen;

	unsigned int bitblue;

	unsigned int bitalpha;

	unsigned int tag;

	unsigned int n_surface;

} PVRHEADER;


class Texture {
	char			name[ MAX_CHAR ];

	unsigned int	tid;

	unsigned short	width;

	unsigned short	height;

	unsigned char	byte;

	unsigned int	size;

	unsigned int	target;

	unsigned int	internal_format;

	unsigned int	format;

	unsigned int	texel_type;

	unsigned char	*texel_array;

	unsigned int	n_mipmap;

	unsigned int	compression;



public:
	Texture(char *name);
	~Texture();
	void create(char *name, char *filename, unsigned char relativePath, unsigned int flags,
			unsigned char filter, float anisotropicFilter);
	void load(DataBuffer *dataBuffer);
	void loadPNG(DataBuffer *dataBuffer);
	void loadPVR(DataBuffer *dataBuffer);
	void convert16Bits(unsigned char use5551);
	void generateId(unsigned int flags, unsigned char filter, float anisotropicFilter);
	void deleteId();
	void freePixel();
	void draw();
};


#endif
