#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "data.h"
#include "letter.h"

void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres);

Vector3d barycentre(Letter lettre);
Letter deformation(Letter lettre);
Letter deformation_sin(Letter lettre, char type);

Vector3d calculterTranslation(int width, int height, int marge, float z);
float calculOffsetX(float z, int width, int marge);

#endif
