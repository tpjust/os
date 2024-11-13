// C-SCAN disk scheduling

#include <stdio.h>
#include <stdlib.h>

void CSCAN(int head, int requests[], int n, int disk_size)
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

    printf("\nC-SCAN Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);

    printf("\nRequest\tCurrent Head Position\tSeek Time\n");
    printf("-------\t----------------------\t---------\n");

    // Move towards the end of the disk serving requests on the right
    for (i = pos; i < n; i++)
    {
        int seek_time = abs(requests[i] - head);
        total_seek_time += seek_time;
        printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
        head = requests[i];
    }

    // Jump to the beginning of the disk
    if (head != disk_size - 1)
    {
        int seek_time = abs((disk_size - 1) - head);
        total_seek_time += seek_time;
        printf("%d\t\t%d\t\t\t%d\n", disk_size - 1, head, seek_time);
        head = 0; // Jump to 0 (beginning of the disk)
        printf("%d\t\t%d\t\t\t%d\n", 0, disk_size - 1, head);
    }

    // Continue serving requests from the start to the head position
    for (i = 0; i < pos; i++)
    {
        int seek_time = abs(requests[i] - head);
        total_seek_time += seek_time;
        printf("%d\t\t%d\t\t\t%d\n", requests[i], head, seek_time);
        head = requests[i];
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main()
{
    int n, head, disk_size;

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

    // Call the CSCAN function to calculate seek time
    CSCAN(head, requests, n, disk_size);

    return 0;
}

/*6
98
183
37
122
14
124
50
200*/
