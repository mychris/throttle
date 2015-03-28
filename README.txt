THROTTLE(1)                        Commands                        THROTTLE(1)



NAME
       throttle - A very slow pipe


SYNOPSIS
       throttle [-f] [-vh]


DESCRIPTION
       throttle  transfers  all  data  from its standard input to its standard
       output.  Unlike the normal pipe, the data is  read  into  the  programs
       memory  and  the  printed out again.  This slows down the data transfer
       significantly.

       This tool is designed to be used for testing other command line  utili‐
       ties.

       In  fast  mode,  the  C library I/O buffering remains enabled and might
       speed up the transfer process.


OPTIONS
       -f     enable fast mode

       -v     output version information and exit

       -h     output a help and exit


AUTHOR
       Written by Christoph Göttschkes.


COPYRIGHT
       Copyright (c) 2015 Christoph Göttschkes.

       Released under MIT license.



throttle 1.0.0                    2015-03-22                       THROTTLE(1)
