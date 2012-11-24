/*
 * simpleVertexShader.vsh.
 * Copyright (c) 2012, Hanoilabs.
 */
 
uniform mediump mat4 uMVPMatrix;

attribute mediump vec4 aPosition;

attribute lowp vec4 aColor;

varying lowp vec4 color;

void main( void ) {

	gl_Position = uMVPMatrix * aPosition;

	color = aColor;

}