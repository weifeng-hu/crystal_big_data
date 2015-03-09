       Subroutine spin_properties(wave, num_a, num_b, s_z, s_sq)

       use be
       double precision::wave(4,4,4,4,4,4)
       double precision:: num_a, num_b, s_z, s_sq
       double precision u1(4,4,4,4,4,4)
       double precision u2(4,4,4,4,4,4)
       double precision u3(4,4,4,4,4,4)
       double precision u4(4,4,4,4,4,4)
       double precision overlap
       double precision ddot, dnrm2
c S+ = sum_p C_+p, alpha C_p, beta
c S- = sum_p C_+p, beta  C_p, alpha
c Sz = 1/2 sum_p ( C_+p alpha C_p alpha - C_+ p beta C_p beta )
c S^2 = S+ S- + Sz ( Sz - 1 )
c      Sz
       U4 = 0.0d0
       Do isum = 1, 6
        U1 = 0.0d0
        call MatrixVector(isum, 0.5d0, AnnUp, wave, U1)
        call MatrixVector(isum, 1.0d0, CreUp, U1, U4)

        U1 = 0.0d0
        call MatrixVector(isum, 0.5d0, AnnDw, wave, U1)
        call MatrixVector(isum, -1.0d0, CreDw, U1, U4)
       Enddo
       s_z = ddot( 4096, wave,1,  U4, 1 )

       U4 = 0.0d0
c      Sz (Sz - 1) .w 
c      (Sz * Sz - Sz) .w
       Do jsum = 1, 6
        U2 = 0.0d0
        Do isum = 1, 6
         U1 = 0.0d0
         call MatrixVector( isum, 0.5e0, AnnUp, wave, U1 )
         call MatrixVector( isum, 1.0d0, CreUp, U1, U2)

         U1 = 0.0d0
         call MatrixVector( isum, 0.5d0, AnnDw, wave, U1)
         call MatrixVector( isum, -1.0d0, CreDw, U1, U2 )
        EndDo
        U3 = 0.0d0
        call MatrixVector( jsum, 0.5d0, AnnUp, U2, U3 )
        call MatrixVector( jsum, 1.0d0, CreUp, U3, U4)

        U3 = 0.0d0
        call MatrixVector( jsum, 0.5d0, AnnDw, U2, U3)
        call MatrixVector( jsum, -1.0d0, CreDw, U3, U4 )
       EndDo

c      S+ S- . w
       Do jsum = 1, 6
        U2=0.0d0
         Do isum = 1, 6
          U1 = 0.0d0
          call MatrixVector( isum, 1.0d0, AnnUp, wave, U1 )
          call MatrixVector( isum, 1.0d0, CreDw, U1, U2 )
         Enddo
        U3 = 0.0d0
        call MatrixVector( jsum, 1.0d0, AnnDw, U2, U3 )
        call MatrixVector( jsum, 1.0d0, CreUp, U3, U4 )
       EndDo
       s_sq = ddot( 4096, wave, 1, U4, 1 )

c      N.w
       U2 = 0.0d0
       Do isum = 1,6
        U1 = 0.0d0
        call MatrixVector(isum, 1.0d0, AnnUp, wave, U1)
        call MatrixVector(isum, 1.0d0, CreUp, U1, U2)
       EndDo
       num_a = ddot( 4096, wave, 1, U2, 1 )

       U2 = 0.0d0
       Do isum = 1,6
        U1 = 0.0d0
        call MatrixVector(isum, 1.0d0, AnnDw, wave, U1)
        call MatrixVector(isum, 1.0d0, CreDw, U1, U2)
       Enddo
       num_b = ddot( 4096, wave, 1, U2, 1 )

       end subroutine spin_properties
