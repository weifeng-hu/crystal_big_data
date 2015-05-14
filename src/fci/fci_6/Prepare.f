        Subroutine Prepare()
        
        USE BE

        double precision intv
        double precision tempu(6,6,6,6)
        character(len=100) fcidump
        CreUp=0.0d0
        CreDw=0.0d0
        AnnUp=0.0d0
        AnnDw=0.0d0
        
        CreUp(2,1)=1.0d0; CreUp(4,3)=1.0d0
        CreDw(3,1)=1.0d0; CreDw(4,2)=-1.0d0
        AnnUp(1,2)=1.0d0; AnnUp(3,4)=1.0d0
        AnnDw(1,3)=1.0d0; AnnDw(2,4)=-1.0d0

        NumSpace=0.0d0; SpinSpace=0.0d0
        NumSpace(1)=0.0d0; NumSpace(2)=1.0d0; NumSpace(3)=1.0d0
        NumSpace(4)=2.0d0
        
        SpinSpace(1)=0.0d0; SpinSpace(2)=0.5d0; SpinSpace(3)=-0.5d0
        SpinSpace(4)=0.0d0

        Do n=1,4
        Do m=1,4
            Do l=1,4
               Do k=1,4
                   Do j=1,4
                      Do i=1,4
        NumSubSpace(i,j,k,l,m,n)=NumSpace(i)+
     &                         NumSpace(j)+
     &                         NumSpace(k)+
     &                         NumSpace(l)+
     &                         NumSpace(m)+
     &                         NumSpace(n)
                End Do
              End Do
            End Do
          End Do
        End Do
        End Do

        Do n=1,4
        Do m=1,4
            Do l=1,4
               Do k=1,4
                   Do j=1,4
                      Do i=1,4
        SpinSubSpace(i,j,k,l,m,n)=SpinSpace(i)+
     &                         SpinSpace(j)+
     &                         SpinSpace(k)+
     &                         SpinSpace(l)+
     &                         SpinSpace(m)+
     &                         SpinSpace(n)
                End Do
              End Do
            End Do
          End Do
        End Do
        End DO


        Unit1=0.0d0
        Unit1(1,1)=1.0d0
        Unit1(2,2)=1.0d0
        Unit1(3,3)=1.0d0
        Unit1(4,4)=1.0d0
        
        Unit2=0.0d0
        Do i=1,16
        Unit2(i,i)=1.0d0
        End Do
        
        Unit3=0.0d0
        Do i=1,64
        Unit3(i,i)=1.0d0
        End Do
        
        Unit4=0.0d0
        Do i=1,256
        Unit4(i,i)=1.0d0
        End Do

        Unit5=0.0e0
        Do i=1,1024
        Unit5(i,i)=1.0d0
        End Do
        
        P1=0.0d0
        P1(1,1)=1.0d0; P1(2,2)=-1.0d0; P1(3,3)=-1.0d0; P1(4,4)=1.0d0
        
        P2=0.0d0
        Do k=1,4; Do l=1,4
         Do i=1,4; Do j=1,4
        P2((k-1)*4+i,(l-1)*4+j)=P1(i,j)*P1(k,l)
         End Do; End Do
        End Do; End Do

        P3=0.0d0
        Do k=1,4; Do l=1,4
         Do i=1,16; Do j=1,16
        P3((k-1)*16+i,(l-1)*16+j)=P2(i,j)*P1(k,l)
         End Do; End Do
        End Do; End Do
        
        P4=0.0d0
        Do k=1,4; Do l=1,4
                 Do i=1,64; Do j=1,64
        P4((k-1)*64+i,(l-1)*64+j)=P3(i,j)*P1(k,l)
                 End Do; End Do
        End Do; End Do

        P5=0.0d0
        Do k=1,4; Do l=1,4
                 Do i=1,256; Do j=1,256
        P4((k-1)*256+i,(l-1)*256+j)=P4(i,j)*P1(k,l)
                 End Do; End Do
        End Do; End Do

        open(file='input.txt', unit=666, access='sequential')
        read(666,'(A)')directory
        read(666,'(A)')molecule
        read(666,'(F)')nele
        read(666,'(F)')n_sz
        read(666,'(F)')n_s_sq
        read(666,'(I)')guess
        close(666)

c        write(*,*)directory
c        write(*,*)molecule
c        write(*,*)nele
c        write(*,*)n_sz
c        write(*,*)n_s_sq
c        write(*,*)guess
c        stop

        tempu=0.0d0
c        fcidump=directory//"/"//molecule//".qcdmrg.FCIDUMP"
c        write(fcidump,'(A,A,A,A)')
c     &directory, "/", molecule,".qcdmrg.FCIDUMP"
        fcidump = directory(1:index(directory,' ')-1)//
     &molecule(1:index(molecule,' ')-1)//".qcdmrg.FCIDUMP"
c        write(*,*)fcidump
c        stop
        open(file=fcidump(1:index(fcidump, ' ')-1), 
     &unit=666, access='sequential')
        read(666,*)
        read(666,*)
        read(666,*)
        read(666,*)
        do while( .true. )
         read(666,*)intv, i, j, k, l
c         write(*,*) intv, i,j,k,l
         if( k .ne. 0 .and. l .ne. 0 )then
          tempu(i,j,k,l) = intv
          tempu(j,i,k,l) = intv
          tempu(i,j,l,k) = intv
          tempu(j,i,l,k) = intv
         elseif( k .eq. 0 .and. l .eq. 0 )then
          if( i .eq. 0 .and. j .eq. 0 )then
           core_energy = intv
           exit
          else
           t(i,j) = intv
           t(j,i) = intv
          endif
         endif
        enddo
        close(666)

        do i = 1,6; do j = 1,6; do k = 1,6; do l=1,6
         u(i,k,l,j)=tempu(i,j,k,l)
        enddo; enddo; enddo; enddo
c        write(*,*)"integral done"
c	OPEN(FILE='SEINTEGRALS',UNIT=666,FORM='UNFORMATTED',
c     &		ACCESS='SEQUENTIAL')
c	DO i=1,5; Do j=1,5
c		READ(666)T(i,j)
c	END DO; END DO
c	CLOSE(666)

c	OPEN(FILE='DEINTEGRALS',UNIT=999,FORM='UNFORMATTED',
c     &		ACCESS='SEQUENTIAL')
c	DO i=1,5; Do j=1,5; Do k=1,5; Do l=1,5
c	READ(999)U(i,k,l,j)
c	End Do; End Do; End Do; End Do
c	CLOSE(999)
        U=0.5d0*U

        End Subroutine Prepare
