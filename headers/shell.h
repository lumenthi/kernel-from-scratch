#ifndef SHELL_H
#define SHELL_H

#define INPUT_LENGTH 4096

extern char	shell_buf[INPUT_LENGTH+1]; /* +1 for trailing '\0' */

/* Shell commands structure */
struct shell_command {
	char *name;
	void (*routine)(void);
};

/* All commands available declared in shell.c */
extern struct shell_command	*cmd_list;

/* shell.c */
void	help(void);
void	shell_initialize(void);
void	shell_reset(void);
void	get_command(void);
int		handle_command(char *str);
#endif
