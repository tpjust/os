//system calls

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
 
void process_related() {
    int choice;
    pid_t pid;
   
    printf("\nProcess Related System Calls:\n");
    printf("1. fork()\n");
    printf("2. exit()\n");
    printf("3. wait()\n");
    printf("4. exec()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            pid = fork();
            if (pid == 0) {
                printf("This is the child process. PID = %d\n", getpid());
                exit(0);
            } else {
                printf("This is the parent process. PID = %d\n", getpid());
            }
            break;
 
        case 2:
            printf("Exiting with status 0...\n");
            exit(0);
            break;
 
        case 3:
            pid = fork();
            if (pid == 0) {
                printf("Child process. PID = %d\n", getpid());
                exit(0);
            } else {
                wait(NULL);
                printf("Child process finished. Parent PID = %d\n", getpid());
            }
            break;
 
        case 4:
            pid = fork();
            if (pid == 0) {
                printf("Child process executing ls command:\n");
                execl("/bin/ls", "ls", NULL);
                exit(0);
            } else {
                wait(NULL);
                printf("ls command executed by child process.\n");
            }
            break;
 
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void communication_related() {
    int choice;
    int fd[2];
    char write_msg[20] = "Hello, World!";
    char read_msg[20];
    pid_t pid;
 
    printf("\nCommunication Related System Calls:\n");
    printf("1. pipe()\n");
    printf("2. FIFO (named pipe)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            if (pipe(fd) == -1) {
                perror("Pipe failed");
                exit(1);
            }
 
            pid = fork();
            if (pid == 0) {
                close(fd[0]); // Close unused read end
                write(fd[1], write_msg, strlen(write_msg)+1);
                close(fd[1]);
            } else {
                close(fd[1]); // Close unused write end
                read(fd[0], read_msg, sizeof(read_msg));
                printf("Received message: %s\n", read_msg);
                close(fd[0]);
            }
            break;
 
        case 2:
            mkfifo("/tmp/myfifo", 0666);
            pid = fork();
 
            if (pid == 0) {
                int fd = open("/tmp/myfifo", O_WRONLY);
                write(fd, write_msg, strlen(write_msg)+1);
                close(fd);
                exit(0);
            } else {
                int fd = open("/tmp/myfifo", O_RDONLY);
                read(fd, read_msg, sizeof(read_msg));
                printf("Received message: %s\n", read_msg);
                close(fd);
            }
            unlink("/tmp/myfifo");
            break;
 
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void file_related() {
    int choice;
    int fd;
    char buffer[100];
 
    printf("\nFile Related System Calls:\n");
    printf("1. open(), write(), close()\n");
    printf("2. link(), stat(), unlink()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
            if (fd == -1) {
                perror("Error opening file");
                exit(1);
            }
 
            write(fd, "Hello, World!\n", 14);
            close(fd);
            printf("File written and closed successfully.\n");
 
            fd = open("example.txt", O_RDONLY);
            read(fd, buffer, 100);
            printf("File content: %s", buffer);
            close(fd);
            break;
 
        case 2:
            link("example.txt", "example_link.txt");
            struct stat file_stat;
            stat("example_link.txt", &file_stat);
            printf("File size: %ld bytes\n", file_stat.st_size);
            unlink("example_link.txt");
            printf("Link removed.\n");
            break;
 
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
void info_related() {
    int choice;
 
    printf("\nInformation Related System Calls:\n");
    printf("1. alarm()\n");
    printf("2. sleep()\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch(choice) {
        case 1:
            printf("Setting an alarm for 5 seconds...\n");
            alarm(5);
            sleep(6); // To show the alarm trigger
            break;
 
        case 2:
            printf("Sleeping for 3 seconds...\n");
            sleep(3);
            printf("Woke up after 3 seconds.\n");
            break;
 
        default:
            printf("Invalid choice.\n");
            break;
    }
}
 
int main() {
    int choice;
 
    while(1) {
        printf("\nMenu:\n");
        printf("1. Process Related\n");
        printf("2. Communication Related\n");
        printf("3. File Related\n");
        printf("4. Information Related\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch(choice) {
            case 1:
                process_related();
                break;
 
            case 2:
                communication_related();
                break;
 
            case 3:
                file_related();
                break;
 
            case 4:
                info_related();
                break;
 
            case 5:
                printf("Exiting...\n");
                exit(0);
 
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
 
    return 0;
}
