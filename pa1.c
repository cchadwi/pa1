#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char * * argv)
{
    if(argc != 4) { //Checks to make sure the number of arguments passed isn't 4
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "-a") == 0) //Array Shell Sorting -a bc array
    {
        long * array;
        long n_comp = 0;
        int size = 0;

        array = Array_Load_From_File(argv[2], &size);

        if(array == NULL) {
            return EXIT_FAILURE; 
        }
        Array_Shellsort(&array, size, &n_comp);
        
        if(Array_Save_To_File(argv[3], array, size) == -1) 
        {
            return EXIT_FAILURE;
        }

        free(array); 
        fprintf(stdout, "%ld\n", n_comp);
    }
    else if(strcmp(argv[1], "-l") == 0) //List Shell Sorting -l bc list
    {
        Node * node;
        long n_comp = 0;

        node = List_Load_From_File(argv[2]);
        node = List_Shellsort(node, &n_comp); 
        
        if(List_Save_To_File(argv[3], node) == -1) 
        {
            return EXIT_FAILURE;
        }
        fprintf(stdout, "%ld\n", n_comp); 
        
        Node * iterator = node;
        Node * n = NULL;

        while(iterator != NULL)
        {
            n = iterator -> next;
            free(iterator);
            iterator = n;
        }
    }
    else
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
