#include <math.h>

#include "vector.h"

Vector3d normalize(const Vector3d *vector)
{
    Vector3d normal = *vector;
    float size = sqrt((vector->x) * (vector->x) + (vector->y) * (vector->y) + (vector->z) * (vector->z));

    normal.x /= size;
    normal.y /= size;
    normal.z /= size;

    return normal;
}

Vector3d vector_add(const Vector3d *n1, const Vector3d *n2)
{
    Vector3d n;

    n.x = n1->x + n2->x;
    n.y = n1->y + n2->y;
    n.z = n1->z + n2->z;

    return n;
}
