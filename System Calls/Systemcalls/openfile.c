#include <stdio.h>
#include <string.h>

int main() {
  char filename[100];
  char content[256];

  // Get filename from user
  printf("Enter filename: ");
  fgets(filename, sizeof(filename), stdin);
  filename[strcspn(filename, "\n")] = '\0'; // Remove trailing newline from filename

  // Get content from user
  printf("Enter content to write: ");
  fgets(content, sizeof(content), stdin);
  content[strcspn(content, "\n")] = '\0'; // Remove trailing newline from content

  // Open the file in write mode (create if not existing)
  FILE* fp = fopen(filename, "w");

  // Check if the file was opened successfully
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Write the content to the file
  if (fputs(content, fp) == EOF) {
    perror("Error writing to file");
    return 1;
  }

  // Close the file
  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Content written to '%s' successfully.\n", filename);
  return 0;
}

