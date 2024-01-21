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
    // Converts the epoch into a readable time string
    time_t current_time = time(NULL);
    char *time_str = ctime(&current_time);
    time_str[strlen(time_str) - 1] = '\0';

    // Populate time data with time string
    data.time = time_str;

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
    // Calculate the total length of the log
    // Set a pointer to head of log list and initialize length to 0.
    log_t *current = headptr;
    size_t totalLength = 0;

    // Iterate through the entire log list.
    while (current != NULL) {
        // Calculate the length of each log entry
        size_t entryLength = snprintf(NULL, 0, "%s : %s\n", current->item.time, current->item.string);

        // Add the length of the current entry to the total length
        totalLength += entryLength;

        current = current->next;
    }

    // Allocate memory for the log string
    char *logString = (char *)malloc(totalLength + 1); // +1 for the null terminator

    if (logString == NULL) {
        // Allocation failed
        return NULL;
    }

    // Concatenate log entries into the log string
    current = headptr;
    size_t offset = 0;

    while (current != NULL) {
        // Format the current log entry and copy it to the log string
        size_t written = snprintf(logString + offset, totalLength - offset + 1, "%s : %s\n", current->item.time, current->item.string);

        // Update the offset based on the characters written
        offset += written;

        current = current->next;
    }

    return logString;
}

// Saves the logged mssages to a disk file.
int savelog(char *filename) {
    // Open a file with "write" 
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        // File could not be opened or created.
        return -1;
    }

    log_t *current = headptr;

    // Print each entry into the file.
    while (current != NULL) {
        fprintf(file, "%s : %s\n", current->item.time, current->item.string);
        current = current->next;
    }

    fclose(file);
    return 0;
}