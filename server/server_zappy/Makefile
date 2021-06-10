### MAKE PROJECT FILE ###
include config.mk

BYellow	=	\033[1;33m
NC	=	\033[0m
BGreen	=	\033[1;32m

# Generally should not need to edit below this line

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Shell used in this makefile
# bash is used for 'echo -ne'
SHELL = /bin/bash

# Append pkg-config specific libraries if need be
ifneq ($(LIBS),)
	#COMPILE_FLAGS += $(shell pkg-config --cflags $(LIBS))
	#LINK_FLAGS += $(shell pkg-config --libs $(LIBS))
	LINK_FLAGS += $(LIBS)
endif

# Verbose option, to output compile and link commands
ifeq ($(MAKE_VERBOSE),false)
	CMD_PREFIX :=	@
endif

# Combine compiler and linker flags
release: export CFLAGS := $(CFLAGS) $(COMPILE_FLAGS)
release: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS)

# Build and output paths
release: export BUILD_PATH := target/build
release: export BIN_PATH := target/bin

# Find all source files in the source directory, sorted by most
# recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
	  | sort -k 1nr | cut -f2-)

# fallback in case the above fails
rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) \
	    $(filter $(subst *,%,$2), $d))
ifeq ($(SOURCES),)
	SOURCES := $(call rwildcard, $(SRC_PATH), *.$(SRC_EXT))
endif

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# Macros for timing compilation
TIME_FILE = $(dir $@).$(notdir $@)_time
START_TIME = date '+%s' > $(TIME_FILE)
END_TIME = read st < $(TIME_FILE) ; \
	   $(RM) $(TIME_FILE) ; \
	   st=$$((`date '+%s'` - $$st - 86400)) ; \
	   echo `date -u -d @$$st '+%H:%M:%S'`

# Standard build
.PHONY: release
release: dirs
	@echo "Beginning build"
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Create the directories used in the build
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting build directorie"
	@$(RM) -r build

.PHONY: fclean
fclean: clean
	@echo "Deleting $(TARGET_NAME) symlink"
	@$(RM) $(TARGET_NAME)
	@echo "Deleting target directorie"
	@$(RM) -r target

.PHONY: re
re: fclean release

.PHONY: all
all: $(BIN_PATH)/$(TARGET_NAME)
	@echo "Making symlink: $(TARGET_NAME) -> $<"
	@$(RM) $(TARGET_NAME)
	@ln -s $(BIN_PATH)/$(TARGET_NAME) $(TARGET_NAME)

# Link the executable
$(BIN_PATH)/$(TARGET_NAME): $(OBJECTS)
	@echo -e "Linking: $(BGreen)$@$(NC)"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo -en "\t Link time: "
	@$(END_TIME)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo -e "Compiling: $(BYellow)$<$(NC) -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)
