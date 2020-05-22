#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
 
#define PHT_SIZE 5

typedef struct example_tag
{
    const char *name;
    unsigned left_fork;
    unsigned right_fork;
} example_t;


typedef struct table_tag
{
    pthread_mutex_t forks[PHT_SIZE];
} table_t;

typedef struct example_args_tag
{
    const example_t *example;
    const table_t *table;
} example_args_t;


pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;


void init_example(example_t *example, const char *name,
unsigned left_fork, unsigned right_fork)
{
    example->name = name;
    example->left_fork = left_fork;
    example->right_fork = right_fork;
}


void init_table(table_t *table)
{
    size_t i;
    for (i = 0; i < PHT_SIZE; i++)
    {
        pthread_mutex_init(&table->forks[i], NULL);
    }
}


void* eat(void *args)
{
    example_args_t *arg = (example_args_t*) args;
    const example_t *example = arg->example;
    const table_t *table = arg->table;
    unsigned rand_time;  
    srand(NULL);
    do {
        printf("%s started dinner\n", example->name);
 
        pthread_mutex_lock(&entry_point); 
        pthread_mutex_lock(&table->forks[example->left_fork]);
        pthread_mutex_unlock(&entry_point); 
        rand_time =rand()%10;
        sleep(rand_time);
        pthread_mutex_lock(&entry_point);
        pthread_mutex_lock(&table->forks[example->right_fork]);
        pthread_mutex_unlock(&entry_point);
        printf("%s is eating after %d s sleep\n", example->name, rand_time);
        pthread_mutex_unlock(&table->forks[example->right_fork]);
        pthread_mutex_unlock(&table->forks[example->left_fork]);
        printf("%s finished dinner\n", example->name);
    } while (1);
}
 
void main()
{
    pthread_t threads[PHT_SIZE];
    example_t examples[PHT_SIZE];
    example_args_t arguments[PHT_SIZE];
    table_t table;
    size_t i;
 
    init_table(&table);
 
    init_example(&examples[0], "Apollonius", 0, 1);
    init_example(&examples[1], "Socrates",   1, 2);
    init_example(&examples[2], "Parmenides", 2, 3);
    init_example(&examples[3], "Heraclitus", 3, 4);
    init_example(&examples[4], "Aristotle", 4, 0);
 
    for (i = 0; i < PHT_SIZE; i++)
    {
        arguments[i].example = &examples[i];
        arguments[i].table = &table;
    }
 
    for (i = 0; i < PHT_SIZE; i++)
    {
        pthread_create(&threads[i], NULL, eat, &arguments[i]);
    }
 
    for (i = 0; i < PHT_SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
