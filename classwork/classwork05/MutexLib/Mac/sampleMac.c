/**
 * Filename:   sampleMac.c
 * Purpose:    demonstrate mutex and semaphore use
 * Author:     Dr. Johnson
 * Date:       2022-02-13
 * See:        https://shivammitra.com/c/producer-consumer-problem-in-c/#
 * Description:  This program provides a possible solution for producer-consumer problem
 *    using mutex and semaphore.  It uses 5 producers and 5 consumers to demonstrate the
 *    solution. You can always play with these values.
 */
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_ITEMS 5 // Maximum items a producer can produce or a consumer can consume
#define BUFFER_SIZE 5 // Size of the buffer

int in = 0;
int out = 0;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void *producer( void *pno ) {
    int item;
    for( int i = 0; i < MAX_ITEMS; i++ ) {
        item = rand(); // Produce an random item
        sem_wait( &empty );
        pthread_mutex_lock( &mutex );
        buffer[in] = item;
        printf( "Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in );
        in = (in + 1) % BUFFER_SIZE;
        usleep( 258 );
        pthread_mutex_unlock( &mutex );
        sem_post( &full );
    }
}

void *consumer( void *cno ) {
    for( int i = 0; i < MAX_ITEMS; i++ ) {
        sem_wait( &full );
        pthread_mutex_lock( &mutex );
        int item = buffer[out];
        printf( "Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out );
        out = (out + 1) % BUFFER_SIZE;
        usleep( 369 );
        pthread_mutex_unlock( &mutex );
        sem_post( &empty );
    }
}

int main( int argc, char * argv[] ) {

    pthread_t pro[5];
    pthread_t con[5];
    pthread_mutex_init( &mutex, NULL );
    sem_init( &empty, 0, BUFFER_SIZE );
    sem_init( &full, 0, 0 );

    int a[5] = { 1, 2, 3, 4, 5 };         //Just used for numbering the producer and consumer

    for( int i = 0; i < 5; i++ ) {
        pthread_create( &pro[i], NULL, (void *)producer, (void *)&a[i] );
    }
    for( int i = 0; i < 5; i++ ) {
        pthread_create( &con[i], NULL, (void *)consumer, (void *)&a[i] );
    }

    for( int i = 0; i < 5; i++ ) {
        pthread_join( pro[i], NULL );
        usleep( 258 );
    }
    for( int i = 0; i < 5; i++ ) {
        pthread_join( con[i], NULL );
        usleep( 369 );
    }

    pthread_mutex_destroy( &mutex );
    sem_destroy( &empty );
    sem_destroy( &full );

    return 0;

}
