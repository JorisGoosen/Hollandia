#include <SDL/SDL_image.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "SDLStage.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "Huis.vert.h"
#include "Huis.frag.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale
#include "glm/ext/matrix_clip_space.hpp" // glm::perspective
#include "glm/ext/scalar_constants.hpp" // glm::pi

GLuint programObject;
SDLStage* stage;


void handleEvent (SDL_Event &event) {
  
	
	
}


GLuint loadShader (GLenum type, const char *source) {
	
	GLuint shader;
	GLint compiled;
	
	shader = glCreateShader (type);
	
	if (shader == 0) {
		
		cerr << "Error creating shader" << endl;
		return 0;
		
	}
	
	glShaderSource (shader, 1, &source, NULL);
	glCompileShader (shader);
	
	glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled) {
		
		GLint infoLen = 0;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen > 1) {
			
			char* infoLog = (char*) malloc (sizeof (char) * infoLen);
			glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
			cerr << "Error compiling shader: " << infoLog << endl;
			free (infoLog);
			
		}
		
		glDeleteShader (shader);
		return 0;
		
	}
	
	return shader;

}


int initOpenGL () {

	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;
	
	vertexShader 	= loadShader (GL_VERTEX_SHADER, 	HuisVert);
	fragmentShader 	= loadShader (GL_FRAGMENT_SHADER,	HuisFrag);
	
	programObject = glCreateProgram ();
	
	if (programObject == 0) {
		
		cerr << "Could not create OpenGL program" << endl;
		return 0;
		
	}
	
	glAttachShader (programObject, vertexShader);
	glAttachShader (programObject, fragmentShader);
	glBindAttribLocation (programObject, 0, "vPosition");
	glLinkProgram (programObject);
	
	glGetProgramiv (programObject, GL_LINK_STATUS, &linked);
	
	if (!linked) {
		
		GLint infoLen = 0;
		
		glGetProgramiv (programObject, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen > 1) {
			
			char* infoLog = (char*) malloc (sizeof (char) * infoLen);
			glGetProgramInfoLog (programObject, infoLen, NULL, infoLog);
			cerr << "Error linking program: " << infoLog << endl;
			free (infoLog);
			
		}
		
		glDeleteProgram (programObject);
		return 0;
		
	}
	
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	return 1;
	
}



glm::mat4 camera(float Translate, glm::vec2 const& Rotate, float fov = 0.25f, float aspect = 4.0f / 3.0f, float near = 0.1f, float far = 100.0f)
{
	glm::mat4 	Projection 	= glm::perspective(glm::pi<float>() * fov, aspect, near, far);
	glm::mat4 	View 		= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
				View 		= glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
				View 		= glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 	Model 		= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

bool didAlready = false;

GLfloat vVertices[] = { 
		0.0f, 0.75f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

float xRot = 0.0f;
float yRot = 0.0f;

void render (SDL_Surface *screen) 
{
	glViewport (0, 0, screen -> w, screen -> h);
	
	glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
	glClear (GL_COLOR_BUFFER_BIT);
	
	


	glm::mat4 m = camera(1.0f, glm::vec2(xRot, yRot));

	glUseProgram (programObject);
	glUniformMatrix4fv(glGetUniformLocation(programObject, "ProjViewModel"), 1, GL_FALSE, glm::value_ptr(m));
	
	
//	if(!didAlready)
	{
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	
		glEnableVertexAttribArray (0);
	}
	
	glDrawArrays (GL_TRIANGLES, 0, 3);
	
	SDL_GL_SwapBuffers ();

}


void update (int deltaTime) 
{
	float sec = float(deltaTime) / 1000.0f;

	xRot += 0.10f * sec;
	yRot += 0.33f * sec;
	
}


void step () 
{
	
	stage -> step ();



	
}

EM_BOOL on_canvassize_changed(int eventType, const void *reserved, void *userData)
{
  int w, h, fs;
  emscripten_get_canvas_size(&w, &h, &fs);
  double cssW, cssH;
  emscripten_get_element_css_size(0, &cssW, &cssH);
  printf("Canvas resized: WebGL RTT size: %dx%d, canvas CSS size: %02gx%02g\n", w, h, cssW, cssH);

  stage->resize(cssW, cssH);
  return 0;
}


void enterSoftFullscreen(int scaleMode, int canvasResolutionScaleMode, int filteringMode)
{
  EmscriptenFullscreenStrategy s;
  memset(&s, 0, sizeof(s));
  s.scaleMode 					= scaleMode;
  s.canvasResolutionScaleMode 	= canvasResolutionScaleMode;
  s.filteringMode 				= filteringMode;
  s.canvasResizedCallback 		= on_canvassize_changed;
  EMSCRIPTEN_RESULT ret 		= emscripten_enter_soft_fullscreen(0, &s);
}

int main (int argc, char** argv) 
{
	double cssW, cssH;
	emscripten_get_element_css_size(0, &cssW, &cssH);
	stage = new SDLStage (cssW, cssH, 30, SDL_OPENGL);
	
	if (!initOpenGL ()) {
		
		cerr << "Error initializing OpenGL" << endl;
		return 1;
		
	}
	
	stage -> setCaption ("SimpleGL");
	stage -> setEventListener (&handleEvent);
	stage -> setRenderCallback (&render);
	stage -> setUpdateCallback (&update);
	
	#ifdef EMSCRIPTEN
	
	enterSoftFullscreen(EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH, EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF, EMSCRIPTEN_FULLSCREEN_FILTERING_BILINEAR);
	emscripten_set_main_loop (step, 0, true);
	
	#else
	
	while (stage -> active) {
		
		step ();
		
	}
	
	#endif
	
	delete stage;
	return 0;
	
}
