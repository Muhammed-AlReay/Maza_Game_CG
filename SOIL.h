#ifndef SOIL_H
#define SOIL_H
#include <GL/glut.h>
GLuint SOIL_load_OGL_texture(const char* filename, int flag, int new_texture_id, int texture_flag);
const char* SOIL_last_result();
#endif
