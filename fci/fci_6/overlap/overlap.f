       program main

       double precision psixp(4096)
       double precision psixm(4096)
       double precision psiy(4096)
       double precision psid(4096)
       double precision a
       double precision overlapp, overlapm
       double precision overlap_test
       double precision ddot, dnrm2
       double precision nac

       a=0.005d0

       open(unit=120)
       do i = 1, 4096
        read(120,*)psiy(i)
       enddo
       close(120)
       overlap_test = dnrm2(4096, psiy, 1)
       write(*,*)" overlap_test = ", overlap_test
c       stop

       open(unit=121)
       do i = 1, 4096
        read(121,*)psixp(i)
       enddo
       close(121)

       open(unit=119)
       do i = 1, 4096
        read(119,*)psixm(i)
       enddo
       close(119)

       overlap_test=ddot(4096, psixm, 1, psixp, 1 )
       write(*,*) " overlap_test + - = ", overlap_test
       if( overlap_test .lt. 0.0d0 )then
        psixm = -1.0d0 * psixm
       endif

       overlapp = ddot(4096, psiy, 1, psixp, 1)
       overlapm = ddot(4096, psiy, 1, psixm, 1)
       nac = (overlapp-overlapm)/(2.0d0*a)

       write(*,*) "nacp = ", nac, " overlaps + - ", overlapp, overlapm

       end
