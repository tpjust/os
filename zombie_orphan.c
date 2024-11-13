// 1)zombie process 2)orphan processes 3)sum of even numbers

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void zombie_process()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent process started, PID: %d\n", getpid());
        printf("Child process PID: %d\n", pid);

        // Give time for child process to exit and become a zombie
        printf("\nRunning 'ps -l' to show zombie process:\n");
        fflush(stdout);
        system("ps -l | grep Z"); // Show zombie process

        // Wait a while before cleaning up the zombie
        printf("\nParent process is cleaning up the zombie process...\n");
        fflush(stdout);
        wait(NULL); // Clean up the zombie process
        printf("Zombie process cleaned up.\n");
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process started, PID: %d\n", getpid());
        printf("Child process exiting to become a zombie.\n");
        exit(0); // Child exits, becomes a zombie until parent calls wait()
    }
    else
    {
        // Fork failed
        printf("Fork failed!\n");
    }
}

void orphan_process()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent process is running, PID: %d\n", getpid());
        printf("Parent process will sleep for 1 second to allow the child to become an orphan.\n");
        sleep(1);
        printf("Parent process is exiting, child will become an orphan.\n");
        exit(0); // Parent exits, making the child an orphan
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process started, PID: %d. Parent PID: %d\n", getpid(), getppid());
        sleep(3); // Sleep to ensure it outlives the parent
        printf("Child process awoke, PID: %d. Checking new Parent PID...\n", getpid());
        printf("Child process is now an orphan and adopted by init. New Parent PID: %d\n", getppid());
    }
    else
    {
        // Fork failed
        printf("Fork failed!\n");
    }
}

void calculate_sums()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Sample array
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_sum = 0, odd_sum = 0;
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process: Calculate sum of even numbers
        wait(NULL); // Wait for child process to complete
        for (int i = 0; i < n; i++)
        {
            if (arr[i] % 2 == 0)
            {
                even_sum += arr[i];
            }
        }
        printf("Parent Process (Even Sum): %d\n", even_sum);
    }
    else if (pid == 0)
    {
        // Child process: Calculate sum of odd numbers
        for (int i = 0; i < n; i++)
        {
            if (arr[i] % 2 != 0)
            {
                odd_sum += arr[i];
            }
        }
        printf("Child Process (Odd Sum): %d\n", odd_sum);
        exit(0); // End child process
    }
    else
    {
        // Fork failed
        printf("Fork failed!\n");
    }
}

int main()
{
    printf("Running zombie process demonstration:\n");
    zombie_process();

    printf("\nRunning orphan process demonstration:\n");
    orphan_process();

    printf("\nCalculating sums in parent and child processes:\n");
    calculate_sums();

    return 0;
}