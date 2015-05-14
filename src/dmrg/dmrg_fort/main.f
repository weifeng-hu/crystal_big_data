      program main

       integer :: i;
       integer argc
       character(len = 32) :: argv(3)

       argc = iargc()
#ifdef _GNU
       if( argc .ne. 2 )then
        write(*,*)' error: incorrect number of arguments ';
        call print_help_note();
        stop
       end if

       do i = 0, 2
        call getarg( i, argv(i+1) );
        write(*,*) argv(i+1)
       end do
#endif

#ifdef _INTEL
       if( command_argument_count .ne. 2 )then
        write(*,*)' error: incorrect number of arguments ';
        call print_help_note();
        stop
       endif

       do i = 0, 2
        call get_command_argument( i, argv(i+1) )
       end do
#endif

       call dmrg( argc, argv )

      end program main

c     to print help note, or other information, can be expanded in future
      subroutine print_help_note()

       write(*,*) ' usage: dmrg.fortran [configure file] [output file]'

      end subroutine print_help_note
