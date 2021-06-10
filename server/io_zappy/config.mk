##### MAKE PROJECT SETTINGS #####

TARGET_NAME		:= libzappy_io.a

CC			?= gcc

INCLUDES		= -I ../server_zappy/includes -I ./includes
LIBS			=

SRC_EXT			= c
SRC_PATH		= ./sources

COMPILE_FLAGS		=  -Wall -Wextra
LINK_FLAGS		=

export MAKE_VERBOSE ?= false
