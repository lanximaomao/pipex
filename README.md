# Pipex - 42 School Project

## Description

Pipex mimics the behavior of the pipe (|) in Bash, allowing the output of one command to be used as input for the next command. Detailed project requirements can be found [here](Pipex.pdf).

## Language Used

[![Language Used](https://skills.thijs.gg/icons?i=c)](https://skills.thijs.gg)

## Install and Run

**1. Compilation:**

To compile the program, run the following command:

**2. Running the Program:**

	make

The program takes four arguments:
- `file1`: Input file for `cmd1`.
- `file2`: Output file for `cmd2`.
- `cmd1`: Relative or absolute path of the first command.
- `cmd2`: Relative or absolute path of the second command.

Use the following command format to run the program:

	./pipex file1 cmd1 cmd2 file2

**3. Comparison with Bash:**

To compare the result with the equivalent Bash command, use the following format:

	$> < file1 cmd1 | cmd2 > file2

## Testing

*External Testers:*
- [pipex_tester by vfurmane](https://github.com/vfurmane/pipex-tester)
