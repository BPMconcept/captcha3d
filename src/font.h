#ifndef ARIAL_H
#define ARIAL_H

#include "data.h"

enum Captcha3dFont {
    FONT_ARIAL
};

const Letter* get_letter(enum Captcha3dFont font, char letter);

#endif
