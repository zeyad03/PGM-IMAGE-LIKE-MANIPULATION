#include <stdio.h>
#include <stdlib.h>

#include "ebcRead.h"

int ebcRead1(ebcImage *data, FILE *fileName1)
{
    // cast char array to short
    data->magicNumberValue1 = (unsigned short *)data->magicNumber1;

    // get first 2 characters which should be magic number
    data->magicNumber1[0] = getc(fileName1);
    data->magicNumber1[1] = getc(fileName1);

    // checking against the casted value due to endienness
    if (*data->magicNumberValue1 != MAGIC_NUMBER)
    {
        // ensure that allocated data is freed before exit
        fclose(fileName1);
        free(data);
        return BAD_MAGIC_NUMBER;
    }

    // scan for dimenstions
    int check = fscanf(fileName1, "%d %d", &data->dim1[0], &data->dim1[1]);
    // and capture fscanfs return to ensure we got 2 values lie within range
    if (check != 2 || data->dim1[0] < MIN_DIMENSION || data->dim1[1] < MIN_DIMENSION
        || data->dim1[0] > MAX_DIMENSION || data->dim1[1] > MAX_DIMENSION)
    {
        // ensure that allocated data is freed before exit
        fclose(fileName1);
        free(data);
        return BAD_DIM;
    }

    // calculate total size and allocate memory for array
    data->numBytes1 = data->dim1[0] * data->dim1[1];
    data->imageData1 = (unsigned int *)malloc(data->numBytes1 * sizeof(unsigned int));

    // if malloc is unsuccessful, it will return a null pointer
    if (data->imageData1 == NULL)
    {
        // ensure that allocated data is freed before exit
        free(data->imageData1);
        fclose(fileName1);
        free(data);
        return BAD_MALLOC;
    }

    // read in ech grey value from the file
    for (int current = 0; current < data->numBytes1; current++)
    {
        // reading in
        check = fscanf(fileName1, "%u", &data->tempPixel1);

        // validate that we have captured 1 pixel value
        // or the pixel value isn't greater than 31
        // or the data exceeded the specified space
        if (check != 1 || data->tempPixel1 > 31
            || (current == data->numBytes1 - 1
            && fscanf(fileName1, "%u", &data->tempPixel1) == 1))
        {
            // ensure that allocated data is freed before exit
            free(data->imageData1);
            fclose(fileName1);
            return BAD_DATA;
        }
        data->imageData1[current] = data->tempPixel1;
    }

    return SUCCESS;
}

int ebcRead2(ebcImage *data, FILE *fileName2)
{
    // cast char array to short
    data->magicNumberValue2 = (unsigned short *)data->magicNumber2;

    // get first 2 characters which should be magic number
    data->magicNumber2[0] = getc(fileName2);
    data->magicNumber2[1] = getc(fileName2);

    // checking against the casted value due to endienness
    if (*data->magicNumberValue2 != MAGIC_NUMBER)
    {
        // ensure that allocated data is freed before exit
        fclose(fileName2);
        free(data);
        return BAD_MAGIC_NUMBER;
    }

    // scan for dimenstions
    int check = fscanf(fileName2, "%d %d", &data->dim2[0], &data->dim2[1]);
    // and capture fscanfs return to ensure we got 2 values lie within range
    if (check != 2 || data->dim2[0] < MIN_DIMENSION || data->dim2[1] < MIN_DIMENSION
        || data->dim2[0] > MAX_DIMENSION || data->dim2[1] > MAX_DIMENSION)
    {
        // ensure that allocated data is freed before exit
        fclose(fileName2);
        free(data);
        return BAD_DIM;
    }

    // calculate total size and allocate memory for array
    data->numBytes2 = data->dim2[0] * data->dim2[1];
    data->imageData2 = (unsigned int *)malloc(data->numBytes2 * sizeof(unsigned int));

    // if malloc is unsuccessful, it will return a null pointer
    if (data->imageData2 == NULL)
    {
        // ensure that allocated data is freed before exit
        free(data->imageData2);
        fclose(fileName2);
        free(data);
        return BAD_MALLOC;
    }

    // read in ech grey value from the file
    for (int current = 0; current < data->numBytes2; current++)
    {
        // reading in
        check = fscanf(fileName2, "%u", &data->tempPixel2);

        // validate that we have captured 1 pixel value
        // or the pixel value isn't greater than 31
        // or the data exceeded the specified space
        if (check != 1 || data->tempPixel2 > 31
            || (current == data->numBytes2 - 1
            && fscanf(fileName2, "%u", &data->tempPixel2) == 1))
        {
            // ensure that allocated data is freed before exit
            free(data->imageData2);
            fclose(fileName2);
            return BAD_DATA;
        }
        data->imageData2[current] = data->tempPixel2;
    }

    return SUCCESS;
}
