/*
 *
 * http://androgeek.info/?p=331#more-331
 *
 */

void Particle::init()
{
    char gVertexShader[] =
          "uniform mat4 u_mvpMatrix;                            \n"
          "uniform float u_time;                                \n"
          "uniform vec3 u_centerPosition;                       \n"
          "attribute float a_lifetime;                          \n"
          "attribute vec3 a_startPosition;                      \n"
          "attribute vec3 a_endPosition;                        \n"
          "varying float v_lifetime;                            \n"
          "void main()                                          \n"
          "{                                                    \n"
          "  if ( u_time <= a_lifetime )                        \n"
          "  {                                                  \n"
          "    gl_Position.xyz = a_startPosition +              \n"
          "                      (u_time * a_endPosition);      \n"
          "    gl_Position=(u_mvpMatrix*gl_Position);           \n"
          "  }                                                  \n"
          "  v_lifetime = 1.0 - ( u_time / a_lifetime );        \n"
          "  v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );       \n"
          "  gl_PointSize =sin( v_lifetime*v_lifetime *3.1416 ) \n"
          "                     * 80.0;                         \n"
          "}";

    char gFragmentShader[] =
          "precision mediump float;                             \n"
          "uniform vec4 u_color;                                \n"
          "varying float v_lifetime;                            \n"
          "uniform sampler2D s_texture;                         \n"
          "void main()                                          \n"
          "{                                                    \n"
          "  vec4 texColor;                                     \n"
          "  texColor = texture2D( s_texture, gl_PointCoord );  \n"
          "  gl_FragColor =  texColor;                          \n"
          "  gl_FragColor.a *= (v_lifetime);}                   \n";

    if(gFragmentShader!=0 && gVertexShader!=0)
    {
        gProgram = createProgram(gVertexShader, gFragmentShader);
    }
    if (!gProgram)
    {
        LOGE("Could not create program for particle.");
        return;
    }
    LOGI("particle program ok");
<span id="more-331"></span>
    lifetimeLoc = glGetAttribLocation ( gProgram, "a_lifetime" );
    startPositionLoc = glGetAttribLocation ( gProgram, "a_startPosition" );
    endPositionLoc = glGetAttribLocation ( gProgram, "a_endPosition" );

    // Get the uniform locations
    mvpLoc = glGetUniformLocation ( gProgram, "u_mvpMatrix" );
    timeLoc = glGetUniformLocation ( gProgram, "u_time" );
    centerPositionLoc = glGetUniformLocation ( gProgram, "u_centerPosition" );
    colorLoc = glGetUniformLocation ( gProgram, "u_color" );
    samplerLoc = glGetUniformLocation ( gProgram, "s_texture" );

    LOGI("glGetAttribLocation(\"a_lifetime\") = %d\n",lifetimeLoc);
    LOGI("glGetAttribLocation(\"a_startPosition\") = %d\n",startPositionLoc);
    LOGI("glGetAttribLocation(\"a_endPosition\") = %d\n",endPositionLoc);
    LOGI("glGetAttribLocation(\"u_mvpMatrix\") = %d\n",mvpLoc);
    LOGI("glGetAttribLocation(\"u_time\") = %d\n",timeLoc);
    LOGI("glGetAttribLocation(\"u_centerPosition\") = %d\n",centerPositionLoc);
    LOGI("glGetAttribLocation(\"u_color\") = %d\n",colorLoc);
    LOGI("glGetAttribLocation(\"s_texture\") = %d\n",samplerLoc);
    LOGI("values ok");

    // Use tightly packed data
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //LOGI("Particle Tex:%s",tex_name);
    int texidx=texmng->getIndex(tex_name);
    //LOGI("Particle Tex:%s   id %d",tex_name,texidx);
    if(texmng->tex_id[texidx]==-1)
    {
        int w=texmng->tex_w[texidx];
        int h=texmng->tex_h[texidx];
        glGenTextures(1, &tex_id);
        tex_id = createSimpleTexture2D(tex_id, texmng->pixels[texidx],w, h, 4);
        texmng->tex_id[texidx]=tex_id;
        LOGI("Particle Tex ID %d",tex_id);
    }
    else
    {
        tex_id=texmng->getID(tex_name);
        LOGI("Already Loaded:Particle Tex ID %d",tex_id);
    }

    srand ( 0 );
    for ( int i = 0; i < NUM_PARTICLES; i++ )
    {
        float *particleData =&mParticleData[i * PARTICLE_SIZE];

        // Lifetime of particle
        (*particleData++) = 1.0f*( (float)(rand() % 10000) / 10000.0f );
        // End position of particle
        (*particleData++) = 30.000f*(( (float)(rand() % 10000) / 5000.0f ) - 1.0f);
        (*particleData++) = 30.000f*(( (float)(rand() % 10000) / 5000.0f ) - 1.0f);
        (*particleData++) = 30.000f*(( (float)(rand() % 10000) / 5000.0f ) - 1.0f);

        // Start position of particle
        (*particleData++) = 5.000f*(( (float)(rand() % 10000) / 40000.0f ) - 0.125f);//40000 0.125
        (*particleData++) = 5.000f*(( (float)(rand() % 10000) / 40000.0f ) - 0.125f);
        (*particleData++) = 5.000f*(( (float)(rand() % 10000) / 40000.0f ) - 0.125f);

    }

    // Initialize time to cause reset on first update
    time = 1.0f;
    LOGI("Particle init OK");

}

//=================================================================
gl_PointSize =sin( v_lifetime*v_lifetime *3.1416 );

void Particle::Update(float timeDelta)
{
	time+=0.01f*timeDelta;

	if ( time >= 1.0f )
	{
		time = 0.0f;
	}

}

void Particle::Render(ESMatrix &mvp)
{
    checkGlError("Render");
    glUseProgram ( gProgram );
    checkGlError("glUseProgram");
    glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, (GLfloat*) &mvp.m[0][0] );
    glUniform1f ( timeLoc, time );
    checkGlError("glUniformMatrix4fv");
    glEnableVertexAttribArray ( lifetimeLoc );
    glEnableVertexAttribArray ( endPositionLoc );
    glEnableVertexAttribArray ( startPositionLoc );
    checkGlError("glEnableVertexAttribArray");
    glUniform1i ( samplerLoc, 0 );
    checkGlError("samplerLoc");
    // Load the vertex attributes
    glVertexAttribPointer ( lifetimeLoc, 1, GL_FLOAT,
                            GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat),
                            &mParticleData[0] );
    checkGlError("lifetimeLoc");
    glVertexAttribPointer ( endPositionLoc, 3, GL_FLOAT,
                            GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat),
                            &mParticleData[1] );
    checkGlError("endPositionLoc");
    glVertexAttribPointer ( startPositionLoc, 3, GL_FLOAT,
                            GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat),
                            &mParticleData[4] );
    checkGlError("startPositionLoc");

    // Blend particles
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable(GL_DEPTH_TEST);
    // Bind the texture
    glActiveTexture ( GL_TEXTURE0 );
    int texidx=texmng->getIndex(tex_name);
    glBindTexture(GL_TEXTURE_2D, texmng->tex_id[texidx]);
    checkGlError("Particle glBindTexture");

    // Set the sampler texture unit to 0

    glDrawArrays( GL_POINTS, 0, NUM_PARTICLES*time*time );

    glDisable(GL_BLEND);
}
