       subroutine get_h_core(norb, ncore, h, h_core)

       integer::norb,ncore
       double precision::h(norb,norb)
       double precision::h_core(ncore,ncore)

       do i = 1, ncore
         do j = 1, ncore
          h_core(i,j) = h(i,j)
       end do; end do

       end subroutine get_ha_ao_core
