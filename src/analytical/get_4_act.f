       subroutine get_4_act( norb, ncore, nact, t, newt )

       integer::norb,ncore,nact
       double precision::t(norb, norb, norb, norb)
       double precision::newt(nact, nact, nact, nact)

       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
          do k = ncore + 1, ncore + nact
            do l = ncore + 1, ncore + nact
             newt(l,k,j,i) = t(l,k,j,i)
       end do; end do; end do; end do

       end subroutine get_4_act
