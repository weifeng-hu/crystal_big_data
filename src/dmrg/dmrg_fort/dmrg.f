      subroutine dmrg_input( config_file )

       character( len = 32 ) config_file

      end subroutine dmrg_input

      subroutine dmrg( argc, argv )

       integer :: argc
       character( len = 32 ) :: argv( argc )
       character( len = 32 ) config_file

       config_file = argv(3)

       call dmrg_input( config_file )
       call dmrg_main( runtype )

      end subroutine dmrg
