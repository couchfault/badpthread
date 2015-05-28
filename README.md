# Badpthread
This is a dynamic library that, when loaded into a process, will execute a function before that process's main that starts a new thread. This new thread will try to find whatever file is in argv[1], and find the symbol "main" in it. If it is successful, it will then execute the method.

This means that if it is injected into, say, `/bin/ls`, and given an argument of `/tmp/meterpreter`, both will run. You will see ls print the name of the file specified (because that's what ls does) and the program will also run within ls. ls will not terminate until the second program completes.

Compiling:
----------
`gcc -o badpthread.dylib -dynamiclib badpthread.c`

Example:
---------
`DYLD_INSERT_LIBRARIES=badpthread.dylib /path/to/host/binary /path/to/evil/parasite`

Notes:
------
* This won't work with any OS X binaries that use entitlements that disallow DYLD_* environmental variables.
* This won't work on any binaries in which euid != ruid
* This doesn't currently work on linux because you can't load ELF executables like dynamic libraries
    - [Possible workaround](https://grugq.github.io/docs/subversiveld.pdf)

Screen shot:
------------
![Screen shot of usage](https://i.imgur.com/ZR2kJaA.png)
