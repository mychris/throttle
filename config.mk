# version
VERSION = 1.1.0

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# flags
CPPFLAGS = -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c99 -pedantic
CFLAGS  += -Wall -Wextra -Werror -Wno-deprecated-declarations
CFLAGS  += -O0
LDFLAGS  =
LDLIBS   =

# compiler, linker, and other tools
CC = gcc
SHELL = /bin/sh
