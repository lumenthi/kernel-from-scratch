NAME = kernlib.a

SRC_DIR = sources
OBJ_DIR = objects
INCLUDES_DIR = headers
BIN_DIR = .
PRINTK_DIR = printk
PRINTK_SRC_DIR = $(addprefix $(PRINTK_DIR)/, sources)
PRINTK_INC_DIR = $(addprefix $(PRINTK_DIR)/, headers)
PRINTK_OBJ_DIR = $(addprefix $(PRINTK_DIR)/, objects)
OPTI_FLAGS = -O3

SRC_RAW =	strlen.c \
			memset.c \
			memcpy.c \
			memmove.c \
			bzero.c \
			write.c \
			cursor.c \
			kputchar.c \
			kputstr.c \
			out.c \
			in.c \
			itoa.c \
			terminal.c \
			strcmp.c \
			atoi.c \
			ansi.c \
			poweroff.c \
			reboot.c \
			case.c \
			print_bits.c \
			print_stack.c \
			print_hexa.c \

SRC_SIZE = $(shell ls sources | wc -l)

HEADERS = kernlib.h vga.h

PRINTK_SRC_RAW =	base_utils.c \
					bprintk.c \
					custom_error.c \
					custom_invalid.c \
					dprintk.c \
					fill_buffer.c \
					noprintk.c \
					novprintk.c \
					parse_colors.c \
					parse_flags.c \
					parse_functions.c \
					pf_atoi.c \
					pf_float_padding.c \
					pf_invalid.c \
					pf_putaddr.c \
					pf_putchar.c \
					pf_putlong_base.c \
					pf_putnbr.c \
					pf_putnbr_base.c \
					pf_putpercent.c \
					pf_putstr.c \
					pf_putunbr.c \
					pf_strnequ.c \
					printk.c \
					put_padding.c \
					snprintk.c \
					sprintk.c \
					vprintk.c \
					vsnprintk.c \
					vsprintk.c \

PRINTK_SRC_SIZE = $(shell ls printk/sources | wc -l)

PRINTK_HEADERS = printk.h base_utils.h color.h put_padding.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

PRINTK_SRC = $(addprefix $(PRINTK_SRC_DIR)/, $(PRINTK_SRC_RAW))
PRINTK_OBJ = $(addprefix $(PRINTK_OBJ_DIR)/, $(PRINTK_SRC_RAW:.c=.o))

ifeq ($(OS), Windows_NT)
	OPTI_FLAGS = -O3
else
    OPTI_FLAGS = -O3
endif

CFLAGS =	-I $(INCLUDES_DIR) -I $(PRINTK_INC_DIR) \
			-Wno-unused-result -m32 \
			-fno-builtin \
			-fno-exceptions \
			-fno-stack-protector \
			-nostdlib \
			-nodefaultlibs \
			-fno-pic \
			-m32 \
			-ffreestanding \
			-static \
			#$(OPTI_FLAGS) \
			#-fsanitize=address -g3 \

# Color declarations
RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"
BLANK = '\033[0m'

TICK = '\033[1;32m~\033[0m'
CROSS = '\033[1;31mx\033[0m'


all: $(BIN_DIR)/$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(PRINTK_OBJ_DIR):
	@mkdir -p $(PRINTK_OBJ_DIR)

I = 1
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
#	@printf $(YELLOW)"[$(I)/$(SRC_SIZE)] Compiling $<\n"$(RESET)
	$(eval I=$(shell echo $$(($(I) + 1))))
	gcc -c $< -o $@ $(CFLAGS)

PI = 1
$(PRINTK_OBJ_DIR)/%.o: $(PRINTK_SRC_DIR)/%.c
#	@printf $(YELLOW)"[$(PI)/$(PRINTK_SRC_SIZE)] Compiling $<\n"$(RESET)
	$(eval PI=$(shell echo $$(($(PI) + 1))))
	gcc -c $< -o $@ $(CFLAGS)

$(BIN_DIR)/$(NAME): $(OBJ_DIR) $(OBJ) $(PRINTK_OBJ_DIR) $(PRINTK_OBJ)
#	@printf "\e[0;36m[INFO] Linking ${NAME}\e[0m\n"
	ar rc --target elf32-i386 $(NAME) $(OBJ) $(PRINTK_OBJ)
	ranlib $(NAME)
	@ printf " %b | Compiled %blibft%b\n" $(TICK) $(GREEN) $(BLANK)

clean:
	@ test -d $(OBJ_DIR) && rm -rf $(OBJ_DIR) && \
	test -d $(PRINTK_OBJ_DIR) && \
	rm -rf $(PRINTK_OBJ_DIR) && \
	printf " %b | " $(TICK) && \
	printf "Removed %bkernlib%b object folder\n" $(YELLOW) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %bkernlib%b object folder\n" $(YELLOW) $(BLANK))

fclean: clean
	@ test -f $(NAME) && \
	rm -rf $(NAME) && \
	printf " %b | " $(TICK) && \
	printf "Removed %bkernlib%b library\n" $(RED) $(BLANK) \
	|| (printf " %b | " $(CROSS) && \
	printf "No %bkernlib%b library\n" $(RED) $(BLANK))

re: fclean all

.PHONY: fclean all clean kernlib
