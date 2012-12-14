/*
 *
 * http://androgeek.info/?p=167
 *
 */
FILE* file = fopen("/sdcard/tex.txt","r");
int w,h;
char *s;
if (file != NULL)
{
    fscanf(file,"%d %d",&w,&h);
    LOGI("w=%d h=%d\n", w, h);
    texPixel_w=w;
    texPixel_h=h;
    fscanf(file,"%s",s);
    if(s=="RGB")
    {
        bAlpha=false;
        texPixels=new GLubyte[w*h*3];
        for(int i=0;i<w*h*3;++i)
        {
            int a;
            fscanf(file,"%d",&a);
            texPixels[i]=(GLubyte)a;
        }
    }
    else
    {
        bAlpha=true;
        texPixels=new GLubyte[w*h*4];
        for(int i=0;i<w*h*4;++i)
        {
            int a;
            fscanf(file,"%d",&a);
            texPixels[i]=(GLubyte)a;
        }
    }

}

//================================

static const char gVertexShader[] = "attribute vec4 a_position;   \n"
                "attribute vec3 a_normal;     \n"
        "attribute vec2 a_texCoord;   \n"
        "varying vec2 v_texCoord;     \n"
        "varying vec3 v_normal; \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = a_position; \n"
        " v_normal = a_normal; \n"
        "   v_texCoord = a_texCoord;  \n"
        "}                            \n";

static const char gFragmentShader[] =
                "precision mediump float;                            \n"
                        "varying vec2 v_texCoord;                            \n"
                        "varying vec3 v_normal; \n"
                        "uniform sampler2D s_texture;                        \n"
                        "void main()                                         \n"
                        "{                                                   \n"
                        "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
                        "}                         




bool setupGraphics(int w, int h) {
		printGLString("Version", GL_VERSION);
		printGLString("Vendor", GL_VENDOR);
		printGLString("Renderer", GL_RENDERER);
		printGLString("Extensions", GL_EXTENSIONS);

		LOGI("setupGraphics(%d, %d)", w, h);
		gProgram = createProgram(gVertexShader, gFragmentShader);
		if (!gProgram) {
				LOGE("Could not create program.");
				return false;
		}
		gvPositionHandle = glGetAttribLocation(gProgram, "a_position");
		gvNormalHandle=glGetAttribLocation(gProgram,"a_normal");
		gvTexCoordHandle = glGetAttribLocation(gProgram, "a_texCoord");

		gvSamplerHandle = glGetAttribLocation(gProgram, "s_texture");

		// Use tightly packed data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Generate a texture object
		glGenTextures(1, &textureID);
		if(!bAlpha)
			textureID = createSimpleTexture2D(textureID, texPixels,texPixel_w, texPixel_h, 3);
		else
			textureID = createSimpleTexture2D(textureID, texPixels,texPixel_w, texPixel_h, 3);

		checkGlError("glGetAttribLocation");
		LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
						gvPositionHandle);

		glViewport(0, 0, w, h);
		checkGlError("glViewport");
		return true;
}

		/////////////////////////////////////////////////////////////
GLuint createSimpleTexture2D(GLuint _textureid, GLubyte* pixels,
				int width, int height, int channels) {

		// Bind the texture
		glActiveTexture(GL_TEXTURE0);
		checkGlError("glActiveTexture");
		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, _textureid);
		checkGlError("glBindTexture");

		GLenum format;
		switch (channels) {
		case 3:
				format = GL_RGB;
				break;
		case 1:
				format = GL_LUMINANCE;
				break;
		case 4:
				format = GL_RGBA;
				break;
		}
		// Load the texture
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
						GL_UNSIGNED_BYTE, pixels);

		checkGlError("glTexImage2D");
		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		return _textureid;

}



void renderFrame() {

		GLfloat vVertices[] = { -0.75f, 1.0f, 0.0f, // Position 0
										0.0f,1.0f,0.0f,
						0.0f, 0.0f, // TexCoord 0
						-.75f, -1.0f, 0.0f, // Position 1
						0.0f,1.0f,0.0f,
						0.0f, 1.0f, // TexCoord 1
						.75f, -1.0f, 0.0f, // Position 2
						0.0f,1.0f,0.0f,
						1.0f, 1.0f, // TexCoord 2
						.75f, 1.0f, 0.0f, // Position 3
						0.0f,1.0f,0.0f,
						1.0f, 0.0f // TexCoord 3
						};
		GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
		GLsizei stride = 8 * sizeof(GLfloat); // 3 for position, 3 for normal, 2 for texture

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		checkGlError("glClearColor");

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		checkGlError("glClear");

		glUseProgram(gProgram);
		checkGlError("glUseProgram");

		// Load the vertex position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
						vVertices);
						checkGlError("gvPositionHandle");
		glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, stride,
					vVertices+3);
		checkGlError("gvNormalHandle");
		// Load the texture coordinate
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
						vVertices+6);
						checkGlError("gvTexCoordHandle");

		glEnableVertexAttribArray(gvPositionHandle);
		glEnableVertexAttribArray(gvNormalHandle);
		glEnableVertexAttribArray(gvTexCoordHandle);

		// Bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set the sampler texture unit to 0
		glUniform1i(gvSamplerHandle, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}
