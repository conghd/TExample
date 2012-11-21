/*
 * Director.cpp
 * Copyright (c) 2012, Hanoilabs
 */

#include "Director.h"

#ifndef __IPHONE_4_0
	PFNGLBINDVERTEXARRAYOESPROC		glBindVertexArrayOES;
	PFNGLGENVERTEXARRAYSOESPROC		glGenVertexArraysOES;
	PFNGLDELETEVERTEXARRAYSOESPROC	glDeleteVertexArraysOES;
#endif

Director::Director() {

}

Director::~Director() {

}

void Director::start() {
	#ifdef __IPHONE_4_0

		printf("\nGL_VENDOR:      %s\n", ( char * )glGetString( GL_VENDOR     ) );
		printf("GL_RENDERER:    %s\n"  , ( char * )glGetString( GL_RENDERER   ) );
		printf("GL_VERSION:     %s\n"  , ( char * )glGetString( GL_VERSION    ) );
		printf("GL_EXTENSIONS:  %s\n"  , ( char * )glGetString( GL_EXTENSIONS ) );
	#else

		__android_log_print( ANDROID_LOG_INFO, "", "\nGL_VENDOR:      %s\n", ( char * )glGetString( GL_VENDOR     ) );
		__android_log_print( ANDROID_LOG_INFO, "", "GL_RENDERER:    %s\n"  , ( char * )glGetString( GL_RENDERER   ) );
		__android_log_print( ANDROID_LOG_INFO, "", "GL_VERSION:     %s\n"  , ( char * )glGetString( GL_VERSION    ) );
		__android_log_print( ANDROID_LOG_INFO, "", "GL_EXTENSIONS:  %s\n"  , ( char * )glGetString( GL_EXTENSIONS ) );
	#endif

	glHint( GL_GENERATE_MIPMAP_HINT, GL_NICEST );

	glHint( GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES, GL_NICEST );

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE  );
	glDisable( GL_DITHER );
	glDepthMask( GL_TRUE );
	glDepthFunc( GL_LESS );
	glDepthRangef( 0.0f, 1.0f );
	glCullFace ( GL_BACK );
	glFrontFace( GL_CCW  );
	glClearStencil( 0 );
	glStencilMask( 0xFFFFFFFF );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glClear( GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	#ifndef __IPHONE_4_0

		glBindVertexArrayOES 	= ( PFNGLBINDVERTEXARRAYOESPROC    ) eglGetProcAddress("glBindVertexArrayOES"  );
		glGenVertexArraysOES 	= ( PFNGLGENVERTEXARRAYSOESPROC    ) eglGetProcAddress("glGenVertexArraysOES"  );
		glDeleteVertexArraysOES = ( PFNGLDELETEVERTEXARRAYSOESPROC ) eglGetProcAddress("glDeleteVertexArraysOES");
	#endif

	setMatrixMode(TEXTURE_MATRIX);
	loadIdentity();

	setMatrixMode(PROJECTION_MATRIX);
	loadIdentity();

	setMatrixMode(MODELVIEW_MATRIX);
	loadIdentity();
}

void Director::error( void )
{
	unsigned int error;

	while( ( error = glGetError() ) != GL_NO_ERROR )
	{
		char str[ MAX_CHAR ] = {""};

		switch( error )
		{
			case GL_INVALID_ENUM:
			{
				strcpy( str, "GL_INVALID_ENUM" );
				break;
			}

			case GL_INVALID_VALUE:
			{
				strcpy( str, "GL_INVALID_VALUE" );
				break;
			}

			case GL_INVALID_OPERATION:
			{
				strcpy( str, "GL_INVALID_OPERATION" );
				break;
			}

			case GL_OUT_OF_MEMORY:
			{
				strcpy( str, "GL_OUT_OF_MEMORY" );
				break;
			}
		}

//		console_print( "[ GL_ERROR ]\nERROR: %s\n", str );
	}
}

void Director::setMatrixMode(unsigned char matrixMode) {
	this->matrixMode = matrixMode;
}

void Director::loadIdentity(void)
{
	switch(matrixMode)
	{
		case MODELVIEW_MATRIX:
		{
			EsUtils::loadIdentity(getModelviewMatrix());
			break;
		}
		case PROJECTION_MATRIX:
		{
			EsUtils::loadIdentity(getProjectionMatrix());
			break;
		}
		case TEXTURE_MATRIX:
		{
			EsUtils::loadIdentity(getTextureMatrix());
			break;
		}
	}
}

