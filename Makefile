##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC_SERVER 		= 		src/server/main.c \
						src/server/server.c \
						src/server/handle_clients.c \
						src/my_str_to_word_array.c \
						src/count_elements_arr.c \
						src/server/login.c \
						src/server/logout.c \
						src/server/help.c \
						src/server/users.c \
						src/server/save_users.c \
						src/server/init_db.c \
						src/server/user.c \
						src/server/save_private_msgs.c \
						src/server/send.c \
						src/server/messages.c \

SRC_CLIENT 		= 		src/client/main.c \
						src/client/client.c \
						src/client/is_command.c \
						src/client/handle_replies_auth.c \
						src/client/handle_replies_users.c \
						src/my_str_to_word_array.c \
						src/count_elements_arr.c \
						src/client/handle_replies_msgs.c \

OBJ_SERVER 		=		$(SRC_SERVER:.c=.o)

OBJ_CLIENT		=		$(SRC_CLIENT:.c=.o)

NAME_SERVER 	=		myteams_server

NAME_CLIENT 	=	 	myteams_cli

CPPFLAGS	=		-iquote include/

CFLAGS 		=		-Werror -Wall -Wextra

LIB			=		-luuid -L libs/myteams -lmyteams

CC 		?=		gcc

RM 		?= 		rm -f

all: db
all: server
all: client

db:
	[ -d db/ ] || mkdir -p db/
	[ -d db/users/ ] || mkdir -p db/users/
	[ -d db/users/private_msgs ] || mkdir -p db/users/private_msgs
	[ -d db/teams/ ] || mkdir -p db/teams/
	[ -d db/teams/descriptions ] || mkdir -p db/teams/descriptions
	[ -d db/teams/members ] || mkdir -p db/teams/members

server: $(OBJ_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIB)

client: $(OBJ_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIB)

debug: CFLAGS += -g3
debug: re

clean:
	$(RM) $(OBJ_SERVER)
	$(RM) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY:	fclean clean all re debug tests_run
