/* SPDX-License-Identifier: MIT
 *
 * MIT License
 *
 * Copyright (c) 2015 Christoph Göttschkes
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#ifndef VERSION
#define VERSION "n/a"
#endif

static char *prog_name = "throttle";
static int in_fast_mode = 0;

static int version(void) {
	puts(VERSION);
	return EXIT_SUCCESS;
}

static int help(int exit_code) {
	fprintf((exit_code) ? stderr : stdout, "Usage: %s [-f] [-vh]\n", prog_name);
	return exit_code;
}

static int configure(FILE *stream) {
	if (!in_fast_mode) {
		/* setvbuf might not set errno on failure */
		/* also, the return value in case of a failure is nonzero, not -1 */
		errno = 0;
		if (setvbuf(stream, NULL, _IONBF, 0) != 0) {
			char *err_str = "request cannot be honored";
			if (errno) {
				err_str = strerror(errno);
			}
			fprintf(stderr, "%s: setvbuf: %s\n", prog_name, err_str);
			return -1;
		}
	}
	return 0;
}

static int run(void) {
	int c;
	for (;;) {
		errno = 0;
		c = getchar();
		if (c == EOF) {
			if (!errno) {
				return 0;
			}
			fprintf(stderr, "%s: getchar: %s\n", prog_name, strerror(errno));
			return -1;
		}
		if (putchar(c) == EOF) {
			fprintf(stderr, "%s: putchar: %s\n", prog_name, strerror(errno));
			return -1;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc > 0) {
		prog_name = *argv;
	}
	for (--argc, ++argv; argc; --argc, ++argv) {
		char *arg = *argv;
		if (*arg == '-') {
			if (*(arg + 1) == '-' && *(arg + 2) == '\0') {
				break;
			}
			for (++arg; *arg; ++arg) {
				switch (*arg) {
					case 'h':
						return help(EXIT_SUCCESS);
					case 'v':
						return version();
					case 'f':
						in_fast_mode = 1;
						break;
					default:
						fprintf(stderr,
						        "%s: illegal option -- %c\n",
						        prog_name,
						        *arg
						);
						return help(EXIT_FAILURE);
				}
			}
		}
	}
	if (configure(stdin) == -1 || configure(stdout) == -1) {
		return EXIT_FAILURE;
	}
	if (run() == -1) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
