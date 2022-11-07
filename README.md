# Minishell @ 42KualaLumpur

![VN20221107_172330](https://user-images.githubusercontent.com/32697686/200279017-5fa85c4a-c526-469b-82eb-cb86e774201a.gif)

## About
Minishell is the first group project you will do as a Cadet at 42KL. It's a minimum viable version of a real shell.
The project teaches you how to tokenize and parse inputs into usable command groups to be executed.
It also gives you a good understanding of process creation and synchronisation using the C programmming language.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (v4.2.1)

### Building the program

1. Download/Clone this repo

        git clone https://github.com/jasonkwm/minishell.git
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After building the source, run `./minishell` from the project root.

#### Mandatory :
- Not interpret unclosed quotes or unspecified special characters like \ or ; `Accidentally did unclosed quotes ._.`
- Not use more than one global variable
- Show a prompt when waiting for a new command
- A working history
- Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
- Builtins:
    - cd with relative or absolute path
    - echo with -n
    - pwd
    - export
    - unset
    - env
    - exit
- Single and double quote support
- Redirections :
    - `<` should redirect input
    - `>` should redirect output
    -  `<<` read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
    - `>>` should redirect output with append mode
- Piping `|`
- Environment variables expansion
- $? should expand to the exit status of the most recently executed foreground pipeline.
- Signals :
    - ctrl-C print a new prompt on a newline
    - ctrl-D exit the shell.
    - ctrl-\ do nothing
    
### Prerequisites
Before starting on the project, it is mandatory to have a basic understanding of some concepts. You might or might not have learnt this in your past projects, but its always a good time to revisit them. These concepts include:
- Linked lists
- Signals in UNIX
- Processes , specifically working with `fork()`
- I/O (Input and output streams) for piping and redirections
- File descriptors for piping and redirections
- Basic libft stuff like Makefiles and headers etc.. youll need them.
