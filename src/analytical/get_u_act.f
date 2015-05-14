       subroutine get_u_act(norb, ncore, nact, u, u_act )

       integer::norb,ncore,nact
       double precision::u(norb, norb)
       double precision::u_act(norb, nact)

       do i = ncore + 1, ncore + nact
         do j = 1, norb
         u_act(j,i) = u(j,i)
       end do; end do

       end subroutine get_u_act
