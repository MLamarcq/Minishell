==253662== Memcheck, a memory error detector
==253662== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==253662== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==253662== Command: ./minishell
==253662== Parent PID: 252344
==253662== 
==253685== Invalid read of size 4
==253685==    at 0x10E9B5: child_process (start_exec.c:187)
==253685==    by 0x10EC4E: start_exec (start_exec.c:237)
==253685==    by 0x1094DD: main (main.c:60)
==253685==  Address 0x4bd75e4 is 0 bytes after a block of size 4 alloc'd
==253685==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253685==    by 0x10E293: init_sep_type (start_exec.c:21)
==253685==    by 0x1094B2: main (main.c:56)
==253685== 
==253685== Invalid read of size 4
==253685==    at 0x10E9D8: child_process (start_exec.c:187)
==253685==    by 0x10EC4E: start_exec (start_exec.c:237)
==253685==    by 0x1094DD: main (main.c:60)
==253685==  Address 0x4bd75dc is 4 bytes before a block of size 4 alloc'd
==253685==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253685==    by 0x10E293: init_sep_type (start_exec.c:21)
==253685==    by 0x1094B2: main (main.c:56)
==253685== 
==253686== Invalid read of size 4
==253686==    at 0x10E9B5: child_process (start_exec.c:187)
==253686==    by 0x10EC4E: start_exec (start_exec.c:237)
==253686==    by 0x1094DD: main (main.c:60)
==253686==  Address 0x4bd82f4 is 0 bytes after a block of size 4 alloc'd
==253686==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253686==    by 0x10E293: init_sep_type (start_exec.c:21)
==253686==    by 0x1094B2: main (main.c:56)
==253686== 
==253686== Invalid read of size 4
==253686==    at 0x10E9D8: child_process (start_exec.c:187)
==253686==    by 0x10EC4E: start_exec (start_exec.c:237)
==253686==    by 0x1094DD: main (main.c:60)
==253686==  Address 0x4bd82ec is 4 bytes before a block of size 4 alloc'd
==253686==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253686==    by 0x10E293: init_sep_type (start_exec.c:21)
==253686==    by 0x1094B2: main (main.c:56)
==253686== 
==253687== Invalid read of size 4
==253687==    at 0x10E9B5: child_process (start_exec.c:187)
==253687==    by 0x10EC4E: start_exec (start_exec.c:237)
==253687==    by 0x1094DD: main (main.c:60)
==253687==  Address 0x4bd9004 is 0 bytes after a block of size 4 alloc'd
==253687==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253687==    by 0x10E293: init_sep_type (start_exec.c:21)
==253687==    by 0x1094B2: main (main.c:56)
==253687== 
==253687== Invalid read of size 4
==253687==    at 0x10E9D8: child_process (start_exec.c:187)
==253687==    by 0x10EC4E: start_exec (start_exec.c:237)
==253687==    by 0x1094DD: main (main.c:60)
==253687==  Address 0x4bd8ffc is 4 bytes before a block of size 4 alloc'd
==253687==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253687==    by 0x10E293: init_sep_type (start_exec.c:21)
==253687==    by 0x1094B2: main (main.c:56)
==253687== 
==253700== Conditional jump or move depends on uninitialised value(s)
==253700==    at 0x10E778: child_process (start_exec.c:159)
==253700==    by 0x10EC4E: start_exec (start_exec.c:237)
==253700==    by 0x1094DD: main (main.c:60)
==253700==  Uninitialised value was created by a heap allocation
==253700==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253700==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253700==    by 0x1094D1: main (main.c:59)
==253700== 
==253701== Invalid read of size 4
==253701==    at 0x10E9B5: child_process (start_exec.c:187)
==253701==    by 0x10EC4E: start_exec (start_exec.c:237)
==253701==    by 0x1094DD: main (main.c:60)
==253701==  Address 0x4bdbf28 is 0 bytes after a block of size 8 alloc'd
==253701==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253701==    by 0x10E293: init_sep_type (start_exec.c:21)
==253701==    by 0x1094B2: main (main.c:56)
==253701== 
==253701== Conditional jump or move depends on uninitialised value(s)
==253701==    at 0x10EAFF: child_process (start_exec.c:196)
==253701==    by 0x10EC4E: start_exec (start_exec.c:237)
==253701==    by 0x1094DD: main (main.c:60)
==253701==  Uninitialised value was created by a heap allocation
==253701==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253701==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253701==    by 0x1094D1: main (main.c:59)
==253701== 
==253662== Invalid write of size 1
==253662==    at 0x10CF97: write_without_qt_2 (remove_quote_2.c:22)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Address 0x4be2ccb is 0 bytes after a block of size 11 alloc'd
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x4847D18: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x493EBA0: __printf_buffer (vfprintf-process-arg.c:423)
==253662==    by 0x493F2A1: __vfprintf_internal (vfprintf-internal.c:1459)
==253662==    by 0x4934EAE: printf (printf.c:33)
==253662==    by 0x10D02D: write_without_qt_2 (remove_quote_2.c:36)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10DEBB: count_sep_2 (sep.c:95)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10DEBB: count_sep_2 (sep.c:95)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10DEBB: count_sep_2 (sep.c:95)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10DEBB: count_sep_2 (sep.c:95)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10DEBB: count_sep_2 (sep.c:95)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10D92C: count_word_for_alloc (prepare_exec.c:45)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10D92C: count_word_for_alloc (prepare_exec.c:45)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10D92C: count_word_for_alloc (prepare_exec.c:45)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10D92C: count_word_for_alloc (prepare_exec.c:45)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10D92C: count_word_for_alloc (prepare_exec.c:45)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10EE61: fill_little_tab (exec_utils.c:21)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10EE61: fill_little_tab (exec_utils.c:21)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10EE61: fill_little_tab (exec_utils.c:21)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10EE61: fill_little_tab (exec_utils.c:21)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10EE61: fill_little_tab (exec_utils.c:21)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x109CF1: ft_strdup (ft_strdup.c:20)
==253662==    by 0x10EE15: fill_little_tab (exec_utils.c:23)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x109D4F: ft_strdup (ft_strdup.c:24)
==253662==    by 0x10EE15: fill_little_tab (exec_utils.c:23)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10E2CA: init_sep_type (start_exec.c:27)
==253662==    by 0x1094B2: main (main.c:56)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10E2CA: init_sep_type (start_exec.c:27)
==253662==    by 0x1094B2: main (main.c:56)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10E2CA: init_sep_type (start_exec.c:27)
==253662==    by 0x1094B2: main (main.c:56)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10E2CA: init_sep_type (start_exec.c:27)
==253662==    by 0x1094B2: main (main.c:56)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10E2CA: init_sep_type (start_exec.c:27)
==253662==    by 0x1094B2: main (main.c:56)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253750== Conditional jump or move depends on uninitialised value(s)
==253750==    at 0x10E778: child_process (start_exec.c:159)
==253750==    by 0x10EC4E: start_exec (start_exec.c:237)
==253750==    by 0x1094DD: main (main.c:60)
==253750==  Uninitialised value was created by a heap allocation
==253750==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253750==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253750==    by 0x1094D1: main (main.c:59)
==253750== 
==253751== Conditional jump or move depends on uninitialised value(s)
==253751==    at 0x10E984: child_process (start_exec.c:178)
==253751==    by 0x10EC4E: start_exec (start_exec.c:237)
==253751==    by 0x1094DD: main (main.c:60)
==253751==  Uninitialised value was created by a heap allocation
==253751==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253751==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253751==    by 0x1094D1: main (main.c:59)
==253751== 
==253752== Invalid read of size 4
==253752==    at 0x10E9B5: child_process (start_exec.c:187)
==253752==    by 0x10EC4E: start_exec (start_exec.c:237)
==253752==    by 0x1094DD: main (main.c:60)
==253752==  Address 0x4be307c is 0 bytes after a block of size 12 alloc'd
==253752==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253752==    by 0x10E293: init_sep_type (start_exec.c:21)
==253752==    by 0x1094B2: main (main.c:56)
==253752== 
==253752== Conditional jump or move depends on uninitialised value(s)
==253752==    at 0x10EAFF: child_process (start_exec.c:196)
==253752==    by 0x10EC4E: start_exec (start_exec.c:237)
==253752==    by 0x1094DD: main (main.c:60)
==253752==  Uninitialised value was created by a heap allocation
==253752==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253752==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253752==    by 0x1094D1: main (main.c:59)
==253752== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10DD0A: check_first_is_sep (sep.c:35)
==253662==    by 0x10DE40: check_first_sep_error_2 (sep.c:78)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10DD0A: check_first_is_sep (sep.c:35)
==253662==    by 0x10DE40: check_first_sep_error_2 (sep.c:78)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10DD0A: check_first_is_sep (sep.c:35)
==253662==    by 0x10DE40: check_first_sep_error_2 (sep.c:78)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10DD0A: check_first_is_sep (sep.c:35)
==253662==    by 0x10DE40: check_first_sep_error_2 (sep.c:78)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10DD0A: check_first_is_sep (sep.c:35)
==253662==    by 0x10DE40: check_first_sep_error_2 (sep.c:78)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10DD93: check_first_is_sep_2 (sep.c:60)
==253662==    by 0x10DE58: check_first_sep_error_2 (sep.c:80)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10DD93: check_first_is_sep_2 (sep.c:60)
==253662==    by 0x10DE58: check_first_sep_error_2 (sep.c:80)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10DD93: check_first_is_sep_2 (sep.c:60)
==253662==    by 0x10DE58: check_first_sep_error_2 (sep.c:80)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10DD93: check_first_is_sep_2 (sep.c:60)
==253662==    by 0x10DE58: check_first_sep_error_2 (sep.c:80)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10DD93: check_first_is_sep_2 (sep.c:60)
==253662==    by 0x10DE58: check_first_sep_error_2 (sep.c:80)
==253662==    by 0x10DE8F: count_sep_2 (sep.c:90)
==253662==    by 0x10EEC8: init_big_tab (exec_utils.c:36)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10EF1E: init_big_tab (exec_utils.c:42)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10EF1E: init_big_tab (exec_utils.c:42)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10EF1E: init_big_tab (exec_utils.c:42)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10EF1E: init_big_tab (exec_utils.c:42)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10EF1E: init_big_tab (exec_utils.c:42)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DBF7: is_sep (sep.c:17)
==253662==    by 0x10D90A: count_word_for_alloc (prepare_exec.c:41)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC29: is_sep (sep.c:19)
==253662==    by 0x10D90A: count_word_for_alloc (prepare_exec.c:41)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC5B: is_sep (sep.c:21)
==253662==    by 0x10D90A: count_word_for_alloc (prepare_exec.c:41)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DC8A: is_sep (sep.c:23)
==253662==    by 0x10D90A: count_word_for_alloc (prepare_exec.c:41)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== Conditional jump or move depends on uninitialised value(s)
==253662==    at 0x10A1D8: ft_strlen (ft_strlen.c:22)
==253662==    by 0x10DCB9: is_sep (sep.c:25)
==253662==    by 0x10D90A: count_word_for_alloc (prepare_exec.c:41)
==253662==    by 0x10DB20: prepare_exec (prepare_exec.c:90)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662==  Uninitialised value was created by a heap allocation
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==254138== Invalid read of size 4
==254138==    at 0x10E9B5: child_process (start_exec.c:187)
==254138==    by 0x10EC4E: start_exec (start_exec.c:237)
==254138==    by 0x1094DD: main (main.c:60)
==254138==  Address 0x4be4864 is 0 bytes after a block of size 4 alloc'd
==254138==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==254138==    by 0x10E293: init_sep_type (start_exec.c:21)
==254138==    by 0x1094B2: main (main.c:56)
==254138== 
==254138== Invalid read of size 4
==254138==    at 0x10E9D8: child_process (start_exec.c:187)
==254138==    by 0x10EC4E: start_exec (start_exec.c:237)
==254138==    by 0x1094DD: main (main.c:60)
==254138==  Address 0x4be485c is 4 bytes before a block of size 4 alloc'd
==254138==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==254138==    by 0x10E293: init_sep_type (start_exec.c:21)
==254138==    by 0x1094B2: main (main.c:56)
==254138== 
==254156== Invalid read of size 4
==254156==    at 0x10E9B5: child_process (start_exec.c:187)
==254156==    by 0x10EC4E: start_exec (start_exec.c:237)
==254156==    by 0x1094DD: main (main.c:60)
==254156==  Address 0x4be6a24 is 0 bytes after a block of size 4 alloc'd
==254156==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==254156==    by 0x10E293: init_sep_type (start_exec.c:21)
==254156==    by 0x1094B2: main (main.c:56)
==254156== 
==254156== Invalid read of size 4
==254156==    at 0x10E9D8: child_process (start_exec.c:187)
==254156==    by 0x10EC4E: start_exec (start_exec.c:237)
==254156==    by 0x1094DD: main (main.c:60)
==254156==  Address 0x4be6a1c is 4 bytes before a block of size 4 alloc'd
==254156==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==254156==    by 0x10E293: init_sep_type (start_exec.c:21)
==254156==    by 0x1094B2: main (main.c:56)
==254156== 
==253662== 
==253662== FILE DESCRIPTORS: 25 open (3 std) at exit.
==253662== Open file descriptor 103: /opt/visual-studio-code/v8_context_snapshot.bin
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 56: /opt/visual-studio-code/resources/app/node_modules.asar
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 51: /usr/share/fonts/liberation/LiberationSerif-Regular.ttf
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 50: /dev/shm/.org.chromium.Chromium.lWZLcO (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 49: /dev/shm/.org.chromium.Chromium.7lEowk (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 48: /opt/visual-studio-code/resources/app/node_modules.asar
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 47: /dev/shm/.org.chromium.Chromium.Mcx9Rk (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 46: /dev/shm/.org.chromium.Chromium.78tZUk (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 45: /dev/shm/.org.chromium.Chromium.zhnjHa (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 44: /dev/shm/.org.chromium.Chromium.LMZ90v (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 43: /dev/shm/.org.chromium.Chromium.GPRUFY (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 42: /dev/shm/.org.chromium.Chromium.1mCGaS (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 41: /dev/shm/.org.chromium.Chromium.lgPaMB (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open AF_UNIX socket 40: <unknown>
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 39: /dev/shm/.org.chromium.Chromium.0eQwYR (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 38: /dev/shm/.org.chromium.Chromium.VVBZXF (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 33: /tmp/.org.chromium.Chromium.iP0QKI (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 32: /proc/205588/status
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 31: /proc/205588/statm
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 30: /dev/shm/.org.chromium.Chromium.596ZJs (deleted)
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 21: /opt/visual-studio-code/v8_context_snapshot.bin
==253662==    <inherited from parent>
==253662== 
==253662== Open file descriptor 3: /home/gael/mini_gael/minishell/filename.erl
==253662==    <inherited from parent>
==253662== 
==253662== 
==253662== HEAP SUMMARY:
==253662==     in use at exit: 224,624 bytes in 475 blocks
==253662==   total heap usage: 3,631 allocs, 3,156 frees, 413,880 bytes allocated
==253662== 
==253662== 33 bytes in 3 blocks are indirectly lost in loss record 20 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10CF79: write_without_qt_2 (remove_quote_2.c:21)
==253662==    by 0x10D11A: remove_quote_2 (remove_quote_2.c:68)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 36 bytes in 3 blocks are indirectly lost in loss record 21 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10E534: init_tab_fd (start_exec.c:119)
==253662==    by 0x1094D1: main (main.c:59)
==253662== 
==253662== 39 bytes in 3 blocks are definitely lost in loss record 22 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x109CFE: ft_strdup (ft_strdup.c:20)
==253662==    by 0x10D0EF: remove_quote_2 (remove_quote_2.c:66)
==253662==    by 0x10C6C5: build_result_output (parsing.c:85)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 40 bytes in 7 blocks are definitely lost in loss record 23 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10E293: init_sep_type (start_exec.c:21)
==253662==    by 0x1094B2: main (main.c:56)
==253662== 
==253662== 40 bytes in 7 blocks are definitely lost in loss record 24 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10EB84: start_exec (start_exec.c:222)
==253662==    by 0x1094DD: main (main.c:60)
==253662== 
==253662== 44 bytes in 15 blocks are indirectly lost in loss record 25 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x109DC2: ft_strdup_len (ft_strdup.c:45)
==253662==    by 0x1098E7: ft_lstnew_word (ft_lstnew_word.c:23)
==253662==    by 0x10C530: put_word_in_minish (parsing.c:48)
==253662==    by 0x10C67D: build_result_output (parsing.c:80)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 56 bytes in 2 blocks are indirectly lost in loss record 29 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10E4C9: init_tab_fd (start_exec.c:113)
==253662==    by 0x1094D1: main (main.c:59)
==253662== 
==253662== 59 bytes in 15 blocks are indirectly lost in loss record 31 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x109CFE: ft_strdup (ft_strdup.c:20)
==253662==    by 0x10EE15: fill_little_tab (exec_utils.c:23)
==253662==    by 0x10DB71: prepare_exec (prepare_exec.c:94)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 200 bytes in 10 blocks are indirectly lost in loss record 40 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10DB5D: prepare_exec (prepare_exec.c:92)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 264 bytes in 11 blocks are indirectly lost in loss record 42 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x1098B6: ft_lstnew_word (ft_lstnew_word.c:19)
==253662==    by 0x10C530: put_word_in_minish (parsing.c:48)
==253662==    by 0x10C67D: build_result_output (parsing.c:80)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 372 (280 direct, 92 indirect) bytes in 7 blocks are definitely lost in loss record 43 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10DF6D: init_exec (which_sep.c:17)
==253662==    by 0x1094BE: main (main.c:57)
==253662== 
==253662== 395 (136 direct, 259 indirect) bytes in 7 blocks are definitely lost in loss record 44 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x10EEEC: init_big_tab (exec_utils.c:38)
==253662==    by 0x10DAEE: prepare_exec (prepare_exec.c:85)
==253662==    by 0x10C6D1: build_result_output (parsing.c:86)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 509 (168 direct, 341 indirect) bytes in 7 blocks are definitely lost in loss record 45 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x1098B6: ft_lstnew_word (ft_lstnew_word.c:19)
==253662==    by 0x10C530: put_word_in_minish (parsing.c:48)
==253662==    by 0x10C67D: build_result_output (parsing.c:80)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== 3,055 bytes in 124 blocks are definitely lost in loss record 64 of 95
==253662==    at 0x4841888: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==253662==    by 0x109E6A: ft_strjoin (ft_strjoin.c:23)
==253662==    by 0x10D474: ft_find_cmd (ft_find_path.c:29)
==253662==    by 0x10D556: ft_find_path (ft_find_path.c:52)
==253662==    by 0x10D5DB: ft_find_env (ft_find_path.c:64)
==253662==    by 0x10C795: type_utils_1 (set_type.c:19)
==253662==    by 0x10CB5F: set_type (set_type.c:97)
==253662==    by 0x10C6AD: build_result_output (parsing.c:83)
==253662==    by 0x10C742: ft_parsing (parsing.c:97)
==253662==    by 0x1094A1: main (main.c:54)
==253662== 
==253662== LEAK SUMMARY:
==253662==    definitely lost: 3,758 bytes in 162 blocks
==253662==    indirectly lost: 692 bytes in 59 blocks
==253662==      possibly lost: 0 bytes in 0 blocks
==253662==    still reachable: 0 bytes in 0 blocks
==253662==         suppressed: 220,174 bytes in 254 blocks
==253662== 
==253662== For lists of detected and suppressed errors, rerun with: -s
==253662== ERROR SUMMARY: 109 errors from 51 contexts (suppressed: 0 from 0)
