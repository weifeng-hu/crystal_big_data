      subroutine dmrg_main()

       if( runtype == wilson_warmup )then
        call wilson_rg()
       endif

      end subroutine dmrg_main
