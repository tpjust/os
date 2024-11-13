//reader writer mutex

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


// Shared data and synchronization variables
int shared_data = 0;
int reader_count = 0;
pthread_mutex_t resource_mutex;      // Mutex for exclusive access to shared data
pthread_mutex_t reader_count_mutex;   // Mutex for protecting reader count
int max_operations = 5; // Number of iterations for readers and writers


// Reader function
void* reader(void* arg) {
    int reader_id = *((int*)arg);
    free(arg);
    int read_count = 0;


    while (read_count < max_operations) { 
        // Entry section for reader
        pthread_mutex_lock(&reader_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            pthread_mutex_lock(&resource_mutex); // First reader locks the resource
        }
        pthread_mutex_unlock(&reader_count_mutex);


        // Reading section
        printf("Reader %d is reading the shared data: %d\n", reader_id, shared_data);


        // Exit section for reader
        pthread_mutex_lock(&reader_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            pthread_mutex_unlock(&resource_mutex); // Last reader unlocks the resource
        }
        pthread_mutex_unlock(&reader_count_mutex);


        read_count++; // Increment read count
    }


    return NULL;
}


// Writer function
void* writer(void* arg) {
    int writer_id = *((int*)arg);
    free(arg);
    int write_count = 0;


    while (write_count < max_operations) { 
        pthread_mutex_lock(&resource_mutex);  // Writer locks the resource
        shared_data++;
        printf("Writer %d updated shared data to: %d\n", writer_id, shared_data);
        pthread_mutex_unlock(&resource_mutex);  // Writer releases the resource
        
        write_count++; // Increment write count
    }


    return NULL;
}


int main() {
    pthread_t readers[5], writers[2];
    pthread_mutex_init(&resource_mutex, NULL);
    pthread_mutex_init(&reader_count_mutex, NULL);


    // Create reader threads
    for (int i = 0; i < 5; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }


    // Create writer threads
    for (int i = 0; i < 2; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }


    // Wait for threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }


    // Destroy mutexes
    pthread_mutex_destroy(&resource_mutex);
    pthread_mutex_destroy(&reader_count_mutex);


    return 0;
}
