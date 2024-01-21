#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

// Adds a log message to the list of logs
int addmsg(data_t data) {
    // Create new list struct from data.
    log_t *new_msg = (log_t *)malloc(sizeof(log_t));
    
    if (new_msg == NULL) {
        // Allocation failed
        return -1;
    }

    // Gets the time since Jan 1, 1970 -- the Epoch -- in seconds.
    // Conversion to exact readable time is tasked in the savelog function.
    time_t current_time = time(NULL);
    data.time = current_time;

    // Filling new_msg with it's data
    new_msg->item = data;
    new_msg->next = NULL;

    // If first message received, assign head tail to new list struct.
    if (headptr == NULL) {
        headptr = new_msg;
        tailptr = new_msg;
        return 0;
    }

    // If not the first message, add message to list and move tail.
    tailptr->next = new_msg;
    tailptr = new_msg;

    return 0;
}

// Releases all the storage that has been allocated for the logged messages
// and empties the list of logged messages.
void clearlog(void) {
    log_t *current = headptr;
    log_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    headptr = NULL;
    tailptr = NULL;
}

// Allocates enough space for a string containing the entire log, copies
// the log into this string, and returns a pointer to the string.
char *getlog(void) {
    return NULL;
}

// Saves the logged mssages to a disk file.
int savelog(char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return -1;
    }

    log_t *current = headptr;

    while (current != NULL) {
        char *time_str = ctime(&current->item.time);
        time_str[strlen(time_str) - 1] = '\0';
        fprintf(file, "%s : %s\n", time_str, current->item.string);
        
        current = current->next;
    }

    fclose(file);

    return 0;
}