      subroutine renormalise()

       call 

      end subroutine renormalise()

      subroutine build_operators()

       do iop_type = 1, n_op_type

         call build_op( iop_type )

       end do

      end subroutine build_operators

      subroutine block_and_decimate()

       call build_operators()
       call renormalise()

      end subroutine block_and_decimate

      subroutine wilson_fwd()

       do block_iter = block_iter_start, block_iter_end

        call get_quanta_info()

        call block_and_decimate()

       enddo

      end subroutine wilson_fwd

      subroutine wilson_rg()

       if( forward == 1 ) then
        call wilson_fwd()
       else
c        call wilson_bwd()
       endif

      end subroutine wilson_rg
