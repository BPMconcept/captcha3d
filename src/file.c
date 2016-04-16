#include "file.h"

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

void save_png(struct captcha3d_config *config, struct captcha3d_image *image)
{
    FILE *fp = fopen(config->file, "wb");
    if(!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        config->width,
        config->height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);

    png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * config->height);

    for (int y=0; y<config->height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png, info));
    }

    for (int y = 0; y < config->height; ++y) {
        png_byte *row = row_pointers[y];

        for (int x = 0; x < config->width; ++x) {
            png_byte* byte = &(row[x*4]);
            struct captcha3d_color *pixel = captcha3d_image_get(image, x, y);
            byte[0] = pixel->red;
            byte[1] = pixel->green;
            byte[2] = pixel->blue;
            byte[3] = pixel->alpha;
        }
    }

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    for (int y = 0; y < config->height; y++) {
        free(row_pointers[y]);
    }

    free(row_pointers);
    fclose(fp);
}
