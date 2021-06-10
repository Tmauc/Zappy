##### MAKE PROJECT SETTINGS #####

TARGET_NAME		:= zappy_server

CC			?= gcc

INCLUDES		= -I ./includes
LIBS			= -L ./../cmds_zappy -l zappy_cmds -L ./../io_zappy -l zappy_io

SRC_EXT			= c
SRC_PATH		= ./sources

COMPILE_FLAGS		=  -Wall -Wextra
LINK_FLAGS		=

export MAKE_VERBOSE ?= false
