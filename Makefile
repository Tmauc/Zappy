##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile
##

CLIENT_DIR  	= client
CLIENT_TARGET	= zappy_ai
GRAPHIC_DIR	= clientGraph
GRAPHIC_TARGET	= zappy_graph
SERVER_DIR	= server
SERVER_TARGET	= zappy_server

.PHONY: all clean fclean re
all: clear_targets create end_build
clean: clear_targets
fclean: fclean_dirs clear_targets
re: fclean all

.PHONY: clear_targets
clear_targets:
	@unlink $(CLIENT_TARGET) || true
	@unlink $(GRAPHIC_TARGET) || true
	@unlink $(SERVER_TARGET) || true

.PHONY: create
create:
	@(cd $(CLIENT_DIR) && $(MAKE))
	@(cd $(GRAPHIC_DIR) && $(MAKE))
	@(cd $(SERVER_DIR) && $(MAKE))

.PHONY: end_build
end_build:
	@#ln -s $(CLIENT_DIR)/$(CLIENT_TARGET)
	@#ln -s $(GRAPHIC_DIR)/$(GRAPHIC_TARGET)
	@#ln -s $(SERVER_DIR)/$(SERVER_TARGET)
	@cp $(CLIENT_DIR)/$(CLIENT_TARGET) .
	@cp $(GRAPHIC_DIR)/$(GRAPHIC_TARGET) .
	@cp $(SERVER_DIR)/$(SERVER_TARGET) .

.PHONY: fclean_dirs
fclean_dirs:
	@(cd $(CLIENT_DIR) && $(MAKE) fclean)
	@(cd $(GRAPHIC_DIR) && $(MAKE) fclean)
	@(cd $(SERVER_DIR) && $(MAKE) fclean)

.PHONY: client
client:
	@unlink $(CLIENT_TARGET) || true
	@unlink $(GRAPHIC_TARGET) || true
	@(cd $(CLIENT_DIR) && $(MAKE))
	@(cd $(GRAPHIC_DIR) && $(MAKE))
	@#ln -s $(CLIENT_DIR)/$(CLIENT_TARGET) .
	@#ln -s $(GRAPHIC_DIR)/$(GRAPHIC_TARGET) .
	@cp $(CLIENT_DIR)/$(CLIENT_TARGET) .
	@cp $(GRAPHIC_DIR)/$(GRAPHIC_TARGET) .

.PHONY: server
server:
	@unlink $(SERVER_TARGET) || true
	@(cd $(SERVER_DIR) && $(MAKE))
	@#ln -s $(SERVER_DIR)/$(SERVER_TARGET) .
	@cp $(SERVER_DIR)/$(SERVER_TARGET) .
