#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <argp.h>
#include <stdbool.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "captcha3d.h"
#include "file.h"
#include "data.h"
#include "zbuffer.h"
#include "transformations.h"
#include "illumination.h"
#include "param.h"

const char *argp_program_version = "Captcha 3D v1.0.0";
static char doc[] = "A fast and simple 3D Captcha generator.";
static char args_doc[] = "[FILENAME]...";

static struct argp_option options[] = {
    {"string", 's', "STRING", 0, "The set of characters used to draw the image"},
    {"file", 'o', "captcha.png", OPTION_ARG_OPTIONAL, "The output image file"},
    {"width", 'w', "auto", OPTION_ARG_OPTIONAL, "The output image width"},
    {"height", 'h', "100", OPTION_ARG_OPTIONAL, "The output image height"},
    {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct captcha3d_config *config = state->input;

    switch (key) {
    case 's':
        config->string = arg;
        break;
    case 'o':
        config->file = arg;
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
    struct captcha3d_config config;

    config.string = NULL;
    config.file = "captcha.png";
    config.width = 0;
    config.height = 100;
    config.aliasing = 0;

    argp_parse(&argp, argc, argv, 0, 0, &config);

    if (config.width == 0) {
        config.width = config.height * strlen(config.string) * 2 / 3;
    }

    // Vérification des paramètres
//    if (!checkParams(argc, argv)) {
//        return EXIT_FAILURE;
//    }

    // Création de l'image
    const int width = (100 + config.aliasing) * config.width / 100;
    const int height = (100 + config.aliasing) * config.height / 100;

    struct captcha3d_color background = {255, 255, 255, 255};
    struct captcha3d_image *image = captcha3d_image_init(width, height);
    captcha3d_image_fill(image, background);

    //Seed pour nombbres aléatoires
    srand(time(NULL)*getpid());

//    // Affichage du fond d'écran
//    if (cfg_degrade == 1) {
//        degrade(img, width, height, couleur);
//    } else {
//        cvSet(img, cfg_background, 0);
//    }

    // Lancement du Z-Buffer
    captcha3d_generate(image, config.string, couleurAleatoire());

//    // Redimensionnement à la taille voulue
//    if (config.aliasing > 0) {
//        cvResize(img, img_final, CV_INTER_LINEAR);
//    }

    save_png(&config, image);

    captcha3d_image_release(image);

    return EXIT_SUCCESS;
}


