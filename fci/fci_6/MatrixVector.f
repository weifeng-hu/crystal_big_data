       Subroutine MatrixVector(isum,
     &                   a,
     &                   Matrix,Vector,NewVector)

       INTEGER::isum
       DOUBLE PRECISION::a
       DOUBLE PRECISION::Matrix(4,4)
       DOUBLE PRECISION::Vector(4,4,4,4,4,4)
       DOUBLE PRECISION::NewVector(4,4,4,4,4,4)
       
       double precision b,c,d,e,f,g
       
       Select Case(isum)
       Case(1)
       Do n=1,4
         Do m=1,4
           Do l=1,4
             Do k=1,4
               Do j=1,4
                 Do ii=1,4; Do ij=1,4
                  NewVector(ii,j,k,l,m,n)=NewVector(ii,j,k,l,m,n)+a*
     &                            Matrix(ii,ij)*Vector(ij,j,k,l,m,n)
                 End DO; End Do
                End Do
              End Do
            End Do
          End Do
        End DO

        Case(2)
        Do n=1,4
         Do m=1,4
          Do l=1,4
            Do k=1,4
              Do ji=1,4; Do jj=1,4
                Do i=1,4
          IF((i.EQ.2).OR.(i.EQ.3))THEN
            b=-1.0d0
          ELSE
            b=1.0d0
          END IF
          NewVector(i,ji,k,l,m,n)=NewVector(i,ji,k,l,m,n)+b*a*
     &                  Matrix(ji,jj)*Vector(i,jj,k,l,m,n)
                End DO
              End Do; End Do
            End Do
          End Do
        End Do
       End Do

       Case(3)
        Do n=1,4
        Do m=1,4
          Do l=1,4
            Do ki=1,4; Do kj=1,4
              Do j=1,4
        IF((j.EQ.2).OR.(j.EQ.3))THEN
                c=-1.0d0
        ELSE
                c=1.0d0
        END IF
                Do i=1,4
                 IF((i.EQ.2).OR.(i.EQ.3))THEN
                  b=-1.0d0
                 ELSE
                  b=1.0d0
                 END IF
        NewVector(i,j,ki,l,m,n)=NewVector(i,j,ki,l,m,n)+c*b*a*
     &                  Matrix(ki,kj)*Vector(i,j,kj,l,m,n)
                End DO
              End Do
            End Do; End Do
          End Do
        End Do
        End Do

        Case(4)
        Do n=1,4
        Do m=1,4
          Do li=1,4; Do lj=1,4
            Do k=1,4
              IF((k.EQ.2).OR.(k.EQ.3))THEN
                d=-1.0d0
              ELSE
                d=1.0d0
              END IF
              Do j=1,4
               IF((j.EQ.2).OR.(j.EQ.3))THEN
                c=-1.0d0
               ELSE
                c=1.0d0
               END IF
                Do i=1,4
                 IF((i.EQ.2).OR.(i.EQ.3))THEN
                  b=-1.0d0
                 ELSE
                  b=1.0d0
                 END IF
               NewVector(i,j,k,li,m,n)=NewVector(i,j,k,li,m,n)+d*c*b*a*
     &                  Matrix(li,lj)*Vector(i,j,k,lj,m,n)
                End DO
              End Do
            End Do
          End Do; End Do
        End Do
        End Do

        Case(5)
        Do n=1,4
        Do mi=1,4; Do mj=1,4
          Do l=1,4
           IF((l.EQ.2).OR.(l.EQ.3))THEN
            e=-1.0d0
           ELSE
            e=1.0d0
           END IF
            Do k=1,4
             IF((k.EQ.2).OR.(k.EQ.3))THEN
              d=-1.0d0
             ELSE
              d=1.0d0
             END IF
              Do j=1,4
               IF((j.EQ.2).OR.(j.EQ.3))THEN
                 c=-1.0d0
               ELSE
                c=1.0d0
               END IF
                Do i=1,4
                 IF((i.EQ.2).OR.(i.EQ.3))THEN
                   b=-1.0d0
                 ELSE
                   b=1.0d0
                 END IF
              NewVector(i,j,k,l,mi,n)=NewVector(i,j,k,l,mi,n)+e*d*c*b*a*
     &                  Matrix(mi,mj)*Vector(i,j,k,l,mj,n)
                End DO
              End Do
            End Do
          End Do
        End Do; End Do
        End Do

        Case(6)
        Do ni=1,4; Do nj=1,4
         Do m=1,4
          IF((m.EQ.2).OR.(m.EQ.3))THEN
                 f = -1.0e0;
          ELSE
                 f = 1.0d0;
          ENDIF
           do l = 1,4
          IF((l.EQ.2).OR.(l.EQ.3))THEN
                  e=-1.0d0
          ELSE
                  e=1.0d0
          END IF
              Do k=1,4
          IF((k.EQ.2).OR.(k.EQ.3))THEN
                  d=-1.0d0
          ELSE
                  d=1.0d0
          END IF
                Do j=1,4
          IF((j.EQ.2).OR.(j.EQ.3))THEN
                  c=-1.0d0
          ELSE
                  c=1.0d0
          END IF
                  Do i=1,4
          IF((i.EQ.2).OR.(i.EQ.3))THEN
                  b=-1.0d0
          ELSE
                  b=1.0d0
          END IF
          NewVector(i,j,k,l,m,ni)=NewVector(i,j,k,l,m,ni)+f*e*d*c*b*a*
     &                  Matrix(ni,nj)*Vector(i,j,k,l,m,nj)

         enddo; enddo; enddo; enddo; enddo; enddo
        enddo; 

        End Select

        End Subroutine MatrixVector
