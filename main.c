#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void output_array(Array *a)
{
  for (int i = 0; i < a->size; i++)
  {
    printf("%.2f ", a->data[i]);
  }
  printf("\n");
}

void shift_array(Array *a)
{
  if (a->size < 2)
  {
    return; // nothing to shift
  }

  double first = a->data[0];

  for (int i = 0; i < a->size - 1; i++)
  {
    a->data[i] = a->data[i + 1];
  }

  a->data[a->size - 1] = first;
}

Array *average_adjacent(Array *a)
{
  Array *result = (Array *)malloc(sizeof(Array));
  if (result == NULL)
  {
    return NULL;
  }

  result->size = a->size / 2;
  result->data = (double *)malloc(result->size * sizeof(double));
  if (result->data == NULL)
  {
    free(result);
    return NULL;
  }

  for (int i = 0; i < result->size; i++)
  {
    result->data[i] = (a->data[2 * i] + a->data[2 * i + 1]) / 2.0;
  }

  return result;
}


int main(int argc, char *argv[])
{
  // Check that the argument exists
  if (argc != 2)
  {
    printf("Usage: %s <array_size>\n", argv[0]);
    return 1;
  }

  // Convert and validate
  int size = atoi(argv[1]);
  if (size <= 0)
  {
    printf("Error: array size must be a positive integer.\n");
    return 1;
  }

  // Allocate the struct itself
  Array *original = (Array *)malloc(sizeof(Array));
  if (original == NULL)
  {
    printf("Error: memory allocation failed.\n");
    return 1;
  }

  // Allocate the data array inside the struct
  original->size = size;
  original->data = (double *)malloc(size * sizeof(double));
  if (original->data == NULL)
  {
    printf("Error: memory allocation failed.\n");
    free(original);
    return 1;
  }

  // Fill the array with values
  for (int i = 0; i < original->size; i++)
  {
    original->data[i] = i * 1.5;
  }

  // call the functions
  printf("Original array:\n");
  output_array(original);

  shift_array(original);

  printf("After shifting:\n");
  output_array(original);

  Array *avg = average_adjacent(original);
  if (avg == NULL)
  {
    printf("Error: memory allocation failed.\n");
    free(original->data);
    free(original);
    return 1;
  }

  printf("Averaged array:\n");
  output_array(avg);

  // Free everything (data first, then the struct)
  free(avg->data);
  free(avg);
  free(original->data);
  free(original);

  return 0;
}
