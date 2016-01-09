THROTTLE(1)                        Commands                        THROTTLE(1)



NAME
       throttle - A very slow pipe


SYNOPSIS
       throttle [-f] [-vh]


DESCRIPTION
       throttle  transfers  all  data  from its standard input to its standard
       output.  Unlike the normal pipe, the data is first read into  the  pro‐
       grams  memory and then written to is standard output again.  This slows
       down the data transfer significantly.

       This tool is designed to be used for testing other command line  utili‐
       ties.

       In  fast  mode,  the  C library I/O buffering remains enabled and might
       speed up the transfer process.


OPTIONS
       -f     enable fast mode

       -v     output version information and exit

       -h     output a help and exit


EXAMPLES
       Piping through throttle should be very slowest
              $ dd if=/dev/zero bs=4K count=1K | throttle >/dev/null


       Using the -f option should speed up the process
              $ dd if=/dev/zero bs=4K count=1K | throttle -f >/dev/null


       Not using throttle at all is the fastest of the three examples
              $ dd if=/dev/zero bs=4K count=1K >/dev/null


AUTHOR
       Written by Christoph Göttschkes.


COPYRIGHT
       Copyright (c) 2015-2016 Christoph Göttschkes.

       Released under MIT license.



throttle 1.1.0                    2015-03-28                       THROTTLE(1)
