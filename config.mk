# version
VERSION = 1.0.0

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS =
LIBS =

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic \
		 -Wall -Wextra -Werror -Wno-deprecated-declarations \
		 -O0 \
		 ${INCS} ${CPPFLAGS}
LDFLAGS = ${LIBS}

# compiler, linker, and other tools
CC = gcc
SHELL = /bin/sh
