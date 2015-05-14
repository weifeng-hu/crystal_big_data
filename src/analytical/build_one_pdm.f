       subroutine build_one_pdm( norb, ncore, nacc, op_act, op )

       integer::norb,ncore,nacc
       double precision::op_act(ncore, ncore)
       double precision::op(norb, norb)

       op = 0.0d0

       do i = 1, ncore
        do j = 1, ncore
          op(i,j) = 2.0d0;
       end do; end do

       do i = 1, nact
        do j = 1, nact
         op( ncore + i, ncore + j ) = op_act( i, j )
       end do; end do

       end subroutine build_one_pdm
