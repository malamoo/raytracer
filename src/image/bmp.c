#include <stdio.h>
#include <stdlib.h>
#include "program.h"
#include "gfxmath.h"
#include "raytracer.h"
#include "image.h"

static int round4(int x);

enum {
    OFFSET = 0x36,    /* pixel array offset */
    DIBSIZE = 0x28,   /* DIB header size */
    NCPLANE = 0x01,   /* # color planes */
    CDEPTH = 0x18,    /* color depth */
    PRINTRES = 0x2e23 /* print resolution */
};

void writebmpimage(char *path, image image)
{
    uchar sig[] = {
        'B',
        'M'
    };
    uint header[] = {
        0x00,
        0x00,
        OFFSET,
        DIBSIZE,
        IMGWIDTH,
        IMGHEIGHT,
        (CDEPTH << 16) | NCPLANE,
        0x00,
        0x00,
        PRINTRES,
        PRINTRES,
        0x00,
        0x00,
    };
    FILE *fp;
    uchar *pixel;
    size_t pixelsize;
    int rowsize;
    int i, j, k;

    fp = fopen(path, "wb");
    if (fp == NULL)
        eprintf("can't open file %s", path);

    /* pad row to a multiple of 4 bytes */
    rowsize = round4(3 * IMGWIDTH);
    pixelsize = rowsize * IMGHEIGHT;

    pixel = emalloc(pixelsize);
    for (i = 0; i < pixelsize; i++)
        pixel[i] = 0x00;

    for (i = 0; i < IMGHEIGHT; i++) {
        for (j = 0; j < IMGWIDTH; j++) {
            k = i * rowsize + j * 3;
            /* copy RGB in reverse order */
            pixel[k] = image[i][j].b;
            pixel[k + 1] = image[i][j].g;
            pixel[k + 2] = image[i][j].r;
        }
    }

    /* assign header fields */
    header[0] = sizeof(sig) + sizeof(header) + pixelsize; /* file size */

    fwrite(sig, sizeof(sig), 1, fp);
    fwrite(header, sizeof(header), 1, fp);
    fwrite(pixel, pixelsize, 1, fp);
    fclose(fp);

    free(pixel);
}

static int round4(int x)
{
    return x % 4 == 0 ? x : x - x % 4 + 4;
}
