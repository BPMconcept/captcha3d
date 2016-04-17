#include "color.h"

struct captcha3d_color random_color()
{
    struct captcha3d_color couleur;

    couleur.red = rand() % 256;
    couleur.green = rand() % 256;
    couleur.blue = rand() % 256;
    couleur.alpha = 255;

    return couleur;
}
