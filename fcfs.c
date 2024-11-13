// FCFS disk scheduling

#include <stdio.h>
#include <stdlib.h>

void FCFS(int head, int requests[], int n)
{
    int total_seek_time = 0;
    int current_position = head;

    printf("\nFCFS Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);

    printf("\nRequest\tCurrent Head Position\tSeek Time\n");
    printf("-------\t----------------------\t---------\n");

    for (int i = 0; i < n; i++)
    {
        int seek_time = abs(requests[i] - current_position);
        total_seek_time += seek_time;

        printf("%d\t\t%d\t\t\t%d\n", requests[i], current_position, seek_time);

        current_position = requests[i];
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

    // Call the FCFS function to calculate seek time
    FCFS(head, requests, n);

    return 0;
}

/*5
98
183
37
122
14
50*/
