// defining constants
#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 0x7565
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1

typedef struct ebu_Image
{
    unsigned char magicNumber1[2];
    unsigned char magicNumber2[2];

    unsigned short *magicNumberValue1;
    unsigned short *magicNumberValue2;

    int dim1[2];
    int dim2[2];

    unsigned char *imageData1;
    unsigned char *imageData2;

    long numBytes1;
    long numBytes2;

    unsigned char tempPixel1;
    unsigned char tempPixel2;
} ebuImage;

int ebuRead1(ebuImage *data, FILE *fileName1);

int ebuRead2(ebuImage *data, FILE *fileName2);
