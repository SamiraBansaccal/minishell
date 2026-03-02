# minishell (42 School)

## 📋 Description
Minishell is a simplified implementation of a shell, mimicking the behavior of Bash. This project covers process management, file descriptor redirections, and complex command-line parsing. It was developed **solo**.

## 🧠 Implementation Logic (Score: 98/100)
The architecture is built around a robust parsing engine and an execution pipeline that manages system resources and process lifecycles.

- **Parsing & Tokenization**: Implemented a recursive parser to handle complex inputs, including single/double quotes, environment variable expansion ($), and operators (pipes, redirections).
- **Execution Pipeline**: 
  - **Process Control**: Management of child processes using `fork()`, `waitpid()`, and `execve()`.
  - **I/O Redirections**: Handling of data streams through `pipe()` and `dup2()` for redirections (<, >, >>) and `here_doc`.
- **Built-ins**: Native implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signals**: Custom handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` to ensure the shell remains stable and mimics standard terminal behavior.



## 📂 Project Structure
- `src/parsing/`: Lexer, tokenizer, and command parsing logic.
- `src/execution/`: Command execution, pipeline management, and environment copying.
- `src/builtins/`: Native shell command implementations.
- `src/utils/`: Initialization, cleanup, signal handling, and error management.
- `lib/libft/`: Custom C library for utility functions.

## 🛠️ Usage & Compilation

### Compilation
The project requires the `readline` library. The Makefile is configured to link it automatically, you may need to change the path depending your os
```bash
make
```
Execution
```bash
./minishell
```
