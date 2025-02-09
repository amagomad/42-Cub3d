# ---------------------------------- COLORS ---------------------------------- #
DEF     = \033[0m
BOLD    = \033[1m
CUR     = \033[3m
UL      = \033[4m
UP      = \033[A

RED     = \033[38;5;124m
LBLUE   = \033[38;5;153m
LYELLOW = \033[38;5;228m
LPURPLE = \033[38;5;189m
LGREEN  = \033[38;5;155m

# ----------------------------- COMPILER / FLAGS ----------------------------- #
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBRARY = libft.a

# ----------------------------- PATHS / SOURCES ----------------------------- #
SRC_PATH = src/
CHAR_PATH = ${SRC_PATH}char/
IS_PATH = ${SRC_PATH}is/
LST_PATH = ${SRC_PATH}lst/
MEM_PATH = ${SRC_PATH}mem/
PUT_PATH = ${SRC_PATH}put/

SRC_CHAR = ${addprefix ${CHAR_PATH}, ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
                           ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
                           ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
                           ft_split.c ft_striteri.c ft_strmapi.c ft_strlen.c ft_strcmp.c \
						   append_char.c ft_charinstr.c ft_strcpy.c }

SRC_IS = ${addprefix ${IS_PATH}, ft_isalpha.c ft_isdigit.c ft_isalnum.c \
                         ft_isascii.c ft_isprint.c}

SRC_LST = ${addprefix ${LST_PATH}, ft_lstnew.c ft_lstsize.c ft_lstlast.c \
                          ft_lstadd_front.c ft_lstaddback.c \
                          ft_lstdelone.c ft_lstclear.c \
                          ft_lstiter.c ft_lstmap.c}

SRC_MEM = ${addprefix ${MEM_PATH}, ft_memset.c ft_bzero.c ft_memcpy.c \
                           ft_memmove.c ft_calloc.c ft_memcmp.c ft_memchr.c}

SRC_PUT = ${addprefix ${PUT_PATH}, ft_atoi.c ft_itoa.c ft_putchar_fd.c \
                           ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c}

SRC = ${SRC_CHAR} ${SRC_IS} ${SRC_LST} ${SRC_MEM} ${SRC_PUT}

OBJ = ${SRC:.c=.o}
TOTAL_OBJ = $(words ${OBJ})
COMPILED_OBJ = 0

# ----------------------------- COMPILATION RULES ----------------------------- #
all: ${LIBRARY}

# Compilation de la libft avec affichage final "COMPILED ✅"
${LIBRARY}: ${OBJ}
	@ar rcs ${LIBRARY} ${OBJ}
	@printf "\r${LYELLOW}Compiling: ${LGREEN}COMPILED ✅ ${LYELLOW}Progress: [%-50s] (%d/%d)\n${DEF}" \
		$$(printf '#%.0s' $$(seq 1 50)) $(TOTAL_OBJ) $(TOTAL_OBJ)
	@echo "\n${BOLD}${LGREEN}✔ Compilation completed successfully!${DEF}\n"

# ------------------------------- OBJECTS RULES ------------------------------ #
%.o: %.c
	@$(eval COMPILED_OBJ=$(shell echo $$(($(COMPILED_OBJ) + 1))))
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r${LYELLOW}Compiling: ${LPURPLE}%-30s ${LYELLOW}Progress: [%-50s] (%d/%d)\r${DEF}" \
		$< \
		$$(printf '#%.0s' $$(seq 1 $$(($(COMPILED_OBJ)*50/$(TOTAL_OBJ))))) \
		$(COMPILED_OBJ) $(TOTAL_OBJ)

# --------------------------------- CLEANING --------------------------------- #
clean:
	@rm -f ${OBJ}
	@echo "${RED}${BOLD}🗑️  Cleaning object files...${DEF}"

fclean: clean
	@rm -f ${LIBRARY}
	@echo "${RED}${BOLD}🗑️  Library removed...${DEF}"

# --------------------------------- REBUILD --------------------------------- #
re: fclean all

# --------------------------------- PHONY --------------------------------- #
.PHONY: all clean fclean re