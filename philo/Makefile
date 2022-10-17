# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:14:43 by yongmkim          #+#    #+#              #
#    Updated: 2022/05/14 20:43:35 by yongmkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#==============================================================================
#░░░░░░███╗░░░███╗░█████╗░██╗░░██╗███████╗███████╗██╗██╗░░░░░███████╗░░░░░░░░░░
#░░░░░░████╗░████║██╔══██╗██║░██╔╝██╔════╝██╔════╝██║██║░░░░░██╔════╝░░░░░░░░░░
#░░░░░░██╔████╔██║███████║█████═╝░█████╗░░█████╗░░██║██║░░░░░█████╗░░░░░░░░░░░░
#░░░░░░██║╚██╔╝██║██╔══██║██╔═██╗░██╔══╝░░██╔══╝░░██║██║░░░░░██╔══╝░░░░░░░░░░░░
#░░░░░░██║░╚═╝░██║██║░░██║██║░╚██╗███████╗██║░░░░░██║███████╗███████╗░░░░░░░░░░
#░░░░░░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚══════╝╚══════╝░░░░░░░░░░
#==============================================================================
#	Color
#==============================================================================
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
ORANGE		=	\e[38;5;214m
BLUE_PURPLE	=	\e[38;5;057m
PURPLE		=	\e[38;5;165m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_SUCCESS_	=	[$(ORANGE)SUCCESS$(RESET)]
_INFO		=	[$(ORANGE)INFO$(RESET)]
_NAME		=	[$(GREEN)$(NAME)$(RESET)]
_CLEAN		=	[$(BLUE_PURPLE)$(NAME)$(RESET)]
_NAME_B		=	[$(GREEN)$(NAME_B)$(RESET)]
_PROG		=	$(_INFO) [$(ORANGE)$(NAME)$(RESET)] - Compile $(YELLOW)
_DONE		=	$(GREEN)✓$(RESET)
#	Loading bar
#==============================================================================
SHELL	=	/bin/bash
sp		=	/-\|/
idx		=	0
#░░░░░░░░░░░░░░░░░░░░██╗░░░██╗░█████╗░███╗░░░███╗░█████╗░░░░░░░░░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░╚██╗░██╔╝██╔══██╗████╗░████║██╔══██╗░░░░░░░░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░░╚████╔╝░██║░░██║██╔████╔██║███████║░░░░░░░░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░░░╚██╔╝░░██║░░██║██║╚██╔╝██║██╔══██║░░░░░░░░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░░░░██║░░░╚█████╔╝██║░╚═╝░██║██║░░██║░░░░░░░░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░░░░╚═╝░░░░╚════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝░░░░░░░░░░░░░░░░░░░░░░
#==============================================================================
# 	Target Name
#==============================================================================
NAME		=	philo
TARGET		=	$(NAME)

#==============================================================================
#	Source
#==============================================================================
SRC			=	main.c	\
				error.c	\
				util.c	\
				philo.c	\
				philo_util.c	\
				mutex.c	\

#==============================================================================
#	Directory
#==============================================================================
OBJ_DIR		=	./object/
SRC_DIR		=	./source/
INC_DIR		=	./include/
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIB_LNK		=	-I $(INC_DIR)
OBJECT		=	$(OBJ)

#==============================================================================
#	Compile
#==============================================================================
CC			=	gcc
CC_FLAG		=	-Wall -Wextra -Werror
RM			=	rm
RM_FLAG		=	-f
SNTZ		=	-g -fsanitize=address -fno-omit-frame-pointer
THREAD		=	-g -fsanitize=thread -fno-omit-frame-pointer
MEM			=	-g -fsanitize=memory -fsanitize-memory-track-origins \
				-fPIE -pie -fno-omit-frame-pointer
LEAK		=	-g -fsanitize=leak
DEBUG		=	-g
PTH_FLAG	=	-pthread
#==============================================================================
#	Basic Flag
#==============================================================================
CFLAG		=	$(CC_FLAG)
TEMP		=
DEFINE		=	-DLEAK_CHECK=1







#==============================================================================
#	Make Part 
#==============================================================================
.PHONY		:	all 
all			:
		@make obj_dir
		@make $(NAME)

$(NAME)		:	$(OBJECT)
		@if [ $(idx) -gt 0 ]; then\
			printf "\b$(_DONE)\n";\
		fi
		@$(CC) $(CFLAG) $(TEMP) $(PTH_FLAG) $(LIB_LNK) $(OBJECT) -o $(NAME)
		@printf "$(_SUCCESS) $(_NAME) - all $(_DONE)\n"

#==============================================================================
#	Object file, library Make  
#==============================================================================
.PHONY		:	obj_dir
obj_dir		:
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC_DIR)
		$(eval idx = $(shell expr $(idx) + 1))
		$(eval t_idx = $(shell expr $(idx) % 4 + 1))
		$(eval chr = $(shell echo $(sp) | cut -c $(t_idx)))
		@if [ $(idx) = 1 ]; then\
			printf "   $(_PROG) ";\
		fi
		@printf "\b$(chr)"
		@$(CC) $(CFLAG) $(PTH_FLAG) $(LIB_LNK) -o $@ -c $<

#==============================================================================
#	clean fclean re
#==============================================================================
.PHONY		:	clean fclean re clear fclear c f
c			:	clean
clear		:	clean
clean		:
		@$(RM) -rf $(OBJ_DIR)
		@printf "   $(_INFO) $(_CLEAN) - clean $(_DONE)\n"
f			:	fclean
fclear		:	fclean
fclean		:
		@make clean
		@$(RM) -f $(NAME)
		@printf "   $(_INFO) $(_CLEAN) - fclean $(_DONE)\n"

re			:
		@make fclean
		@make all






#==============================================================================
#	Sanitizer Memory Leak
#==============================================================================
.PHONY		:	sntz mem leak m s thread atexit
s			:	sntz
sntz		:	CFLAG+=$(SNTZ)
sntz		:	all
		@printf "$(_SUCCESS_) $(_NAME) - sntz $(_DONE)\n"

thread		:	CFLAG+=$(THREAD)
thread		:	all
		@printf "$(_SUCCESS_) $(_NAME) - thread $(_DONE)\n"

m			:	mem
mem			:	CFLAG+=$(MEM)
mem			:	all
		@printf "$(_SUCCESS_) $(_NAME) - mem $(_DONE)\n"

#atexit		:	TEMP+=$(DEFINE)
#atexit		:	all
#		@printf "$(_SUCCESS_) $(_NAME) - atexit $(_DONE)\n"

leak		:	CFLAG+=$(LEAK)
leak		:	all
		@printf "$(_SUCCESS_) $(_NAME) - leak $(_DONE)\n"

#==============================================================================
#	Debug
#==============================================================================
.PHONY		:	debug lldb d
lldb		:	debug
d			:	debug
debug		:	CFLAG+=$(DEBUG)
debug		:	all
		@printf "$(_SUCCESS_) $(_NAME) - debug $(_DONE)\n"

#==============================================================================
#	Show & Command List
#==============================================================================
.PHONY		:	show command com list
list		:	show
show		:	command
		@make big_flag
		@printf "NAME	: $(NAME)\n"
		@printf "CC	: $(CC)\n"
		@printf "CC_FLAG	: $(CC_FLAG)\n"
		@printf "PTH_FLAG	: $(PTH_FLAG)\n"
		@printf "SRC_DIR	: $(SRC_DIR)\n"
		@printf "OBJ_DIR	: $(OBJ_DIR)\n"
		@printf "INC_DIR	: $(INC_DIR)\n"
		@printf "SRC	: $(SRC)\n"
		@printf "COMPILE	: $(CC) $(CFLAG) $(PTH_FLAG) $(LIB_LNK) $(OBJECT)\n"
		@printf "\n"

com			:	command
command		:
		@make big_com
		@printf "all	: default, create target\n"
		@printf "clean	: del *.o\n"
		@printf "fclean	: [clean] + del target\n"
		@printf "re	: [fclean] + [all]\n"
		@printf "show	: print info\n"
		@printf "command	: print command list\n"
		@printf "sntz	: $(SNTZ)\n"
		@printf "mem	: $(MEM)\n"
		@printf "leak	: $(LEAK)\n"
		@printf "thread	: $(THREAD)\n"
		@printf "debug	: $(DEBUG)\n"
		@make big_alias
		@printf "clear	: [clean]\n"
		@printf "fclear	: [fclean]\n"
		@printf "list	: [show]\n"
		@printf "com	: [command]\n"
		@printf "lldb	: [debug]\n"
		@printf "s	: [sntz]\n"
		@printf "m	: [mem]\n"
		@printf "d	: [debug]\n"

#==============================================================================
#	Print Big text letter
#==============================================================================
.PHONY		:	big_com	big_alias big_flag
big_com		:
		@printf "\n$(YELLOW)"
		@printf "█▀▀ █▀█ █▀▄▀█ █▀▄▀█ ▄▀█ █▄░█ █▀▄   █░░ █ █▀ ▀█▀\n"
		@printf "█▄▄ █▄█ █░▀░█ █░▀░█ █▀█ █░▀█ █▄▀   █▄▄ █ ▄█ ░█░\n"
		@printf "$(RESET)"

big_alias	:
		@printf "\n$(ORANGE)"
		@printf "▄▀█ █░░ █ ▄▀█ █▀   █░░ █ █▀ ▀█▀\n"
		@printf "█▀█ █▄▄ █ █▀█ ▄█   █▄▄ █ ▄█ ░█░\n"
		@printf "$(RESET)"

big_flag	:
		@printf "\n$(GREEN)"
		@printf "█▀▀ █░░ ▄▀█ █▀▀   █░░ █ █▀ ▀█▀\n"
		@printf "█▀░ █▄▄ █▀█ █▄█   █▄▄ █ ▄█ ░█░\n"
		@printf "$(RESET)"
#==============================================================================
#	End of Makeflie
#==============================================================================
