        Subroutine Lanczos()

        USE BE
        double precision v_buf(4,4,4,4,4,4,100)
        double precision v_i(4,4,4,4,4,4)
        double precision v_j(4,4,4,4,4,4)
        double precision v_j_1(4,4,4,4,4,4)
        double precision hv(4,4,4,4,4,4)
        double precision v_x(4,4,4,4,4,4)
        double precision alpha(100),beta(100)
        double precision EngNow,EngFormer
        double precision ddot,dnrm2
        double precision a_j, b_j, overlap
        double precision num_a, num_b, s_z, s_sq
        double precision,allocatable::KrylovH(:,:)
        double precision,allocatable::EigLanc(:),WorkLanc(:)
        double precision val
        character*100 wavefile

        wavefile=''
        iseed=2008

        if( guess .eq. 1 )then 
         Do n=1,4; Do m=1,4;Do l=1,4;Do k=1,4;Do j=1,4; Do i=1,4
          hv(i,j,k,l,m,n)=Ran(iseed)
         End Do; End Do; End Do; End Do; End Do; End Do
        elseif( guess .eq. 2 ) then
         wavefile=directory(1:index(directory,' ')-1)//'/wave.1'
         open(file=wavefile(1:index(wavefile,' ')-1), unit=666)
          Do n=1,4; Do m=1,4;Do l=1,4;Do k=1,4;Do j=1,4; Do i=1,4
           read(666,*)val
           hv(i,j,k,l,m,n)=val
          End Do; End Do; End Do; End Do; End Do; End Do
         close(666)
        endif

        Do n=1,4; Do m=1,4; Do l=1,4; Do k=1,4; Do j=1,4; Do i=1,4
         IF((dabs(NumSubSpace(i,j,k,l,m,n)-nele).GT.1.0d-1).OR.
     &     dabs(SpinSubSpace(i,j,k,l,m,n)-n_sz).GT.1.0d-1)THEN
            hv(i,j,k,l,m,n)=0.0d0
         END IF
        End Do; End Do; End Do; End Do; End Do; End Do

        b_j=0.0d0
        b_j=dnrm2(4096, hv, 1)
        beta(1)=b_j
c        write(*,*)b_j

        Engformer=a_j; EngNow=0.0d0
        v_j_1=0.0d0;

        DO jj = 2, 100

         beta_j_1 = beta(jj-1)
         v_j = hv/beta_j_1
         v_buf(:,:,:,:,:,:,jj) = v_j(:,:,:,:,:,:)

         CALL Hv_Decomposition( v_j, hv )
c	CALL DGEMV('N',1024,1024,1.0d0,H,1024,v_j,1,0.0d0,Hv,1)

         Do n=1,4; Do m=1,4; Do l=1,4; Do k=1,4; DO j=1,4; Do i=1,4
          IF((dabs(NumSubSpace(i,j,k,l,m,n)-nele).GT.1.0d-1).OR.
     &        dabs(SpinSubSpace(i,j,k,l,m,n)-n_sz).GT.1.0d-1)THEN
               hv(i,j,k,l,m,n)=0.0d0
          END IF
         End Do; End Do; End Do; End Do; End Do; End Do

c r = r - v j-1 * b j-1
         if( jj .ge. 2 )then
          beta_j_1 = beta(jj-1);
          v_j_1(:,:,:,:,:,:) = v_buf(:,:,:,:,:,:,jj-1)
          call Daxpy( 4096, -1.0d0*beta_j_1, v_j_1, 1, hv,1 )
         endif

         a_j = ddot( 4096, v_j, 1, hv, 1 )
         alpha(jj-1) = a_j

         if( jj .ge. 2 )then
          Allocate(KrylovH(jj-1,jj-1))
          KrylovH=0.0d0
          Do i=1,jj-1
           KrylovH(i,i)=alpha(i)
          End Do
          Do i=2,jj-1
            KrylovH(i,i-1)=beta(i)
            KrylovH(i-1,i)=beta(i)
          END DO
c          write(*,*)krylovh
          Allocate(EigLanc(jj-1))
          Allocate(WorkLanc(jj-1))
          call eigtql2(jj-1,krylovh,eiglanc)
          EngNow=EigLanc(1)

          IF((Dabs(EngNow-Engformer).LT.1.0d-15).OR.(jj.GE.100))THEN
           if( jj .ge. 8)then
            iroot = 0
            do ii = 1, 10
             v_x=0.0d0
             do ij = 1, jj-1
              v_i = v_buf(:,:,:,:,:,:, ij+1 )
              call daxpy( 4096, 1.0d0*krylovh(ij, ii), v_i, 1, v_x ,1 )
             enddo
             call normalise( 4096, v_x )
             call Spin_properties( v_x, num_a, num_b, s_z, s_sq)
             if( (dabs( num_a + num_b - nele ) .le. 1.0e-1 ).and.
     &           (dabs( s_z - n_sz ) .le. 1.0e-1 ) .and. 
     &           (dabs( s_sq - n_s_sq ) .le. 1.0e-1 ) .and. 
     &           iroot .lt. 3)then
              iroot = iroot + 1
              write(*,15)"root[", iroot, "]  energy = ", 
     &                   eiglanc(ii) + core_energy,
     &                   " Na = ", num_a,
     &                   " Nb = ", num_b,
     &                   " Sz = ", s_z,
     &                   " S^2 = ", s_sq
c              write(wavefile,'(A,6A,A)')
c     &directory(1:index(directory,' ')-1), "/wave.", iroot
              wavefile=directory(1:index(directory,' ')-1)//"/wave."
     &//char(iroot+48)
              open(file=wavefile(1:index(wavefile,' ')-1),unit=100)
              Do n=1,4; Do m=1,4; Do l=1,4; Do k=1,4; DO j=1,4; Do i=1,4
               write(100,*)v_x(i,j,k,l,m,n)
              enddo; enddo; enddo; enddo; enddo; enddo
              close(100)
             endif
            enddo
           endif
15         format(A,I1,A,f17.12,x,A,f7.4,x,A,f7.4,x,A,f7.4,x,A,f7.4)
           EXIT
          ELSE
           Engformer=EngNow
           EngNow=0.0d0
          END IF
          Deallocate(KrylovH,EigLanc,WorkLanc)
         endif
 
         call daxpy(4096, -1.0d0*a_j, v_j, 1, hv, 1)
         do ij = 2, jj
          v_i = v_buf(:,:,:,:,:,:,ij)
          overlap = ddot( 4096, hv, 1, v_i, 1 )
          call daxpy(4096, -1.0d0 * overlap,  v_i, 1, hv, 1 )
         enddo
         
         b_j = dnrm2(4096, hv, 1)
         beta(jj) = b_j
c         write(*,*)b_j
         
        End Do

        End Subroutine Lanczos
