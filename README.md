# minishell

![norminette](https://github.com/KutayKoray/kutish/actions/workflows/norminette.yml/badge.svg)

🐚 As beautiful as a shell.

## About
minishell is a core project in the 42 curriculum that challenges students to recreate a simplified version of the Unix shell. The goal is to handle user input, parse commands, manage environment variables, and execute processes with proper redirections and piping.

### 🎯 Main Objectives
- Reproduce basic shell behavior (`bash`, `sh`)
- Implement a lexer and parser for shell syntax
- Handle quotes, variable expansion (`$VAR`), and tilde expansion (`~`)
- Manage pipes (`|`), redirections (`>`, `<`, `>>`, `<<`)
- Support built-in commands (cd, echo, export, etc.)
- Manage signals (e.g., `Ctrl+C`, `Ctrl+D`)
- Ensure memory safety and leak-free execution

### 🛠️ Skills Gained
- Low-level system programming with `fork`, `execve`, `pipe`, `dup2`, `wait`
- Lexical analysis and parsing techniques
- Process and file descriptor management
- Signal handling and terminal control
- Modular, clean, and maintainable C code under strict 42 norms

minishell builds a solid foundation for understanding how shells and operating systems work at a deeper level — preparing students for more complex projects.

### References
- https://www.gnu.org/software/bash/manual/bash.html
- https://github.com/torvalds/linux (to understand how some system calls work)
- https://ftp.gnu.org/gnu/bash/ (mimic some behaviors from bash 5.1.16)

## Install & Usage (MacOS/Linux)
### Prerequisites
minishell requires the GNU Readline library for command line editing and history.
```bash
apt install libreadline-dev # for deb based distros
dnf install readline-devel # for rpm based distros
brew install readline # for macOS
```

### Installation
1. Clone the repository recursively to include the [libft](https://github.com/lareii/libft) submodule:
```bash
git clone --recursive https://github.com/KutayKoray/kutish.git
```

2. Build the project:
```bash
make
```

### Usage
Run the shell:
```bash
./minishell
```
or run with debug mode to see more verbose output:
```bash
./minishell -d
```
Ta-da! 🥳 \
You now have a working shell that can execute commands, handle pipes, and manage redirections.
