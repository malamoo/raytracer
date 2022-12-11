typedef struct Rgb Rgb;
typedef Rgb *image;

struct Rgb {
    uchar r;
    uchar g;
    uchar b;
};

void imgwritebmp(char *path, image img, int width, int height);

extern Rgb black;
extern Rgb white;
extern Rgb red;
extern Rgb green;
extern Rgb blue;
extern Rgb yellow;
