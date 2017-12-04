# KoopaShell

## Features

- More or less a working version of the bash shell, including functional exit and cd commands.
- Correctly prints error messages typical of bash shell.
- Accepts commands seperated by semicolons.
- Includes functionality to pipe or redirect commands at least once.
- Works regardless of the number of spaces before, after, or in between arguments.

## Unfinished Features

- I wanted to implement >> and <<, but I just didn't have enough time.

## Known Bugs/Issues

- Shell only accepts input of 256 bytes (or fewer) at a time. 
- When piping, the commands pipe correctly but the output of the first command is also written to STDOUT. Unclear why this happens.
- Piping will write a maximum of 512 bytes to a file. Anything more will be truncated. 
- I'm not sure to what extent chained piping and redirection works, so just assumed it doesn't.
  - But you can redirect and then pipe (or vice versa) at least once.
- If there are extra spaces within the given command, too much memory is allocated for an array of its arguments. However, this memory is later freed.

### Function Headers

#### command.h

/* ==== runCommand =========
   Arguments: accepts an array char pointers (strings)

   Returns: an int indicating exit status

   Accepts an array of command line arguments, which it will fork and execute as necessary.

   ========================*/

   /* ==== runSequence =========
   Arguments: accepts a char pointer (string) 

   Returns: an int indicating exit status

   Accepts command line input in the form of a string. It will split on the first semicolon (if any), parse and run the preceding command, and continue recursively in this manner until all commands have been executed.

   ========================*/

   /* ==== runRedir ===========
   Arguments: accepts an array of char pointers (strings), one of which is either "<" or ">". 

   Returns: an int indicating exit status

   Handles command execution in the event redirection is required. It will redirect either STDIN or STDOUT to the desired file as necessary, then fork and execute the given command. 

   ========================*/

   /* ==== runPipe ===========
   Arguments: accepts a char pointer (string) containing at least one pipe.

   Returns: an int indicating exit status

   Accepts command line input in the form of a stirng, and handles execution in the event piping is required. It splits on the pipe, then use popen to read the output of the first command and write the resulting buffer to the second.
 
   ========================*/

   /* ==== hasRedir ===========
   Arguments: accepts an array of char pointers (strings)

   Returns: the array index at which the first instance of ">" or "<" was found. If none exists, returns 0.

   Checks whether the given array of command line arguments contains at least one redirection, and returns the index of the first instance. Returns 0 if none is found.
 
   ========================*/

   /* ==== forkRun ===========
   Arguments: accepts an array of char pointers (strings)

   Returns: an int indicating exit status

   Will fork, and then execute the given array of commands using execvp within the child process.
 
   ========================*/

#### parse.h

   /* ==== parseCommand ========
   Arguments: accepts a char pointer (string) 

   Returns: an array of char pointers which can be passed as command line arguments

   Counts the number of tokens within the string, then allocates the correct amount of memory. It then splits on the spaces between tokens, stripping execess spaces from the front and back of each token as it goes.
 
   ========================*/

   /* ==== countArgs ========
   Arguments: accepts a char pointer (string) 

   Returns: the number of tokens seperated by spaces within the given string

   Returns the mimimum (oops!) number of tokens within the string.

   ========================*/

   /* ====== stripSpaces =======
   Arguments: accepts a char pointer (string) 

   Returns: a pointer to the same string, with all preceding or terminating whitespace having been stripped. It also removes the final newline appended by fgets(), if present.

   Increments the char pointer to the first instance of a char != ' ', effectively removing the preceding spaces. It then iterates from the back of the string, setting the last instance of ' ' to null, effectively truncating the string.

   ========================*/