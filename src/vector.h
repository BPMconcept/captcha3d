#ifndef CAPTCHA3D_VECTOR_H
#define CAPTCHA3D_VECTOR_H

typedef struct {
    float x;
    float y;
    float z;
} Vector3d;

typedef struct {
    float x;
    float y;
} Vector2d;

Vector3d normalize(const Vector3d *vector);
Vector3d vector_add(const Vector3d *n1, const Vector3d *n2);

#endif
