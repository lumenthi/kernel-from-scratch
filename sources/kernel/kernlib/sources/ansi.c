#include "kernlib.h"
#include "vga.h"

/* TODO: more complete ansi */
void	analyze_ansi(char *ansi_sequ)
{
	if (ansi_sequ[0] != '[')
		return ;
	int	nb = atoi(ansi_sequ + 1);
	switch (nb) {
		case 0:
			terminal_setcolor(VGA_COLOR_LIGHT_GREY);
			break;
		case 30:
			terminal_setcolor(VGA_COLOR_BLACK);
			break;
		case 31:
			terminal_setcolor(VGA_COLOR_RED);
			break;
		case 32:
			terminal_setcolor(VGA_COLOR_GREEN);
			break;
		case 33:
			terminal_setcolor(VGA_COLOR_BROWN);
			break;
		case 34:
			terminal_setcolor(VGA_COLOR_BLUE);
			break;
		case 35:
			terminal_setcolor(VGA_COLOR_MAGENTA);
			break;
		case 36:
			terminal_setcolor(VGA_COLOR_CYAN);
			break;
		case 37:
			terminal_setcolor(VGA_COLOR_DARK_GREY);
			break;
		case 40:
			terminal_setcolor(VGA_COLOR_BLACK);
			break;
		case 41:
			terminal_setcolor(VGA_COLOR_LIGHT_RED);
			break;
		case 42:
			terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
			break;
		case 43:
			terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
			break;
		case 44:
			terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
			break;
		case 45:
			terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
			break;
		case 46:
			terminal_setcolor(VGA_COLOR_LIGHT_CYAN);
			break;
		case 47:
			terminal_setcolor(VGA_COLOR_LIGHT_GREY);
			break;
		default:
			break;
	}
}

