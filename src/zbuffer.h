#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_INCLUDED

#include "captcha3d.h"
#include "data.h"

#include <opencv/cv.h>

void zBufferGouraud(struct captcha3d_image *image, CvMat* buffer, Letter lettre, Material materiau);

#endif
