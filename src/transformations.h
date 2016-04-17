#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_H_INCLUDED

#include "data.h"

void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres);
void letter_transform(Letter *letter, int i, int width, int height, int z, int marge, float e, float offset);
void letter_translate(Letter *lettre, Vector3d vector);
void scale(Letter *letter, float coeff);
Vector3d barycentre(Letter lettre);
Letter deformation(Letter lettre);
Letter deformation_sin(Letter lettre, char type);
Vector3d letter_apply_matrix(Vector3d m[3], Vector3d q);
void letter_rotate(Letter *letter, Vector3d angles);
Vector3d calculterTranslation(int width, int height, int marge, float z);
float calculOffsetX(float z, int width, int marge);

#endif
