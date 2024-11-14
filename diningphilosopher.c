#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5  // Number of philosophers

// Semaphores for each fork and a table semaphore to limit access
sem_t forks[N];
sem_t table;  // Allows only N-1 philosophers to access the table at a time

void *philosopher(void *arg) {
    int id = *((int *)arg);

    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(100000);  // Thinking

        // Wait to sit at the table
        sem_wait(&table);

        // Pick up forks in a specific order to avoid deadlock
        if (id % 2 == 0) {
            sem_wait(&forks[id]);                // Pick up left fork first
            sem_wait(&forks[(id + 1) % N]);      // Then pick up right fork
        } else {
            sem_wait(&forks[(id + 1) % N]);      // Pick up right fork first
            sem_wait(&forks[id]);                // Then pick up left fork
        }

        printf("Philosopher %d is eating.\n", id);
        usleep(100000);  // Eating

        // Put down forks in the same order
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        // Leave the table
        sem_post(&table);

        printf("Philosopher %d finished eating.\n", id);
        usleep(100000);  // Thinking again
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize each fork and the table semaphore
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&table, 0, N - 1);  // Limit access to N-1 philosophers at a time

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&table);

    return 0;
}
