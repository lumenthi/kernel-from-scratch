#include "kernlib.h"
#include "vga.h"
#include "printk.h"

uint16_t		kscreen[NB_SCREENS][VGA_WIDTH * VGA_HEIGHT];
uint16_t		*current_screen;
int				current_screen_id;

struct cursor	cursor[NB_SCREENS];
struct cursor	*current_cursor;
uint8_t			terminal_color;
uint16_t		*terminal_buffer;
bool			terminal_show_cursor;
unsigned int	line_count = 0;

void	terminal_initialize(void)
{
	current_screen_id = SCREEN1;
	current_screen = kscreen[current_screen_id];
	current_cursor = &cursor[current_screen_id];
	terminal_show_cursor = true;
	cursor[0].x = 0;
	cursor[0].y = 0;
	cursor[1].x = 0;
	cursor[1].y = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(0, terminal_color);
			kscreen[0][index] = vga_entry(0, terminal_color);
			kscreen[1][index] = vga_entry(0, terminal_color);
		}
	}

	printk("--- Welcome to 42 KFS | {green}Screen 1{reset} ---\n");
	swap_screen();
	printk("--- Welcome to 42 KFS | {cyan}Screen 2{reset} ---\n");
	swap_screen();

	cursor[0].y = VGA_HEIGHT - 1;
	cursor[1].y = VGA_HEIGHT - 1;
	swap_screen();
	printk("%s", KPROMPT);
	swap_screen();
	printk("%s", KPROMPT);
}

void	terminal_shift_right()
{
	unsigned char c = get_char_at(VGA_WIDTH - 1, VGA_HEIGHT - 1);
	if (c != 0) {
		terminal_shift_up();
		line_count++;
		current_cursor->y--;
	}
	size_t start_index = current_cursor->y * VGA_WIDTH + current_cursor->x;
	size_t index = start_index;
	while (index < VGA_WIDTH * VGA_HEIGHT - 1) {
		if (terminal_buffer[index] == 0)
			break;
		index++;
	}
	while (index > start_index) {
		terminal_buffer[index] = vga_entry(terminal_buffer[index - 1], terminal_color);
		current_screen[index] = current_screen[index - 1];
		index--;
	}
}

void	terminal_shift_left()
{
	size_t index = current_cursor->x + VGA_WIDTH * current_cursor->y;
	while (index < VGA_WIDTH * VGA_HEIGHT - 1) {
		terminal_buffer[index] = vga_entry(terminal_buffer[index + 1], terminal_color);
		current_screen[index] = current_screen[index + 1];
		index++;
	}
}

void	terminal_shift_up()
{
	for (int y = 1; y < VGA_HEIGHT - 1; y++) {
		const size_t row = y * VGA_WIDTH;
		const size_t next_row = (y + 1) * VGA_WIDTH;
		for (int x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[row + x] = terminal_buffer[next_row + x];
			current_screen[row + x] = current_screen[next_row + x];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(0, terminal_color);
		current_screen[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(0, terminal_color);
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
	if (current_cursor->x == VGA_WIDTH)
		return 0;
	return get_terminal_char(current_cursor->x + 1, current_cursor->y);
}

void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	current_screen[index] = vga_entry(c, color);
}

void	swap_screen()
{
	current_screen_id = current_screen_id == SCREEN1 ? SCREEN2 : SCREEN1;
	current_screen = kscreen[current_screen_id];
	current_cursor = &cursor[current_screen_id];
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = current_screen[index];
		}
	}
	update_cursor();
}
