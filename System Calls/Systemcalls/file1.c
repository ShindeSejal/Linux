#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> 
int main() {
  const char* filename = "my_file.txt";

  // Open the file in read/write mode with create and exclusive flags
  int fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);

  // Check if the file was opened successfully
  if (fd == -1) {
    if (errno == EEXIST) {
      // File already exists, open in read-only mode
      fd = open(filename, O_RDONLY);
      if (fd == -1) {
        perror("Error opening existing file");
        return 1;
      }
      printf("File '%s' already exists, opened for reading.\n", filename);
    } else {
      perror("Error opening file");
      return 1;
    }
  } else {
    // File was created successfully
    printf("File '%s' created successfully.\n", filename);
  }

   // Close the file using close
  if (close(fd) == -1) {
    perror("Error closing file");
    return 1;
  }

  return 0;
}

