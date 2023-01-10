#include "kernlib.h"
#include "printk.h"
#include "shell.h"
#include "vga.h"

void get_command(void)
{
	int x = KPROMPT_SIZE;
	int y = VGA_HEIGHT - line_count - 1;
	int offset = (x + y * VGA_WIDTH);
	int i = offset;
	char c;

	/* while (i < offset+20) {
		c = get_char_at_index(i);
		shell_buf[i-offset] = c;
		i++;
	} */

	while ((c = get_char_at_index(i))) {
	//	printk("shell_buf[%d] = %c\n",i-offset, c);
		shell_buf[i-offset] = c;
		i++;
	}
}

void shell_reset(void)
{
	shell_cursor = 0;
	bzero(shell_buf, INPUT_LENGTH);
}

void shell_initialize(void)
{
	shell_reset();
}
