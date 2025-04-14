#include "exec.h"
#include <string.h>

// sets "key" with the key part of "arg"
// and null-terminates it
//
// Example:
//  - KEY=value
//  arg = ['K', 'E', 'Y', '=', 'v', 'a', 'l', 'u', 'e', '\0']
//  key = "KEY"
//
static void
get_environ_key(char *arg, char *key)
{
	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
}

// sets "value" with the value part of "arg"
// and null-terminates it
// "idx" should be the index in "arg" where "=" char
// resides
//
// Example:
//  - KEY=value
//  arg = ['K', 'E', 'Y', '=', 'v', 'a', 'l', 'u', 'e', '\0']
//  value = "value"
//
static void
get_environ_value(char *arg, char *value, int idx)
{
	ssize_t i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
}

// sets the environment variables received
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void
set_environ_vars(char **eargv, int eargc)
{
	// Your code here
}

// opens the file in which the stdin/stdout/stderr
// flow will be redirected, and returns
// the file descriptor
//
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int
open_redir_fd(char *file, int flags)
{
    int fd = open(file, flags, 0644);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }
    return fd;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
// - casting could be a good option
void
exec_cmd(struct cmd *cmd)
{
	// To be used in the different cases
	struct execcmd *e;
	struct backcmd *b;
	struct execcmd *r;
	struct pipecmd *p;

	switch (cmd->type) {

	case EXEC:
        e = (struct execcmd *)cmd;
        pid_t process = fork();
        if (process == 0) { //proceso hijo
            execvp(e->argv[0], e->argv); // Aca se podria manejar error de ejecucion
                _exit(1);
        } else if (process > 0) { //proceso padre
            wait(0);
        }
        break;

	case BACK: {
		// runs a command in background
		//
		// Your code here
		printf("Background process are not yet implemented\n");
		_exit(-1);
		break;
	}

	case REDIR: {
		// changes the input/output/stderr flow
		//
		// To check if a redirection has to be performed
		// verify if file name's length (in the execcmd struct)
		// is greater than zero
		//
		r = (struct execcmd *)cmd;

		if(strlen(r->in_file)>0) {
			int new_fd_in = open_redir_fd(r->in_file, O_RDONLY | O_CLOEXEC);
    		dup2(new_fd_in, STDIN_FILENO);
    		close(new_fd_in);
		}
		if(strlen(r->out_file)>0) {
			int new_fd_out = open_redir_fd(r->out_file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC);
    		dup2(new_fd_out, STDOUT_FILENO);
    		close(new_fd_out);
		}
		if(strlen(r->err_file)>0) {
			if (r->err_file[0] == '&') {
				dup2(STDOUT_FILENO, STDERR_FILENO);
			} else {
				int new_fd_err = open_redir_fd(r->err_file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC);
    			dup2(new_fd_err, STDERR_FILENO);
    			close(new_fd_err);
			}
		}
        pid_t process = fork();
        if (process == 0) {
            execvp(r->argv[0], r->argv);
                _exit(1);
        } else if (process > 0) {
            wait(0);
        }
        break;
	}

	case PIPE: {
		// pipes two commands
		//
		// Your code here
		printf("Pipes are not yet implemented\n");

		// free the memory allocated
		// for the pipe tree structure
		free_command(parsed_pipe);

		break;
	}
	}
}
