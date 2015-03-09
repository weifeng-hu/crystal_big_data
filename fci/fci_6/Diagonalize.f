       Subroutine Diagonalize()
       
       USE BE
       double precision overlap
       double precision doot
       integer n1, n2, m1,m2

       goto 15

       do n1=1,4; do m1=1,4; do l1=1,4; do k1=1,4; do j1=1,4; do i1=1,4
       do n2=1,4; do m2=1,4; do l2=1,4; do k2=1,4; do j2=1,4; do i2=1,4
       ix=(n1-1)*1024 +(m1-1)*256+(l1-1)*64+(k1-1)*16+(j1-1)*4+i1
       iy=(n2-1)*1024 +(m2-1)*256+(l2-1)*64+(k2-1)*16+(j2-1)*4+i2
        IF((dabs(NumSubSpace(i1,j1,k1,l1,m1,n1)-4.0d0).GT.1.0d-2).OR.
     &     (dabs(SpinSubSpace(i1,j1,k1,l1,m1,n1)-0.0d0).GT.1.0d-2)
     &     .OR.
     &     (dabs(NumSubSpace(i2,j2,k2,l2,m2,n2)-4.0d0).GT.1.0d-2).OR.
     &     (dabs(SpinSubSpace(i2,j2,k2,l2,m2,n2)-0.0d0).GT.1.0d-2) )THEN
         H(ix,iy)=0.0d0
         H(iy,ix)=0.0d0
        ENDIF
       enddo; enddo; enddo; enddo; enddo; enddo
       enddo; enddo; enddo; enddo; enddo; enddo

       EigVc=H
c       CALL EIGTQL(4096,4096,EigVc,EigVl,work)
c       write(4096,*)EigVl
c       stop
       call eigtql2(4096, eigvc, eigvl )
       do i = 1, 4096
        eigvl(i) = eigvl(i) + core_energy
       enddo
       write(4096,*)EigVl(1:20)

       do i=1,6
        open(unit=100+i)
         do j=1,4096
          write(100+i,*) eigvc(j,i)
         enddo
        close(100+i)
       enddo

15       CALL Lanczos()
       
       End Subroutine Diagonalize
