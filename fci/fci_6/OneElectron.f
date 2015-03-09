	Subroutine OneElectron(isum,jsum)

	USE BE

	INTEGER::isum,jsum
	write(*,*)isum, jsum
	CALL DirectProduct(CreUp,O1,isum)
	CALL DirectProduct(AnnUp,O2,jsum)
	CALL DGEMM('N','N',4096,4096,4096,T(isum,jsum),
     &			O1,4096,O2,4096,1.0d0,H,4096)

	CALL DirectProduct(CreDw,O1,isum)
	CALL DirectProduct(AnnDw,O2,jsum)
	CALL DGEMM('N','N',4096,4096,4096,T(isum,jsum),
     &			O1,4096,O2,4096,1.0d0,H,4096)

	End Subroutine OneElectron
