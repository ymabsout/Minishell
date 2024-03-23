## Welcome to Minishell! 🚀

🚀 42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

## Final Grade: 🎓 125/125

🔴 Mandatory Part: 💯/💯

🟢 Bonus: 25/25

### How to Use It

🔨 Using `make` will create the `minishell` executable.

Simply run it with:

### Command Usage

To run Minishell, simply execute:

./minishell


### Features Overview 🌟

- **Execution**: Minishell executes programs from absolute, relative, or environment PATH (`/bin/ls` or `ls`), supporting arguments and options.
- **Quotation Marks**: Use `'` and `"` similar to Bash, except for multiline commands.
- **Command Chaining**: Separate commands with `&&` or `||`.
- **Redirections**: Utilize `>`, `>>`, `<` for input/output redirection, and `|` for pipes.
- **Environment Variables**: Handles variables like `$HOME` and returns code `$?`.
- **Keyboard Shortcuts**: Use `Ctrl-C` to interrupt, `Ctrl-\` to quit, and `Ctrl-D` to throw an EOF, similar to Bash.
- **Built-in Functions**: Includes `echo`, `pwd`, `cd`, `env`, `export`, `unset`, and `exit`, which are directly implemented within Minishell.
