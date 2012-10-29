/*
 * Types.h
 * Copyright (R) Oct 2012, Hanoilabs
 *
 */

#ifndef TYPES_H
#define TYPES_H

#define MAX_CHAR	64
#define MAX_PATH	256
#define DEG_TO_RAD	M_PI / 180.0f
#define RAD_TO_DEG	90.0f / M_PI

#define BUFFER_OFFSET( x ) ( ( char * )NULL + x )

#define CLAMP( x, low, high ) ( ( x > high ) ? high : ( ( x < low ) ? low : x ) )


enum
{
	STOP  = 0,
	PLAY  = 1,
	PAUSE = 2
};


typedef struct
{
	float x;
	float y;

} vec2;


typedef struct
{
	float x;
	float y;
	float z;

} vec3;


typedef struct
{
	float x;
	float y;
	float z;
	float w;

} vec4;


typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

} ucol4;


typedef struct
{
	float x;
	float y;
	float z;
	float w;

} quat;


typedef struct
{
	vec3 m[ 3 ];

} mat3;


typedef struct
{
	vec4 m[ 4 ];

} mat4;


typedef struct
{
	unsigned short vertex_index;

	unsigned short uv_index;

} vecind;

#endif
