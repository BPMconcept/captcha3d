#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "captcha3d.h"
#include "letter.h"
#include "data.h"

#include <opencv/cv.h>

void z_buffer(struct captcha3d_image *image, CvMat* buffer, const Letter *letter, Material materiau);

#endif
