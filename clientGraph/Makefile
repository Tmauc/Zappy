##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

CLIENT_NAME	=	zappy_graph

CLIENT_SRCS	=	src/get_infos_from_serv.cpp				\
			src/GObject.cpp				\
			src/TObject.cpp				\
			src/SFMLInterface.cpp

CLIENT_OBJS	=	$(CLIENT_SRCS:.cpp=.o)
CLIENT_INCL	=	-I./inc
++		=	g++
RM		=	rm -f
CFLAGS		=	-W -Wall -Wextra -g
LIBS		=	-L /usr/local/lib -l sfml-window -l sfml-graphics -l sfml-system -l sfml-audio
LDFLAGS		=	$(LIBS)

.cpp.o:
	@$(++) $(CFLAGS) $(CLIENT_INCL) -c $< -o $@
	@printf " \033[34m[Compiled]\033[39m %s\n" $<

.PHONY: all
all:	$(CLIENT_OBJS)
	@$(++) $(LDFLAGS) $(CLIENT_OBJS) -o $(CLIENT_NAME)
	@printf " \033[33m[Compilation Complete]\033[39m $(CLIENT_NAME)\n"

.PHONY: clean
clean:
	@$(RM) *~ $(CLIENT_OBJS)
	@find -name "*~" -delete
	@find -name "#*#" -delete
	@find -name "vgcore*" -delete
	@find -name "~.o" -delete
	@find -name "*.a" -delete
	@printf " \033[31m[Deleted] \033[39m%s\n" $(CLIENT_OBJS)

.PHONY: fclean
fclean: clean
	@$(RM) $(CLIENT_NAME)
	@printf " \033[33m[Delete Complete] \033[39m%s\n" $(CLIENT_NAME)

.PHONY: re
re:	fclean all

#make re && ./zappy_ai -p 8000 -n aa
