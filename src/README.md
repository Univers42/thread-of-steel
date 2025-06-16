# need to repair that after the project is done 

dlesieur@dlesieur42:~/Documents/projects-42/fdf/thread-of-steel$ valgrind --track-origins=yes --show-leak-kinds=all ./fdf
==587533== Memcheck, a memory error detector
==587533== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==587533== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==587533== Command: ./fdf
==587533== 
==587533== Syscall param writev(vector[0]) points to uninitialised byte(s)
==587533==    at 0x4AF4864: writev (writev.c:26)
==587533==    by 0x4BEBACA: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==587533==    by 0x4BEBC4E: ??? (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==587533==    by 0x4BECD7E: xcb_writev (in /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
==587533==    by 0x48CF0B8: _XSend (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==587533==    by 0x48D4148: _XReadEvents (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==587533==    by 0x48D452B: XWindowEvent (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==587533==    by 0x10AEC5: mlx_int_wait_first_expose (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533==    by 0x10ABE5: mlx_new_window (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533==    by 0x10A6DF: main (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533==  Address 0x4c48fbc is 28 bytes inside a block of size 16,384 alloc'd
==587533==    at 0x484D953: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==587533==    by 0x48BE42D: XOpenDisplay (in /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
==587533==    by 0x10A996: mlx_init (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533==    by 0x10A6A8: main (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533==  Uninitialised value was created by a stack allocation
==587533==    at 0x10ADD0: mlx_int_anti_resize_win (in /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/fdf)
==587533== 
==587533== 
==587533== HEAP SUMMARY:
==587533==     in use at exit: 0 bytes in 0 blocks
==587533==   total heap usage: 271 allocs, 271 frees, 110,748 bytes allocated
==587533== 
==587533== All heap blocks were freed -- no leaks are possible
==587533== 
==587533== For lists of detected and suppressed errors, rerun with: -s
==587533== ERROR SUMMARY: 2 errors from 1 contexts (suppressed: 0 from 0)
dlesieur@dlesieur42:~/Documents/projects-42/fdf/thread-of-steel$ 
