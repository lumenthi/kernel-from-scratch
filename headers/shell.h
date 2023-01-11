#ifndef SHELL_H
#define SHELL_H

#define INPUT_LENGTH 4096

/* TODO: Multiscreen handling, put in a struct ? */
char	shell_buf[INPUT_LENGTH+1]; /* +1 for trailing '\0' */
int		shell_cursor;

/* shell.c */
void	shell_initialize(void);
void	shell_reset(void);
void	get_command(void);

#endif
