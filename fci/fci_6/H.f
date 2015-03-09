        Subroutine H()
        
        USE BE
        
        Do i=1,6; Do j=1,6
        CALL OneElectron(i,j)
        END Do; END DO
        
        DO i=1,6; DO j=1,6; DO k=1,6; DO l=1,6
        CALL TwoElectron(i,j,k,l)
        END DO; END DO; END DO; END DO

        call printH()
10      End Subroutine H

        subroutine printH()
        USE BE
        open(unit=4095)
        do i=1,4096; do j=1,4096
         write(4095,*)H(i,j)
        enddo; enddo
        close(unit=4095)
        end
