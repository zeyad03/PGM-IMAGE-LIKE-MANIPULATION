
// defining constants
#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 25445
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1

typedef struct ebc_Image {
    // defining variables
    unsigned char magicNumber1[2];
    unsigned char magicNumber2[2];

    unsigned short *magicNumberValue1;
    unsigned short *magicNumberValue2;

    int dim1[2];
    int dim2[2];

    unsigned int *imageData1;
    unsigned int *imageData2;

    long numBytes1;
    long numBytes2;

    unsigned int tempPixel1;
    unsigned int tempPixel2;
} ebcImage;

int ebcRead1(ebcImage *data, FILE *fileName1);

int ebcRead2(ebcImage *data, FILE *fileName2);
