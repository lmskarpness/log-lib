# log-lib: Logging Library
Logs the current time and message data and saves it to a file. Can be used for logging of outputs for debugging, recording startup and shutdown events of a program, etc.
> Note: This software is an adaption from ideas presented by Kay A. Robbins and Steven Robbins' textbook entitled "Unix Systems Programming: Commmunications, Concurrency, and Threads".

## How to use
There is little setup involved for this software. Some use cases will look different, but below is an example to get started.
Begin by including the necessary library in your C program:
```
#include "log.h"
```

Create a new data_t object and set it's string value to the desired log message. For example:
```
char input[30];

printf("Enter a message: ");
scanf("%[^\n]s", input);

data_t input_data;
input_data.string = input;
```

In the above example, the user is prompted for input. The data received will be everything up to the new line character `\n`.
> Note: The above code snippet does not account for inputs greater than 30 characters and will abort the program if that limit is exceeded.


Finally, the message can be added to the log. Then the log can be saved to a file and the logger can be closed.
```
addmsg(input_data);
savelog("test.txt");
clearlog();
```

> [!WARNING]
> Ensure you have used 'clearlog()' to free the memory allocated to storing logged data. Otherwise, data leaks may occur.
