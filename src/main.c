#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "helper.h"
#include "gfxmath.h"
#include "image.h"
#include "raytrace.h"

enum {
    WIDTH = 1920,
    HEIGHT = 1080
};

static vec3 eye = { 0, 0, 0 };
static vec3 viewdir = { 0, 0, -1 };

int main(void)
{
    Cframe frame;
    Ray ray;
    image img;
    Hit hit;
    float r, l, t, b;
    float u, v;
    int i, j;

    cframecamera(eye, viewdir, &frame);

    r = WIDTH / 2.0f;
    l = -r;
    t = HEIGHT / 2.0f;
    b = -t;

    img = emalloc(WIDTH * HEIGHT * sizeof(Rgb));

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            u = l + (r - l) * ((float) j + 0.5f) / (float) WIDTH;
            v = b + (t - b) * ((float) i + 0.5f) / (float) HEIGHT;
            rayortho(u, v, &frame, &ray);
            hitscene(&ray, 0, INFINITY, &hit);
            if (hit.t < INFINITY) {
                img[i * WIDTH + j] = hit.surface->color;
            } else {
                img[i * WIDTH + j] = black;
            }
        }
    }

    imgwritebmp("scene.bmp", img, WIDTH, HEIGHT);
    free(img);

    return 0;
}
