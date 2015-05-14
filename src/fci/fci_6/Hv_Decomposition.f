        Subroutine Hv_Decomposition( v_j, hv )
        
        USE BE
        double precision::v_j(4,4,4,4,4,4)
        double precision::Hv(4,4,4,4,4,4)        
        double precision U1(4,4,4,4,4,4),U2(4,4,4,4,4,4)
        Hv=0.0d0

!Single Electron
      Do isum=1,6; Do jsum=1,6
        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          T(isum,jsum),
     &                          AnnUp,v_j,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreUp,U1,Hv)

        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          T(isum,jsum),
     &                          AnnDw,v_j,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreDw,U1,Hv)
      End Do;End Do

!Double Electron
      Do isum=1,6
            Do jsum=1,6
               Do ksum=1,6
                    Do lsum=1,6
        U1=0.0d0
                CALL MatrixVector(lsum,
     &                          U(isum,jsum,ksum,lsum),
     &                          AnnUp,v_j,U1)
        U2=0.0d0
                CALL MatrixVector(ksum,
     &                          1.0d0,
     &                          AnnUp,U1,U2)
        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          1.0d0,
     &                          CreUp,U2,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreUp,U1,Hv)

        U1=0.0d0
                CALL MatrixVector(lsum,
     &                          U(isum,jsum,ksum,lsum),
     &                          AnnDw,v_j,U1)
        U2=0.0d0
                CALL MatrixVector(ksum,
     &                          1.0d0,
     &                          AnnUp,U1,U2)
        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          1.0d0,
     &                          CreUp,U2,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreDw,U1,Hv)

        U1=0.0d0
                CALL MatrixVector(lsum,
     &                          U(isum,jsum,ksum,lsum),
     &                          AnnUp,v_j,U1)
        U2=0.0d0
                CALL MatrixVector(ksum,
     &                          1.0d0,
     &                          AnnDw,U1,U2)
        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          1.0d0,
     &                          CreDw,U2,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreUp,U1,Hv)

        U1=0.0d0
                CALL MatrixVector(lsum,
     &                          U(isum,jsum,ksum,lsum),
     &                          AnnDw,v_j,U1)
        U2=0.0d0
                CALL MatrixVector(ksum,
     &                          1.0d0,
     &                          AnnDw,U1,U2)
        U1=0.0d0
                CALL MatrixVector(jsum,
     &                          1.0d0,
     &                          CreDw,U2,U1)
                CALL MatrixVector(isum,
     &                          1.0d0,
     &                          CreDw,U1,Hv)
                                End Do
                         End Do
                End Do
        End Do

        End Subroutine Hv_Decomposition