void Director::pushMatrix(void)
{
	switch(matrixMode)
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_copy_mat4( &modelviewMatrix[modelviewMatrixIndex + 1 ],
							&modelviewMatrix[modelviewMatrixIndex	  ] );

			++modelviewMatrixIndex;

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_copy_mat4( &projectionMatrix[projectionMatrixIndex + 1 ],
							&projectionMatrix[ projectionMatrixIndex	    ] );

			++projectionMatrixIndex;

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_copy_mat4( &textureMatrix[ textureMatrixIndex + 1 ],
							&textureMatrix[ textureMatrixIndex     ] );

			++textureMatrixIndex;

			break;
		}
	}
}

void Director::popMatrix( void )
{
	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			--modelviewMatrixIndex;

			break;
		}

		case PROJECTION_MATRIX:
		{
			--projectionMatrixIndex;

			break;
		}

		case TEXTURE_MATRIX:
		{
			--textureMatrixIndex;

			break;
		}
	}
}


void Director::loadMatrix( mat4 *m )
{
	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_copy_mat4( getModelviewMatrix(), m );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_copy_mat4( getProjectionMatrix(), m );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_copy_mat4( getTextureMatrix(), m );

			break;
		}
	}
}


void Director::multiplyMatrix( mat4 *m )
{
	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_multiply_mat4( getModelviewMatrix(), getModelviewMatrix(), m );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_multiply_mat4( getProjectionMatrix(), getProjectionMatrix(), m );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_multiply_mat4( getTextureMatrix(), getTextureMatrix(), m );

			break;
		}
	}
}


void Director::translate( float x, float y, float z )
{
	vec3 v = { x, y, z };

	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_translate( getModelviewMatrix(), getModelviewMatrix(), &v );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_translate( getProjectionMatrix(), getProjectionMatrix(), &v );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_translate( getTextureMatrix(), getTextureMatrix(), &v );

			break;
		}
	}
}


void Director::rotate( float angle, float x, float y, float z )
{
	if( !angle ) return;

	vec4 v = { x, y, z, angle };

	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_rotate( getModelviewMatrix(), getModelviewMatrix(), &v );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_rotate( getProjectionMatrix(), getProjectionMatrix(), &v );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_rotate( getTextureMatrix(), getTextureMatrix(), &v );

			break;
		}
	}
}


void Director::scale( float x, float y, float z )
{
	static vec3 scale = { 1.0f, 1.0f, 1.0f };

	vec3 v = { x, y, z };

	if( !memcmp( &v, &scale, sizeof( vec3 ) ) ) return;


	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_scale( getModelviewMatrix(), getModelviewMatrix(), &v );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_scale( getProjectionMatrix(), getProjectionMatrix(), &v );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_scale( getTextureMatrix(), getTextureMatrix(), &v );

			break;
		}
	}
}


mat4 *Director::getModelviewMatrix( void )
{ return &modelviewMatrix[ modelviewMatrixIndex ]; }


mat4 *Director::getProjectionMatrix( void )
{ return &projectionMatrix[ projectionMatrixIndex ]; }


mat4 *Director::getTextureMatrix( void )
{ return &textureMatrix[ textureMatrixIndex ]; }


mat4 *Director::getModelviewProjectionMatrix( void )
{
	Matrix::mat4_multiply_mat4( &modelviewProjectionMatrix,
						getProjectionMatrix(),
						getModelviewMatrix() );

	return &modelviewProjectionMatrix;
}


mat3 *Director::getNormalMatrix( void )
{
	mat4 mat;

	Matrix::mat4_copy_mat4( &mat, getModelviewMatrix() );

	Matrix::mat4_invert_full( &mat );

	Matrix::mat4_transpose( &mat );

	Matrix::mat3_copy_mat4( &normalMatrix, &mat );

	return &normalMatrix;
}


void Director::ortho( float left, float right, float bottom, float top, float clip_start, float clip_end )
{
	switch( matrixMode )
	{
		case MODELVIEW_MATRIX:
		{
			Matrix::mat4_ortho( getModelviewMatrix(), left, right, bottom, top, clip_start, clip_end );

			break;
		}

		case PROJECTION_MATRIX:
		{
			Matrix::mat4_ortho( getProjectionMatrix(), left, right, bottom, top, clip_start, clip_end );

			break;
		}

		case TEXTURE_MATRIX:
		{
			Matrix::mat4_ortho( getTextureMatrix(), left, right, bottom, top, clip_start, clip_end );

			break;
		}
	}
}


void Director::setOrthoGraphic2D( float left, float right, float bottom, float top )
{ ortho( left, right, bottom, top, -1.0f, 1.0f ); }


