#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{   
    FILE* fp;
    long * array;
    long fplength; 
    int numread;

    fp = fopen("filename", "rb");

    if (fp == NULL)
    {
        *size = 0;
        return NULL;
    }  

    fseek(fp, 0, SEEK_END); 
    fplength = ftell(fp); 
    if (fplength = 0)
    {
        array = 0;
    }
    else
    {
        fseek(fp, 0, SEEK_SET); 
        array = (long *)malloc(fplength); 
        numread = fread(array, sizeof(long), fplength/sizeof(long), fp); 
        fclose(fp); 
        *size = (int)numread;
    }

    return array;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    long numWrite;
    FILE *f;
    if (array == NULL || size == 0)
    {
        array = 0;
        f = fopen("filename", "wb");
        numWrite = fwrite(array, sizeof(long), size, f);
    }
    else
    {
        f = fopen("filename", "wb");
        numWrite = fwrite(array, sizeof(long), size, f);
    }
    fclose(f);
    return numWrite;
}
static int counter(int val)
{
    if(val < 1)
    {
        return 0;
    }

    if (val == 1)
    {
        return 1;
    }

    int serVal = 1;

    for(int i = 2; i <= val; i++)
    {
        serVal = 3 * serVal + 1;
    }

    return serVal;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int count = 1; 
    int h = 1; 
    while(h < size)
    {
        count++;
        h = counter(count);
    }
    count--; 
    *n_comp = 0;

    // Shell Sort
    int k;
    for (k = counter(count); k > 0; k = counter(--count)) 
    {
        long temparr;
        int i;
        int j;
        for (j = k; j < size; j++)
        {
            temparr = array[j];
            i = j;
            while (i >= k && array[i-k] > temparr)
            {
                array[i] = array[i - k];
                i = i - k;
                *n_comp = *n_comp + 1;
            }
            *n_comp = *n_comp + 1;
            array[i] = temparr;
        }
    } 
return;
}