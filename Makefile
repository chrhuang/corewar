# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sregnard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:51:18 by sregnard          #+#    #+#              #
#    Updated: 2019/10/27 20:22:28 by sregnard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###### EXECUTABLES

ASM						:=	asm
COREWAR					:=	corewar

###### LIBFT

LIBDIR					:=	libft/
LIBFT					:=	$(LIBDIR)libft.a

###### DIRECTORIES

INCDIR					:=	includes/
SRCDIR					:=	srcs/
OBJDIR					:=	objs/

DIR_ASM					:=	asm/
DIR_WAR					:=	corewar/
DIR_COM					:=	common/

INCDIR_ASM				:=	$(INCDIR)$(DIR_ASM)
INCDIR_WAR				:=	$(INCDIR)$(DIR_WAR)
INCDIR_COM				:=	$(INCDIR)$(DIR_COM)

SRCDIR_ASM				:=	$(SRCDIR)$(DIR_ASM)
SRCDIR_WAR				:=	$(SRCDIR)$(DIR_WAR)
SRCDIR_COM				:=	$(SRCDIR)$(DIR_COM)

OBJDIR_ASM				:=	$(OBJDIR)$(DIR_ASM)
OBJDIR_WAR				:=	$(OBJDIR)$(DIR_WAR)
OBJDIR_COM				:=	$(OBJDIR)$(DIR_COM)

######	INCLUDES

INCLUDES				:=	-I $(INCDIR_COM)
INCLUDES				+=	-I $(LIBDIR)$(INCDIR)

INCLUDES_ASM			:=	$(INCLUDES)
INCLUDES_ASM			+=	-I $(INCDIR_ASM)

INCLUDES_WAR			:=	$(INCLUDES)
INCLUDES_WAR			+=	-I $(INCDIR_WAR)

INCNAME					:=	asm.h
INC_ASM					:=	$(addprefix $(INCDIR_ASM), $(INCNAME))

INCNAME					:=	corewar.h
INC_WAR					:=	$(addprefix $(INCDIR_WAR), $(INCNAME))

INCNAME					:=	common.h
INC_COM					:=	$(addprefix $(INCDIR_COM), $(INCNAME))

######	SOURCES

SRCNAME					:=	asm.c
SRC_ASM					:=	$(addprefix $(SRCDIR_ASM), $(SRCNAME))

SRCNAME					:=	corewar.c
SRC_WAR					:=	$(addprefix $(SRCDIR_WAR), $(SRCNAME))

SRCNAME					:=	common.c
SRC_COM					:=	$(addprefix $(SRCDIR_COM), $(SRCNAME))

######	OBJECTS

OBJ_ASM					:=	$(SRC_ASM:$(SRCDIR_ASM)%.c=$(OBJDIR_ASM)%.o)
OBJ_WAR					:=	$(SRC_WAR:$(SRCDIR_WAR)%.c=$(OBJDIR_WAR)%.o)
OBJ_COM					:=	$(SRC_COM:$(SRCDIR_COM)%.c=$(OBJDIR_COM)%.o)

######	FLAGS

CC						:=	gcc	
CFLAGS					:=	-Wall -Wextra -Werror

######	COLORS

_RED					:=	\033[1;31m
_GREEN					:=	\033[1;32m
_YELLOW					:=	\033[1;33m
_BLUE					:=	\033[1;34m
_MAGENTA				:=	\033[1;35m
_CYAN					:=	\033[1;36m
_BG_RED					:=	\033[1;41m
_BG_GREEN				:=	\033[1;42m
_BG_YELLOW				:=	\033[1;43m
_BG_BLUE				:=	\033[1;44m
_BG_MAGENTA				:=	\033[1;45m
_BG_CYAN				:=	\033[1;46m
_RESET					:=	\033[0m

######	RULES

all						:	$(LIBFT) $(ASM) $(COREWAR)

$(LIBFT)				:
	@make -C $(LIBDIR)

$(ASM)					:	$(LIBFT) $(OBJ_ASM) $(OBJ_COM)
	$(CC) $(CFLAGS) $(INCLUDES_ASM) $(LIBFT) -o $@ $(OBJ_COM) $(OBJ_ASM)

$(COREWAR)				:	$(LIBFT) $(OBJ_WAR) $(OBJ_COM)
	$(CC) $(CFLAGS) $(INCLUDES_WAR) $(LIBFT) -o $@ $(OBJ_COM) $(OBJ_WAR)

$(OBJDIR_ASM)%.o		:	$(SRCDIR_ASM)%.c $(INC_ASM) $(INC_COM)
	@mkdir -p $(OBJDIR_ASM);
	$(CC) $(CFLAGS) $(INCLUDES_ASM) -o $@ -c $<

$(OBJDIR_WAR)%.o		:	$(SRCDIR_WAR)%.c $(INC_WAR) $(INC_COM)
	@mkdir -p $(OBJDIR_WAR);
	$(CC) $(CFLAGS) $(INCLUDES_WAR) -o $@ -c $<

$(OBJDIR_COM)%.o		:	$(SRCDIR_COM)%.c $(INC_COM)
	@mkdir -p $(OBJDIR_COM);
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean					:
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(ASM)
	@printf "$(_BLUE)%-10s : Objects\tcleaned.\n$(_RESET)" $(COREWAR)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean					:	clean
	@rm -rf $(ASM) $(WAR)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(ASM)
	@printf "$(_MAGENTA)%-10s : Executable\tcleaned.\n$(_RESET)" $(COREWAR)
	@rm -rf $(LIBFT)
	@printf "$(_MAGENTA)%-10s : Library\tcleaned.\n$(_RESET)" $(notdir $(LIBFT))

re						:	fclean	all