//deadlock detection system

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int processes, resources;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

bool finish[MAX_PROCESSES];
int work[MAX_RESOURCES];

void deadlockDetection() {
    bool deadlock = false;
    int deadlockedProcesses[MAX_PROCESSES];
    int deadlockedCount = 0;

    // Initialize work as a copy of available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Initialize finish array
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    // Try to find processes that can finish
    for (int count = 0; count < processes; count++) {
        bool progress = false;

        // Check for processes that can finish
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                // Check if the process can get all resources it needs
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                // If it can proceed, allocate resources temporarily
                if (canProceed) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;  // Mark the process as finished
                    progress = true;   // We made progress in this round
                }
            }
        }

        // If no process could finish in this round, break out
        if (!progress) {
            break;
        }
    }

    // Check for processes that are not finished
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            deadlockedProcesses[deadlockedCount++] = i;
            deadlock = true;
        }
    }

    // Output the result
    if (deadlock) {
        printf("System is in a deadlock state.\n");
        printf("Deadlocked processes: ");
        for (int i = 0; i < deadlockedCount; i++) {
            printf("P%d ", deadlockedProcesses[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a deadlock state.\n");
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    deadlockDetection();

    return 0;
}

Enter the number of processes: 3
Enter the number of resources: 3
Enter the available resources:
3 3 2
Enter the allocation matrix:
0 1 0
2 0 1
3 1 1
Enter the request matrix:
7 3 2
3 2 2
9 0 2
