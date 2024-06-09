#include <stdio.h>
#include <fcntl.h>

/*int main() {
    int fd = open("myfile.txt", O_RDONLY | O_WRONLY);
    if (fd == -1) {
        printf("Error: Invalid flag combination (O_RDONLY | O_WRONLY)\n");
    }
    // ... (rest of your program)
    return 0;
}*/

/*int main() {
    int fd = open("existing_file.txt", O_CREAT | O_TRUNC | O_EXCL);
    if (fd == -1) {
        perror("Error opening file");
    }
    // ... (rest of your program)
    return 0;
}*/

/*int main() {
    int fd = open("myfile.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
    }
    // ... (read from or write to the file using fd)
    return 0;
}*/

int main() {
    int fd = open("new_file.txt", O_CREAT);
    if (fd == -1) {
        perror("Error opening file");
    }
    // ... (write to the new file using fd)
    return 0;
}


