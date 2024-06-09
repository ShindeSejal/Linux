#include <stdio.h>

int main() {
  const char* filename = "my_file.txt";
  const char* content = "All the while I’ve been waiting ,For you to take my heart with you it’s sinking.\n";
  int num_writes = 3; // Number of times to write the content

  // Open the file in append mode
  FILE* fp = fopen(filename, "a");

  // Check if the file was opened successfully
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Write the content to the file multiple times
  for (int i = 0; i < num_writes; i++) {
    if (fputs(content, fp) == EOF) {
      perror("Error writing to file");
      return 1;
    }
  }

  // Close the file
  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Content written to '%s' %d times.\n", filename, num_writes);
  return 0;
}

