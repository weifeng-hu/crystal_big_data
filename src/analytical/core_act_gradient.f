       subroutine core_act_gradient( norb, ncore, nact, Q, TEI, TEI_a,
     &                               U, gradient )

       integer::norb,ncore,nact
       double precision::Q(norb,norb)
       double precision::TEI(norb,norb,norb,norb)
       double precision::TEI_a(norb,norb,norb,norb)
       double precision::U(norb,norb)
       double precision::gradient

       integer m

       gradient = 0.0d0

c Coulumb part (ij|kk)
       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
         do k = 1, ncore
         gradient = gradient + q(i,j) * tei_a(i,j,k,k)
       end do; end do; end do;

       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
         do k = 1, ncore
          do m = 1, norb
       gradient = gradient + q(i,j) * 
     & ( u(m,i) * tei(m,j,k,k) + u(m,j) * tei(i,m,k,k) +
     &   u(m,k) * tei(i,j,m,k) + u(m,k) * tei(i,j,k,m) )
       end do; end do; end do; end do

c Exchange part (ik|jk)
       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
         do k = 1, ncore
         gradient = gradient + q(i,j) * tei_a(i,k,j,k)
       end do; end do; end do;

       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
         do k = 1, ncore
          do m = 1, norb
       gradient = gradient + q(i,j) *
     & ( u(m,i) * tei(m,k,j,k) + u(m,k) * tei(i,m,j,k) +
     &   u(m,j) * tei(i,k,m,k) + u(m,k) * tei(i,k,j,m) )
       end do; end do; end do; end do

       end subroutine core_act_gradient
