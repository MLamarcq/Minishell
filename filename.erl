==211275== Memcheck, a memory error detector
==211275== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==211275== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==211275== Command: ./minishell
==211275== Parent PID: 205646
==211275== 
==211287== Invalid read of size 4
==211287==    at 0x10E910: child_process (start_exec.c:194)
==211287==    by 0x10EB5E: start_exec (start_exec.c:241)
==211287==    by 0x1094CD: main (main.c:60)
==211287==  Address 0x4bd8b18 is 0 bytes after a block of size 8 alloc'd
==211287==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211287==    by 0x10E283: init_sep_type (start_exec.c:21)
==211287==    by 0x1094A2: main (main.c:56)
==211287== 
==211275== 
==211275== FILE DESCRIPTORS: 27 open (3 std) at exit.
==211275== Open file descriptor 5:
==211275==    at 0x49DC1AD: pipe (pipe.c:29)
==211275==    by 0x10E571: init_tab_fd (start_exec.c:121)
==211275==    by 0x1094C1: main (main.c:59)
==211275== 
==211275== Open file descriptor 4:
==211275==    at 0x49DC1AD: pipe (pipe.c:29)
==211275==    by 0x10E571: init_tab_fd (start_exec.c:121)
==211275==    by 0x1094C1: main (main.c:59)
==211275== 
==211275== Open file descriptor 103: /opt/visual-studio-code/v8_context_snapshot.bin
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 56: /opt/visual-studio-code/resources/app/node_modules.asar
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 51: /usr/share/fonts/liberation/LiberationSerif-Regular.ttf
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 50: /dev/shm/.org.chromium.Chromium.lWZLcO (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 49: /dev/shm/.org.chromium.Chromium.7lEowk (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 48: /opt/visual-studio-code/resources/app/node_modules.asar
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 47: /dev/shm/.org.chromium.Chromium.Mcx9Rk (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 46: /dev/shm/.org.chromium.Chromium.78tZUk (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 45: /dev/shm/.org.chromium.Chromium.zhnjHa (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 44: /dev/shm/.org.chromium.Chromium.LMZ90v (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 43: /dev/shm/.org.chromium.Chromium.GPRUFY (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 42: /dev/shm/.org.chromium.Chromium.1mCGaS (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 41: /dev/shm/.org.chromium.Chromium.lgPaMB (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open AF_UNIX socket 40: <unknown>
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 39: /dev/shm/.org.chromium.Chromium.0eQwYR (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 38: /dev/shm/.org.chromium.Chromium.VVBZXF (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 33: /tmp/.org.chromium.Chromium.iP0QKI (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 32: /proc/205588/status
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 31: /proc/205588/statm
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 30: /dev/shm/.org.chromium.Chromium.596ZJs (deleted)
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 21: /opt/visual-studio-code/v8_context_snapshot.bin
==211275==    <inherited from parent>
==211275== 
==211275== Open file descriptor 3: /home/gael/mini_gael/minishell/filename.erl
==211275==    <inherited from parent>
==211275== 
==211275== 
==211275== HEAP SUMMARY:
==211275==     in use at exit: 220,441 bytes in 265 blocks
==211275==   total heap usage: 3,015 allocs, 2,750 frees, 401,085 bytes allocated
==211275== 
==211275== 6 bytes in 2 blocks are indirectly lost in loss record 1 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x109CEE: ft_strdup (ft_strdup.c:20)
==211275==    by 0x10EC76: fill_little_tab (exec_utils.c:23)
==211275==    by 0x10DB61: prepare_exec (prepare_exec.c:94)
==211275==    by 0x10C6C1: build_result_output (parsing.c:86)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 8 bytes in 3 blocks are indirectly lost in loss record 5 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x109DB2: ft_strdup_len (ft_strdup.c:45)
==211275==    by 0x1098D7: ft_lstnew_word (ft_lstnew_word.c:23)
==211275==    by 0x10C520: put_word_in_minish (parsing.c:48)
==211275==    by 0x10C66D: build_result_output (parsing.c:80)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 8 bytes in 1 blocks are definitely lost in loss record 6 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10E283: init_sep_type (start_exec.c:21)
==211275==    by 0x1094A2: main (main.c:56)
==211275== 
==211275== 8 bytes in 1 blocks are definitely lost in loss record 7 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10EA36: start_exec (start_exec.c:226)
==211275==    by 0x1094CD: main (main.c:60)
==211275== 
==211275== 12 bytes in 1 blocks are indirectly lost in loss record 14 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10E524: init_tab_fd (start_exec.c:119)
==211275==    by 0x1094C1: main (main.c:59)
==211275== 
==211275== 24 bytes in 1 blocks are indirectly lost in loss record 23 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10E4B9: init_tab_fd (start_exec.c:113)
==211275==    by 0x1094C1: main (main.c:59)
==211275== 
==211275== 32 bytes in 2 blocks are indirectly lost in loss record 25 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10DB4D: prepare_exec (prepare_exec.c:92)
==211275==    by 0x10C6C1: build_result_output (parsing.c:86)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 48 bytes in 2 blocks are indirectly lost in loss record 28 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x1098A6: ft_lstnew_word (ft_lstnew_word.c:19)
==211275==    by 0x10C520: put_word_in_minish (parsing.c:48)
==211275==    by 0x10C66D: build_result_output (parsing.c:80)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 62 (24 direct, 38 indirect) bytes in 1 blocks are definitely lost in loss record 29 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10ED4D: init_big_tab (exec_utils.c:38)
==211275==    by 0x10DADE: prepare_exec (prepare_exec.c:85)
==211275==    by 0x10C6C1: build_result_output (parsing.c:86)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 76 (40 direct, 36 indirect) bytes in 1 blocks are definitely lost in loss record 31 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x10DF5D: init_exec (which_sep.c:17)
==211275==    by 0x1094AE: main (main.c:57)
==211275== 
==211275== 80 (24 direct, 56 indirect) bytes in 1 blocks are definitely lost in loss record 33 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x1098A6: ft_lstnew_word (ft_lstnew_word.c:19)
==211275==    by 0x10C520: put_word_in_minish (parsing.c:48)
==211275==    by 0x10C66D: build_result_output (parsing.c:80)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== 343 bytes in 16 blocks are definitely lost in loss record 39 of 88
==211275==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==211275==    by 0x109E5A: ft_strjoin (ft_strjoin.c:23)
==211275==    by 0x10D464: ft_find_cmd (ft_find_path.c:29)
==211275==    by 0x10D546: ft_find_path (ft_find_path.c:52)
==211275==    by 0x10D5CB: ft_find_env (ft_find_path.c:64)
==211275==    by 0x10C785: type_utils_1 (set_type.c:19)
==211275==    by 0x10CB4F: set_type (set_type.c:97)
==211275==    by 0x10C69D: build_result_output (parsing.c:83)
==211275==    by 0x10C732: ft_parsing (parsing.c:97)
==211275==    by 0x109491: main (main.c:54)
==211275== 
==211275== LEAK SUMMARY:
==211275==    definitely lost: 447 bytes in 21 blocks
==211275==    indirectly lost: 130 bytes in 11 blocks
==211275==      possibly lost: 0 bytes in 0 blocks
==211275==    still reachable: 0 bytes in 0 blocks
==211275==         suppressed: 219,864 bytes in 233 blocks
==211275== 
==211275== For lists of detected and suppressed errors, rerun with: -s
==211275== ERROR SUMMARY: 6 errors from 6 contexts (suppressed: 0 from 0)
