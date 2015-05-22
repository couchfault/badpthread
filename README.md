# Badpthread
Attempting to hide stuff in other stuff using pthread stuff

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
* This should work on linux (with `LD_PRELOAD` but I haven't tested it)

Screen shot:
------------
[Screen shot of usage](https://i.imgur.com/ZR2kJaA.png)
