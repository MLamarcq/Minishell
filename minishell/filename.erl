==72074== Memcheck, a memory error detector
==72074== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==72074== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
==72074== Command: ./minishell
==72074== Parent PID: 64410
==72074== 

valgrind:  Fatal error at startup: a function redirection
valgrind:  which is mandatory for this platform-tool combination
valgrind:  cannot be set up.  Details of the redirection are:
valgrind:  
valgrind:  A must-be-redirected function
valgrind:  whose name matches the pattern:      strlen
valgrind:  in an object with soname matching:   ld-linux-x86-64.so.2
valgrind:  was not found whilst processing
valgrind:  symbols from the object with soname: ld-linux-x86-64.so.2
valgrind:  
valgrind:  Possible fixes: (1, short term): install glibc's debuginfo
valgrind:  package on this machine.  (2, longer term): ask the packagers
valgrind:  for your Linux distribution to please in future ship a non-
valgrind:  stripped ld.so (or whatever the dynamic linker .so is called)
valgrind:  that exports the above-named function using the standard
valgrind:  calling conventions for this platform.  The package you need
valgrind:  to install for fix (1) is called
valgrind:  
valgrind:    On Debian, Ubuntu:                 libc6-dbg
valgrind:    On SuSE, openSuSE, Fedora, RHEL:   glibc-debuginfo
valgrind:  
valgrind:  Note that if you are debugging a 32 bit process on a
valgrind:  64 bit system, you will need a corresponding 32 bit debuginfo
valgrind:  package (e.g. libc6-dbg:i386).
valgrind:  
valgrind:  Cannot continue -- exiting now.  Sorry.

