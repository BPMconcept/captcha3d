#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_INCLUDED

#include "captcha3d.h"
#include "data.h"

#include <opencv/cv.h>

void z_buffer(struct captcha3d_image *image, CvMat* buffer, const Letter *letter, Material materiau);

#endif
