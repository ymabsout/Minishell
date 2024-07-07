# 🚀 Minishell: As Beautiful as a Shell 🚀

Welcome to Minishell, a project that will take you back in time to the early days of computing. This project involves creating a simple, interactive shell similar to bash. By building Minishell, you'll gain a deep understanding of processes, file descriptors, and the intricacies of shell functionalities. Let's dive into the details! 🌟

## 📚 Table of Contents
- [Introduction](#introduction)
- [Common Instructions](#common-instructions)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)
- [Submission and Peer-evaluation](#submission-and-peer-evaluation)
- [Allowed Functions](#allowed-functions)

## Introduction

The existence of shells is intertwined with the history of IT. Initially, developers communicated with computers using 1/0 switches, which was highly inefficient. The invention of shells allowed for interaction using command lines in human-readable language, revolutionizing computer communication. Minishell will help you understand and recreate the challenges faced during those early days.

## Common Instructions

| Instruction                                                                                                     | Description                                                                                                                                 |
|-----------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| Project Language                                                                                                | C                                                                                                                                           |
| Norm Compliance                                                                                                 | All code must adhere to the Norm standards. Any deviation, including bonus files, will result in a score of 0.                              |
| Stability                                                                                                       | Functions must not cause unexpected crashes (segmentation faults, bus errors, double free, etc.) except for undefined behaviors.            |
| Memory Management                                                                                               | All heap-allocated memory must be properly freed. No memory leaks will be tolerated.                                                        |
| Makefile Requirements                                                                                           | Must compile source files with `-Wall -Wextra -Werror` flags using `cc`. Rules must include `$(NAME)`, `all`, `clean`, `fclean`, and `re`.   |
| Bonus Submission                                                                                                | Must include a `bonus` rule in the Makefile and keep bonus code in separate files `_bonus.{c/h}`.                                           |
| Libft                                                                                                           | If allowed, must copy sources and associated Makefile into a `libft` folder and compile using its Makefile.                                 |
| Testing                                                                                                         | Strongly encouraged to create test programs for self and peer testing, although not submitted or graded.                                    |
| Submission                                                                                                      | Submit work to the assigned git repository. Only work in the repository will be graded.                                                     |

## Mandatory Part

### Program Details

| Item                       | Description                                                                                                                                                                                                                                                                                                  |
|----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Program Name               | `minishell`                                                                                                                                                                                                                                                                                                  |
| Turn-in Files              | `Makefile`, `*.h`, `*.c`                                                                                                                                                                                                                                                                                     |
| Makefile Rules             | `NAME`, `all`, `clean`, `fclean`, `re`                                                                                                                                                                                                                                                                       |
| External Functions Allowed | `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs` |
| Libft Authorized           | Yes                                                                                                                                                                                                                                                                                                          |
| Description                | Write a shell                                                                                                                                                                                                                                                                                                |

### Shell Requirements

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Avoid using more than one global variable to indicate a received signal.
- Handle single (`'`) and double (`"`) quotes.
- Implement redirections:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` for heredoc (input until a delimiter is seen).
  - `>>` for output in append mode.
- Implement pipes (`|`).
- Handle environment variables (`$VAR`).
- Handle `$?` to get the exit status of the most recent foreground pipeline.
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` like in bash:
  - `ctrl-C` displays a new prompt on a new line.
  - `ctrl-D` exits the shell.
  - `ctrl-\` does nothing.
- Implement the following builtins:
  - `echo` with `-n` option
  - `cd` with relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options

## Bonus Part

Your program must also implement:

- `&&` and `||` with parenthesis for priorities.
- Wildcards `*` should work for the current working directory.

**Note:** The bonus part will only be evaluated if the mandatory part is perfect. This means the mandatory part must be completely functional and meet all requirements.

## Submission and Peer-evaluation

Submit your assignment to your Git repository. Only the work inside your repository will be evaluated during the defense. Double-check the names of your files to ensure correctness. Happy coding! 😃

---

## Allowed Functions

| Function           | Description                                                                                      |
|--------------------|--------------------------------------------------------------------------------------------------|
| `readline`         | Reads a line from the terminal.                                                                  |
| `rl_clear_history` | Clears the history of commands entered.                                                          |
| `rl_on_new_line`   | Prepares for a new line of input.                                                                |
| `rl_replace_line`  | Replaces the current line with a new line.                                                       |
| `rl_redisplay`     | Redisplays the current line.                                                                     |
| `add_history`      | Adds the current line to the history.                                                            |
| `printf`           | Prints formatted output to the standard output.                                                  |
| `malloc`           | Allocates memory dynamically.                                                                    |
| `free`             | Frees dynamically allocated memory.                                                              |
| `write`            | Writes data to a file descriptor.                                                                |
| `access`           | Checks the user's permissions for a file.                                                        |
| `open`             | Opens a file.                                                                                    |
| `read`             | Reads data from a file descriptor.                                                               |
| `close`            | Closes a file descriptor.                                                                        |
| `fork`             | Creates a new process by duplicating the calling process.                                        |
| `wait`             | Waits for a child process to change state.                                                       |
| `waitpid`          | Waits for a specific child process to change state.                                              |
| `wait3`            | Waits for a child process to change state, providing resource usage information.                 |
| `wait4`            | Waits for a specific child process to change state, providing resource usage information.        |
| `signal`           | Sets a function to handle a signal.                                                              |
| `sigaction`        | Examines and changes a signal action.                                                            |
| `sigemptyset`      | Initializes a signal set to exclude all signals.                                                 |
| `sigaddset`        | Adds a signal to a signal set.                                                                   |
| `kill`             | Sends a signal to a process or a group of processes.                                             |
| `exit`             | Terminates the calling process.                                                                  |
| `getcwd`           | Gets the current working directory.                                                              |
| `chdir`            | Changes the current working directory.                                                           |
| `stat`             | Retrieves information about a file.                                                              |
| `lstat`            | Retrieves information about a file, not following symbolic links.                                |
| `fstat`            | Retrieves information about a file based on its file descriptor.                                 |
| `unlink`           | Deletes a name from the filesystem.                                                              |
| `execve`           | Executes a program.                                                                              |
| `dup`              | Duplicates a file descriptor.                                                                    |
| `dup2`             | Duplicates a file descriptor to a specific file descriptor number.                               |
| `pipe`             | Creates a pair of file descriptors for interprocess communication.                               |
| `opendir`          | Opens a directory stream.                                                                        |
| `readdir`          | Reads a directory entry from a directory stream.                                                 |
| `closedir`         | Closes a directory stream.                                                                       |
| `strerror`         | Returns a string describing the error code.                                                      |
| `perror`           | Prints a description for the last error that occurred.                                           |
| `isatty`           | Tests if a file descriptor refers to a terminal.                                                 |
| `ttyname`          | Returns the name of the terminal associated with a file descriptor.                              |
| `ttyslot`          | Returns the index of the current terminal in the terminal array.                                 |
| `ioctl`            | Manipulates the underlying device parameters of special files.                                   |
| `getenv`           | Retrieves the value of an environment variable.                                                  |
| `tcsetattr`        | Sets the parameters associated with the terminal.                                                |
| `tcgetattr`        | Gets the parameters associated with the terminal.                                                |
| `tgetent`          | Loads the entry for a terminal type.                                                             |
| `tgetflag`         | Gets the boolean value of a terminal capability.                                                 |
| `tgetnum`          | Gets the numeric value of a terminal capability.                                                 |
| `tgetstr`          | Gets the string value of a terminal capability.                                                  |
| `tgoto`            | Returns a cursor movement string for the terminal.                                               |
| `tputs`            | Outputs a string to the terminal with padding.                                                   |
| `tgoto`            | Returns a cursor movement string for the terminal.                                               |
| `tputs`            | Outputs a string to the terminal with padding.                                                   |
