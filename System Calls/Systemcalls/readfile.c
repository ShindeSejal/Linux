#include <stdio.h>

int main() {
  const char* filename = "my_file.txt";

  // Open the file in read-only mode
  FILE* fp = fopen(filename, "r");

  // Check if the file was opened successfully
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Read the contents of the file character by character
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    printf("%c", ch);
  }

  // Close the file
  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("\nFile '%s' read successfully.\n", filename);
  return 0;
}

