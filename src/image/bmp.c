#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "image.h"

static int round4(int x);

enum {
    OFFSET = 0x36,    // pixel array offset
    DIBSIZE = 0x28,   // DIB header size
    NCPLANE = 0x01,   // # color planes
    CDEPTH = 0x18,    // color depth
    PRINTRES = 0x2e23 // print resolution
};

void imgwritebmp(char *path, image img, int width, int height)
{
    FILE *fp;
    uchar sig[] = {
        'B',
        'M'
    };
    uint header[] = {
        0x00,
        0x00,
        OFFSET,
        DIBSIZE,
        width,
        height,
        (CDEPTH << 16) | NCPLANE,
        0x00,
        0x00,
        PRINTRES,
        PRINTRES,
        0x00,
        0x00,
    };
    uchar *pixel;
    size_t npixel;
    int padwidth;
    int i, j, k, l;

    fp = fopen(path, "wb");
    if (fp == NULL)
        eprintf("can't open file %s", path);

    // pad width to a multiple of 4 bytes
    padwidth = round4((int) sizeof(Rgb) * width);
    npixel = padwidth * height;

    pixel = emalloc(npixel * sizeof(uchar));
    for (i = 0; i < npixel; i++)
        pixel[i] = 0x00;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            k = i * padwidth + j * 3;
            l = i * width + j;
            pixel[k] = img[l].b;
            pixel[k + 1] = img[l].g;
            pixel[k + 2] = img[l].r;
        }
    }

    // set file size in header
    header[0] = sizeof(sig) + sizeof(header) + npixel * sizeof(uchar);

    fwrite(sig, sizeof(sig), 1, fp);
    fwrite(header, sizeof(header), 1, fp);
    fwrite(pixel, npixel * sizeof(uchar), 1, fp);
    fclose(fp);

    free(pixel);
}

static int round4(int x)
{
    return x % 4 == 0 ? x : x - x % 4 + 4;
}