       subroutine get_2_act( norb, ncore, nact )

       integer::norb, ncore, nact
       double precision::t(norb, norb)
       double precision::newt(nact, nact)

       do i = ncore + 1, ncore + nact
        do j = ncore + 1, ncore + nact
         newt(j,i) = t(j,i)
       end do; end do

       end subroutine get_2_act
