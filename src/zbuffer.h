#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "captcha3d.h"
#include "letter.h"
#include "data.h"

struct zBufferData
{
    struct Image *image;
    float data[];
};

struct zBufferData* z_buffer_data_allocate(struct Image *image);

void z_buffer_data_release(struct zBufferData *buffer);

void z_buffer_run(struct zBufferData *buffer, const Letter *letter, Material materiau);

#endif
