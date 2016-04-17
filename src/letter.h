#ifndef LETTER_H
#define LETTER_H

#include <stdlib.h>

#include "font.h"
#include "vector.h"

typedef struct {
    int a;
    int b;
    int c;
} Triangle;

typedef struct {
    size_t pointsNumber;
    Vector3d points[500];
    size_t facesNumber;
    Triangle faces[800];
} Letter;

const Letter* get_letter(enum Font font, char letter);

void letter_translate(Letter *lettre, Vector3d vector);
void letter_rotate(Letter *letter, Vector3d angles);
void letter_scale(Letter *letter, float coeff);
void letter_transform(Letter *letter, int i, int width, int height, int z, int marge, float e, float offset);

void compute_normal_vectors(Vector3d tab[], const Letter *letter);
Vector3d face_normal_vector(const Triangle *face, const Vector3d points[]);

#endif
