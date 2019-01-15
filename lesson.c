#include <stdlib.h>

// create an empty array
int *array_of_vector = NULL;
size_t array_of_vector_size = 0;

void append_vector(int value)
{
    array_of_vector_size++;
    int *resized_area = realloc(array_of_vector, sizeof(int) * array_of_vector_size);
    if (!resized_area)
    {
        // panic
        return;
    }

    array_of_vector = resized_area;
    array_of_vector[array_of_vector_size - 1] = value;
}