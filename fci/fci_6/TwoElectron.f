	Subroutine TwoElectron(isum,jsum,ksum,lsum)

	USE BE

	INTEGER::isum,jsum,ksum,lsum
	write(*,*)isum,jsum,ksum,lsum
	CALL DirectProduct(CreUp,O1,isum)
	CALL DirectProduct(CreUp,O2,jsum)
	CALL DirectProduct(AnnUp,O3,ksum)
	CALL DirectProduct(AnnUp,O4,lsum)
	CALL DGEMM('N','N',4096,4096,4096,U(isum,jsum,ksum,lsum),
     &			O1,4096,O2,4096,0.0d0,TE1,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  O3,4096,O4,4096,0.0d0,TE2,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE1,4096,TE2,4096,1.0d0,H,4096)

        CALL DirectProduct(CreUp,O1,isum)
        CALL DirectProduct(CreDw,O2,jsum)
        CALL DirectProduct(AnnDw,O3,ksum)
        CALL DirectProduct(AnnUp,O4,lsum)
        CALL DGEMM('N','N',4096,4096,4096,U(isum,jsum,ksum,lsum),
     &                  O1,4096,O2,4096,0.0d0,TE1,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE1,4096,O3,4096,0.0d0,TE2,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE2,4096,O4,4096,1.0d0,H,4096)

        CALL DirectProduct(CreDw,O1,isum)
        CALL DirectProduct(CreUp,O2,jsum)
        CALL DirectProduct(AnnUp,O3,ksum)
        CALL DirectProduct(AnnDw,O4,lsum)
        CALL DGEMM('N','N',4096,4096,4096,U(isum,jsum,ksum,lsum),
     &                  O1,4096,O2,4096,0.0d0,TE1,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE1,4096,O3,4096,0.0d0,TE2,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE2,4096,O4,4096,1.0d0,H,4096)

        CALL DirectProduct(CreDw,O1,isum)
        CALL DirectProduct(CreDw,O2,jsum)
        CALL DirectProduct(AnnDw,O3,ksum)
        CALL DirectProduct(AnnDw,O4,lsum)
        CALL DGEMM('N','N',4096,4096,4096,U(isum,jsum,ksum,lsum),
     &                  O1,4096,O2,4096,0.0d0,TE1,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE1,4096,O3,4096,0.0d0,TE2,4096)
        CALL DGEMM('N','N',4096,4096,4096,1.0d0,
     &                  TE2,4096,O4,4096,1.0d0,H,4096)

	End Subroutine TwoElectron
