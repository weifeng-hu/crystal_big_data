        subroutine build_two_pdm( norb, ncore, nact, op, tp_act, tp )

        integer::norb, ncore, nact
        double precision::op( norb, norb )
        double precision::tp_act( nact, nact, nact, nact )
        double precision::tp( norb, norb, norb, norb )

        tp = 0.0d0

c       i,j,k,l are all core orbitals ---> Hartree-Fock type
c {
c       i = j = k = i
        do i = 1, ncore
           tp(i,i,i,i) = 2.0d0
        end do

c       i,j,j,i Culumb
        do i = 1, ncore
         do j = 1, ncore
          if( i .ne. j )then
           tp( i, j, j, i ) = 4.0d0
          end if
        end do; end do

c       i,j,i,j
        do i = 1, ncore
         do j = 1, ncore
          if( i .ne. j )then
           tp( i, j, i, j ) = -2.0d0
          end if
        end do; end do

c  }

c       i,j,k,l are all active orbitals
        do i = 1, nact
         do j = 1, nact
          do k = 1, nact
           do l = 1, nact
            tp( ncore + l, ncore + k, ncore + j, ncore + i) = 
     &                  tp_act( l, k, j, i )
        end do; end do; end do; end do

c       two are core, two are act
        do i = 1, ncore
         do j = ncore + 1, ncore + nact
          do k = 1, ncore
           do l = ncore + 1, ncore + nact
            if( i .eq. j )then
            tp( i, j, k, l ) = 2.0d0 * op(j,l)
            end if
        end do; end do; end do; end do

        do i = ncore + 1, ncore + nact
         do j = 1, ncore
          do k = ncore + 1, ncore + nact
           do l = 1, ncore
            if( j .eq. l )then
            tp( i, j, k, l ) = 2.0d0 * op(i,k)
            end if
        end do; end do; end do; end do

        do i = 1, ncore
         do j = ncore + 1, ncore + nact
          do k = ncore + 1, ncore + nact
           do l = 1, ncore
           if( i .eq. l )then
           tp( i, j, k, l ) = -1.0d0 * op(j,l)
           end if
        end do; end do; end do; end do

        do i = ncore + 1, ncore + nact
         do j = 1, ncore
          do k = 1, ncore
           do l = ncore + 1, ncore + nact
           if( j .eq. k )then
           tp( i, j, k, l ) = -1.0d0 * op( i, j, k, l )
           end if
        end do; end do; end do; end do

c       Note that virtual orbital gives zero density matrices since 
c       < vir | c+ c | vir > = 0


        end subroutine build_two_pdm
