// SSTF disk scheduling

#include <stdio.h>
#include <stdlib.h>

void SSTF(int head, int requests[], int n)
{
    int total_seek_time = 0;
    int completed[n]; // Array to track completed requests
    for (int i = 0; i < n; i++)
        completed[i] = 0; // Mark all requests as incomplete initially

    printf("\nSSTF Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);

    printf("\nRequest\tCurrent Head Position\tSeek Time\n");
    printf("-------\t----------------------\t---------\n");

    for (int i = 0; i < n; i++)
    {
        int closest = -1;
        int min_seek_time = 9999;

        // Find the closest request
        for (int j = 0; j < n; j++)
        {
            if (!completed[j])
            { // Only consider uncompleted requests
                int seek_time = abs(requests[j] - head);
                if (seek_time < min_seek_time)
                {
                    min_seek_time = seek_time;
                    closest = j;
                }
            }
        }

        // Move the head to the closest request
        int seek_time = abs(requests[closest] - head);
        total_seek_time += seek_time;

        printf("%d\t\t%d\t\t\t%d\n", requests[closest], head, seek_time);

        head = requests[closest];
        completed[closest] = 1; // Mark this request as completed
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main()
{
    int n, head;

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

    // Call the SSTF function to calculate seek time
    SSTF(head, requests, n);

    return 0;
}
