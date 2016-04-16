#ifndef PARAM_H_INCLUDED
#define PARAM_H_INCLUDED

#include <stddef.h>
#include <opencv/cv.h>

// Variables globales
//char *cfg_str;
//char *cfg_output;
//int cfg_width;
//int cfg_height;
int cfg_window;
int cfg_deform_sin;
int cfg_degrade;
//float cfg_aliasing;
CvScalar cfg_background;

int checkParams(int argc, char *argv[]);
void initGlobalParams();
int checkChar(char *string);

#endif // PARAM_H_INCLUDED
