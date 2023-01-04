typedef struct Rgb Rgb;

enum {
    IMGWIDTH = 1920,
    IMGHEIGHT = 1080
};

struct Rgb {
    uchar r;
    uchar g;
    uchar b;
};

typedef Rgb image[IMGHEIGHT][IMGWIDTH];

void writebmpimage(char *path, image image);
