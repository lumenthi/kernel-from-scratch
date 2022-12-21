#include "kernlib.h"
#include "vga.h"
#include "printk.h"

size_t		terminal_row;
size_t		terminal_column;
uint8_t		terminal_color;
uint16_t	*terminal_buffer;
bool		terminal_show_cursor;

void	terminal_initialize(void)
{
	terminal_show_cursor = true;
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(0, terminal_color);
		}
	}

	printk("Welcome to --KFS--\n");

	terminal_row = VGA_HEIGHT - 1;
	printk("%s", KPROMPT);
}

void	terminal_shift_right()
{
	size_t x;
	for (x = terminal_column; x < VGA_WIDTH - 1; x++) {
		const size_t index = terminal_row * VGA_WIDTH + x;
		if (terminal_buffer[index] == 0)
			break;
	}
	x--;
	for ( ; x > terminal_column; x--) {
		const size_t index = terminal_row * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(terminal_buffer[index - 1], terminal_color);
	}
}

void	terminal_shift_up()
{
	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		const size_t row = y * VGA_WIDTH;
		const size_t next_row = (y + 1) * VGA_WIDTH;
		for (int x = 0; x < VGA_WIDTH - 1; x++)
			terminal_buffer[row + x] =
				vga_entry(terminal_buffer[next_row + x], terminal_color);
	}
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(0, terminal_color);
	}
}

void	terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

unsigned char	get_terminal_char(int x, int y)
{
	return terminal_buffer[y * VGA_WIDTH + x];
}

unsigned char	get_next_char()
{
	if (terminal_column == VGA_WIDTH)
		return 0;
	return get_terminal_char(terminal_column + 1, terminal_row);
}

void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
