#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#include "vector.h"
#include "letter.h"

#define Z_PROJECTION_CENTER 			600

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

typedef struct {
    float ia;
    float ip;
    Vector3d direction;
} Light;

typedef struct {
    struct Color couleur;
    float ka;
    float kd;
    float ks;
    int n;
} Material;

struct Color color_random();
struct Color color_gouraud(float coeff, struct Color couleur);
void color_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material materiau);

#endif
