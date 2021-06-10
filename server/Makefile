GREEN		= \033[0;32m
BLUE		= \033[0;34m
NC		= \033[0m
WHITE_BG	= \033[47m
BLINK		= \033[5m

MENTION_START	= $(BLUE)$(WHITE_BG)
MENTION_END	= $(NC)$(GREEN)

CMDS_DIR  	= cmds_zappy
CMDS_TARGET	= libzappy_cmds.a
IO_DIR  	= io_zappy
IO_TARGET	= libzappy_io.a
SERVER_DIR	= server_zappy
SERVER_TARGET	= zappy_server

.PHONY: all clean fclean re
all: clear_targets create end_build
clean: clear_targets
fclean: fclean_dirs clear_targets
re: fclean all

.PHONY: clear_targets
clear_targets:
	@unlink $(CMDS_TARGET) || true
	@unlink $(IO_TARGET) || true
	@unlink $(SERVER_TARGET) || true

.PHONY: create
create:
	@echo -e "$(GREEN)****************************"
	@echo -e "* Begin $(MENTION_START)$(BLINK)$(SERVER_TARGET)$(MENTION_END) build *"
	@echo -e "****************************$(NC)"
	@echo -e "$(GREEN)Building $(MENTION_START)cmds$(MENTION_END)'s library...$(NC)"
	@(cd $(CMDS_DIR) && $(MAKE))
	@echo ""
	@echo -e "$(GREEN)Building $(MENTION_START)io$(MENTION_END)'s library...$(NC)"
	@(cd $(IO_DIR) && $(MAKE))
	@echo ""
	@echo -e "$(GREEN)Building $(MENTION_START)zappy_server$(MENTION_END) binary...$(NC)"
	@(cd $(SERVER_DIR) && $(MAKE))
	@echo -e "$(GREEN)"
	@echo -e "****************************"
	@echo -e "* All files Built: $(MENTION_START)$(BLINK)Success$(MENTION_END) *"
	@echo -e "****************************$(NC)"

.PHONY: end_build
end_build:
	@ln -s $(CMDS_DIR)/$(CMDS_TARGET) .
	@ln -s $(IO_DIR)/$(IO_TARGET) .
	@ln -s $(SERVER_DIR)/$(SERVER_TARGET) .

.PHONY: fclean_dirs
fclean_dirs:
	@(cd $(CMDS_DIR) && $(MAKE) fclean)
	@(cd $(IO_DIR) && $(MAKE) fclean)
	@(cd $(SERVER_DIR) && $(MAKE) fclean)
