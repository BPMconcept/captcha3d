#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <argp.h>
#include <stdbool.h>
#include <string.h>

#include "captcha3d.h"
#include "file.h"
#include "data.h"
#include "zbuffer.h"
#include "transformations.h"
#include "illumination.h"

const char *argp_program_version = "Captcha 3D v1.0.0";
static char doc[] = "A fast and simple 3D Captcha generator.";
static char args_doc[] = "[FILENAME]...";

static struct argp_option options[] = {
    {"string", 's', "STRING", 0, "The set of characters used to draw the image"},
    {"file", 'o', "captcha.png", 0, "The output image file"},
    {"width", 'w', "auto", 0, "The output image width"},
    {"height", 'h', "100", 0, "The output image height"},
    {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct Configuration *config = state->input;

    switch (key) {
    case 's':
        config->string = arg;
        break;
    case 'o':
        config->file = arg;
        break;
    case 'h':
        config->height = atoi(arg);
        break;
    case ARGP_KEY_END:
        if (config->string == NULL){
            argp_usage(state);
        }
        return 0;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = {options, parse_opt, NULL, doc, 0, 0, 0};

int main(int argc, char *argv[])
{
    struct Configuration config;

    config.string = NULL;
    config.file = "captcha.png";
    config.width = 0;
    config.height = 100;
    config.aliasing = 0;

    argp_parse(&argp, argc, argv, 0, 0, &config);

    if (config.width == 0) {
        config.width = config.height * strlen(config.string) * 2 / 3;
    }

    // Création de l'image
//    const int width = (100 + config.aliasing) * config.width / 100;
//    const int height = (100 + config.aliasing) * config.height / 100;

    //Seed pour nombbres aléatoires
    srand(time(NULL)*getpid());

    // Lancement du Z-Buffer
    captcha3d_generate(&config);

//    // Redimensionnement à la taille voulue
//    if (config.aliasing > 0) {
//        cvResize(img, img_final, CV_INTER_LINEAR);
//    }

    return EXIT_SUCCESS;
}