void Director::setOrthoGraphic( float screen_ratio, float scale, float aspect_ratio, float clip_start, float clip_end, float screen_orientation )
{
	scale = ( scale * 0.5f ) * aspect_ratio;

	ortho( -1.0f,
			    1.0f,
			   -screen_ratio,
			    screen_ratio,
			    clip_start,
				clip_end );

	Director::scale( 1.0f / scale, 1.0f / scale, 1.0f );

	if( screen_orientation ) rotate( screen_orientation, 0.0f, 0.0f, 1.0f );
}


void Director::setPerspective( float fovy, float aspect_ratio, float clip_start, float clip_end, float screen_orientation )
{
	mat4 mat;

	float d = clip_end - clip_start,
		  r = ( fovy * 0.5f ) * DEG_TO_RAD,
		  s = sinf( r ),
		  c = cosf( r ) / s;

	Matrix::mat4_identity( &mat );

    mat.m[ 0 ].x = c / aspect_ratio;
    mat.m[ 1 ].y = c;
    mat.m[ 2 ].z = -( clip_end + clip_start ) / d;
    mat.m[ 2 ].w = -1.0f;
    mat.m[ 3 ].z = -2.0f * clip_start * clip_end / d;
    mat.m[ 3 ].w =  0.0f;

	multiplyMatrix( &mat );

	if( screen_orientation ) rotate( screen_orientation, 0.0f, 0.0f, 1.0f );
}


void Director::lookAt( vec3 *eye, vec3 *center, vec3 *up )
{
	vec3 f,
		 s,
		 u;

	mat4 mat;

	Matrix::mat4_identity( &mat );

	Vector::vec3_diff( &f, center, eye );

	Vector::vec3_normalize( &f, &f );

	Vector::vec3_cross( &s, &f, up );

	Vector::vec3_normalize( &s, &s );

	Vector::vec3_cross( &u, &s, &f );

	mat.m[ 0 ].x = s.x;
	mat.m[ 1 ].x = s.y;
	mat.m[ 2 ].x = s.z;

	mat.m[ 0 ].y = u.x;
	mat.m[ 1 ].y = u.y;
	mat.m[ 2 ].y = u.z;

	mat.m[ 0 ].z = -f.x;
	mat.m[ 1 ].z = -f.y;
	mat.m[ 2 ].z = -f.z;

	multiplyMatrix( &mat );

	translate( -eye->x, -eye->y, -eye->z );
}


int Director::project( float objx, float objy, float objz, mat4 *modelview_matrix, mat4 *projection_matrix, int *viewport_matrix, float *winx, float *winy, float *winz )
{
	vec4 vin,
		 vout;

	vin.x = objx;
	vin.y = objy;
	vin.z = objz;
	vin.w = 1.0f;

	Matrix::vec4_multiply_mat4( &vout, &vin, modelview_matrix );

	Matrix::vec4_multiply_mat4( &vin, &vout, projection_matrix );

	if( !vin.w ) return 0;

	vin.x /= vin.w;
	vin.y /= vin.w;
	vin.z /= vin.w;

	vin.x = vin.x * 0.5f + 0.5f;
	vin.y = vin.y * 0.5f + 0.5f;
	vin.z = vin.z * 0.5f + 0.5f;

	vin.x = vin.x * viewport_matrix[ 2 ] + viewport_matrix[ 0 ];
	vin.y = vin.y * viewport_matrix[ 3 ] + viewport_matrix[ 1 ];

	*winx = vin.x;
	*winy = vin.y;
	*winz = vin.z;

	return 1;
}


int Director::unproject( float winx, float winy, float winz, mat4 *modelview_matrix, mat4 *projection_matrix, int *viewport_matrix, float *objx, float *objy, float *objz )
{
	mat4 final;

	vec4 vin,
		 vout;

	Matrix::mat4_multiply_mat4( &final,
						projection_matrix,
						modelview_matrix );

	Matrix::mat4_invert_full( &final );

	vin.x = winx;
	vin.y = winy;
	vin.z = winz;
	vin.w = 1.0f;

	vin.x = ( vin.x - viewport_matrix[ 0 ] ) / viewport_matrix[ 2 ];
	vin.y = ( vin.y - viewport_matrix[ 1 ] ) / viewport_matrix[ 3 ];

	vin.x = vin.x * 2.0f - 1.0f;
	vin.y = vin.y * 2.0f - 1.0f;
	vin.z = vin.z * 2.0f - 1.0f;

	Matrix::vec4_multiply_mat4( &vout, &vin, &final );

	if( !vout.w ) return 0;

	vout.x /= vout.w;
	vout.y /= vout.w;
	vout.z /= vout.w;

	*objx = vout.x;
	*objy = vout.y;
	*objz = vout.z;

	return 1;
}
