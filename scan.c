// SCAN disk scheduling

#include <stdio.h>
#include <stdlib.h>

void SCAN(int head, int requests[], int n, int disk_size, int direction)
{
    int total_seek_time = 0;
    int temp, i, j;

    // Sort the request array
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the position of the head in the sorted request array
    int pos = 0;
    for (i = 0; i < n; i++)
    {
        if (head < requests[i])
        {
            pos = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "Right" : "Left");

    printf("\nRequest\tCurrent Head Position\tSeek Time\n");
    printf("-------\t----------------------\t---------\n");

    // Serve requests based on the direction
    if (direction == 1)
    { // Moving towards the right
        for (i = pos; i < n; i++)
        {
            int seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
            head = requests[i];
        }
        // Go to the end of the disk if necessary
        if (head != disk_size - 1)
        {
            int seek_time = abs((disk_size - 1) - head);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", disk_size - 1, head, seek_time);
            head = disk_size - 1;
        }
        // Reverse direction and continue serving requests to the left
        for (i = pos - 1; i >= 0; i--)
        {
            int seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
            head = requests[i];
        }
    }
    else
    { // Moving towards the left
        for (i = pos - 1; i >= 0; i--)
        {
            int seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
            head = requests[i];
        }
        // Go to the start of the disk if necessary
        if (head != 0)
        {
            int seek_time = abs(head - 0);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", 0, head, seek_time);
            head = 0;
        }
        // Reverse direction and continue serving requests to the right
        for (i = pos; i < n; i++)
        {
            int seek_time = abs(requests[i] - head);
            total_seek_time += seek_time;
            printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
            head = requests[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main()
{
    int n, head, disk_size, direction;

    // Input number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    // Input the disk requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Input initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Input the size of the disk
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    // Input direction (1 for right, 0 for left)
    printf("Enter the initial direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    // Call the SCAN function to calculate seek time
    SCAN(head, requests, n, disk_size, direction);

    return 0;
}
