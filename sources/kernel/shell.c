#include "kernlib.h"
#include "printk.h"
#include "shell.h"
#include "vga.h"

struct shell_command *cmd_list;
char shell_buf[INPUT_LENGTH+1]; /* +1 for trailing '\0' */

static struct shell_command commands[] = {
	{"shutdown", poweroff},
	{"help", help},
	{NULL, NULL}
};

void help(void)
{
	int i = 0;

	printk("List of available commands:\n");
	while (cmd_list[i].name) {
		printk("%s\n", cmd_list[i].name);
		i++;
	}
}


int handle_command(char *str)
{
	int i = 0;

	while (cmd_list[i].name) {
		if (!strcmp(cmd_list[i].name, str)) {
			cmd_list[i].routine();
			return 0;
		}
		i++;
	}

	printk("typos: %s command not found\n", str);
	return 1;
}

void get_command(void)
{
	int x = KPROMPT_SIZE;
	int y = VGA_HEIGHT - line_count - 1;
	int offset = (x + y * VGA_WIDTH);
	int i = offset;
	char c;

	while ((c = get_char_at_index(i)) && i-offset < INPUT_LENGTH) {
		shell_buf[i-offset] = c;
		i++;
	}
}

int str_empty(char *str)
{
	int i = 0;

	if (!str)
		return 1;

	while(str[i]) {
		if (str[i] > 33 && str[i] < 127)
			return 0;
		i++;
	}
	return 1;
}

void shell_reset(void)
{
	bzero(shell_buf, INPUT_LENGTH+1); /* +1 for trailing '\0' */
}

void shell_initialize(void)
{
	cmd_list = commands;
	shell_reset();
}
