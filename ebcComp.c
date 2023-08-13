#include <stdio.h>
#include <stdlib.h>

#include "ebcRead.h"

int main(int argc, char **argv)
{
    // declaring utility readIn to read in file and return any errors
    int ebcRead(ebcImage *data, FILE *inputFile1);
    int ebcRead(ebcImage *data, FILE *inputFile2);

    // check for correct usage
    if (argc == 1)
    {
        printf("Usage: ebcComp file1 file2\n");
	    return SUCCESS;
    }

    // validate that user has enter 2 arguments (plus the executable name)
    if (argc != 3)
    {
        printf("ERROR: Bad Arguments\n");
        return BAD_ARGS;
    }

    // open the input file in read mode
    // and create a pointer to the first argument to get first file name
    FILE *inputFile1 = fopen(argv[1], "r");
    char **firstArg1 = &argv[1];

    // check file opened successfully
    if (!inputFile1)
    {
        // ensure that file is closed before exit
        printf("ERROR: Bad File Name (%s)\n", *firstArg1);
        return BAD_FILE;
    }

    // insialising structure of type ebuImage
    ebcImage *data = malloc(sizeof(ebcImage));

    // capturing the value returned from readIn file
    int value1 = ebcRead1(data, inputFile1);

    // check which values have been returned, print message and return value
    switch (value1)
    {
    case BAD_MAGIC_NUMBER:
        printf("ERROR: Bad Magic Number (%s)\n", *firstArg1);
        return BAD_MAGIC_NUMBER;
    case BAD_DIM:
        printf("ERROR: Bad Dimensions (%s)\n", *firstArg1);
        return BAD_DIM;
    case BAD_MALLOC:
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    case BAD_DATA:
        printf("ERROR: Bad Data (%s)\n", *firstArg1);
        return BAD_DATA;
    default:
        break;
    }

    // close inputFile1
    fclose(inputFile1);

    // open second input file in read mode
    FILE *inputFile2 = fopen(argv[2], "rb");
    // pointer to second file name
    char **secondArg = &argv[2];
    
    // check file opened successfully
    if (!inputFile2)
    {
        // free allocated memory before exit
        free(data->imageData1);
        free(data);
        printf("ERROR: Bad File Name (%s)\n", *secondArg);
        return BAD_FILE;
    }

    // capturing the value returned from readIn file
    int value2 = ebcRead1(data, inputFile2);

    // check which values have been returned, print message and return value
    switch (value2)
    {
    case BAD_MAGIC_NUMBER:
        printf("ERROR: Bad Magic Number (%s)\n", *secondArg);
        return BAD_MAGIC_NUMBER;
    case BAD_DIM:
        printf("ERROR: Bad Dimensions (%s)\n", *secondArg);
        return BAD_DIM;
    case BAD_MALLOC:
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    case BAD_DATA:
        printf("ERROR: Bad Data (%s)\n", *secondArg);
        return BAD_DATA;
    default:
        break;
    }

    // close inputFile2
    fclose(inputFile2);

    // compare the data from the two files:

    // start with magic number values
    if (*data->magicNumberValue1 != *data->magicNumberValue2)
    {
        // free allocated memory before exit
        free(data->imageData1);
        free(data->imageData2);
        free(data);
        printf("DIFFERENT\n");
        return SUCCESS;
    }

    // check dimensions
    if ((data->dim1[0] != data->dim2[0]) || (data->dim1[1] != data->dim2[1]))
    {
        // free allocated memory before exit
        free(data->imageData1);
        free(data->imageData2);
        free(data);
        printf("DIFFERENT\n");
        return SUCCESS;
    }

    // and check the pixel values
    for (int n=0; n<data->numBytes1; n++)
    {
        if(data->imageData1[n]!=data->imageData2[n])
        {
            // free allocated memory before exit
            free(data->imageData1);
            free(data->imageData2);
            free(data);
            printf("DIFFERENT\n");
            return SUCCESS;
        }
    }

    // free allocated memory before exit
    free(data->imageData1);
    free(data->imageData2);
    free(data);

    // if we have not exited on different data, must be identical
    printf("IDENTICAL\n");
    return SUCCESS;
}