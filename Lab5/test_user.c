#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(void)
{
    char buf[100];
    int fd = open("/proc/mydev", O_RDWR);

    // Read and print the initial contents
    read(fd, buf, 100);
    puts(buf);

    // Get user input and write to the file
    printf("Enter a number: ");
    scanf("%s", buf);  // Assuming the user enters a string representing a number
    lseek(fd, 0, SEEK_SET);
    write(fd, buf, strlen(buf) + 1);

    // Set the file position to the beginning again
    lseek(fd, 0, SEEK_SET);

    // Read and print the updated contents
    read(fd, buf, 100);
    puts(buf);

    close(fd);

    return 0;
}
