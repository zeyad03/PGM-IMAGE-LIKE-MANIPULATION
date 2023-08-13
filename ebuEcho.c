#include <stdio.h>
#include <stdlib.h>

#include "ebuRead.h"

int main(int argc, char **argv)
{
    // declaring utility readIn to read in file and return any errors
    int ebuRead1(ebuImage *data, FILE *fileName);

    // check for correct usage
    if (argc == 1)
    {
        printf("Usage: ebuEcho file1 file2\n");
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
    FILE *inputFile = fopen(argv[1], "rb");
    char **firstArg = &argv[1];

    // check file opened successfully
    if (!inputFile)
    {
        // ensure that file is closed before exit
        printf("ERROR: Bad File Name (%s)\n", *firstArg);
        return BAD_FILE;
    }

    // allocate data structure
    ebuImage *data = malloc(sizeof(ebuImage));

    // capturing the value returned from readIn file
    int value1 = ebuRead1(data, inputFile);

    // check which values have been returned, print message and return value
    switch (value1)
    {
    case BAD_MAGIC_NUMBER:
        printf("ERROR: Bad Magic Number (%s)\n", *firstArg);
        return BAD_MAGIC_NUMBER;
    case BAD_DIM:
        printf("ERROR: Bad Dimensions (%s)\n", *firstArg);
        return BAD_DIM;
    case BAD_MALLOC:
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    case BAD_DATA:
        printf("ERROR: Bad Data (%s)\n", *firstArg);
        return BAD_DATA;
    default:
        break;
    }

    // close inputFile
    fclose(inputFile);

    // open the output file in write mode
    // and create a pointer to second argument to get second file name
    FILE *outputFile = fopen(argv[2], "wb");
    char **secondArg = &argv[2];

    // validate that the file has been opened correctly
    if (outputFile == NULL)
    {
        // ensure that allocated data is freed before exit
        free(data->imageData1);
        free(data);
        printf("ERROR: Bad File Name (%s)\n", *secondArg);
        return BAD_FILE;
    }

    // write the header data in one block
    int check = fprintf(outputFile, "eb\n%d %d\n", data->dim1[0], data->dim1[1]);
    // and use the return from fprintf to check that we wrote
    if (!check)
    {
        // ensure that allocated data is freed before exit
        free(data->imageData1);
        fclose(outputFile);
        free(data);
        printf("ERROR: Bad Output (%s)\n", *secondArg);
        return BAD_OUTPUT;
    }

    // iterate though the array and print out pixel values
    for (int current = 0; current < data->numBytes1; current++)
        {
        // if we are at the end of a row ((current+1)%width == 0) then write a newline, otherwise a space.
        check = fprintf(outputFile, "%c%c", data->imageData1[current], ((current + 1) % data->dim1[1]) ? ' ' : '\n');
        if (check < 0)
            {
            // ensure that allocated data is freed before exit
            free(data->imageData1);
            fclose(outputFile);
            free(data);
            printf("ERROR: Bad Output\n");
            return BAD_OUTPUT;
            }
        }

    // free allocated memory before exit
    free(data->imageData1);
    //free(data->magicNumberValue);
    free(data);
    // close the output file before exit
    fclose(outputFile);
    
    // print final success message and return
    printf("ECHOED\n");
    return SUCCESS;
}
