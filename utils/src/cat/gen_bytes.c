#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "bytes5.txt"
#define BYTE_COUNT 10000

int main(void) {
  FILE* file = fopen(FILENAME, "w");
  if (file == NULL) {
    fprintf(stderr, "gen-bytes: Error opening file\n");
    return EXIT_FAILURE;
  }
  srand((unsigned int)time(NULL));
  for (int i = 0; i < BYTE_COUNT; ++i) {
    unsigned char random_byte = (unsigned char)(rand() % 256);
    fwrite(&random_byte, sizeof(random_byte), 1, file);
  }
  fclose(file);
  printf("Successfully wrote %d random bytes to %s\n", BYTE_COUNT, FILENAME);
  return EXIT_SUCCESS;
}
