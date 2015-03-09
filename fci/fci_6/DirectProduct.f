       Subroutine DirectProduct(Matrix,ExpdMatrix,isum)
       
       USE BE
       
       INTEGER::isum
       DOUBLE PRECISION::Matrix(4,4)
       DOUBLE PRECISION::ExpdMatrix(4096,4096)
       
       double precision,allocatable::Mid(:,:)
       
       Select Case(isum)
       Case(1)
       Do k=1,1024; Do l=1,1024
        Do i=1,4; Do j=1,4
         ExpdMatrix((k-1)*4+i,(l-1)*4+j)=Matrix(i,j)*Unit5(k,l)
        End Do; End Do
       End Do; End Do
       
       Case(2)
       Allocate(Mid(16,16))
       Do k=1,4; Do l=1,4
        Do i=1,4; Do j=1,4
         Mid((k-1)*4+i,(l-1)*4+j)=P1(i,j)*Matrix(k,l)
        End Do; End Do
       End Do; End Do
       
       Do k=1,256; Do l=1,256
        Do i=1,16; Do j=1,16
         ExpdMatrix((k-1)*16+i,(l-1)*16+j)=Mid(i,j)*Unit4(k,l)
        End Do; End Do
       End Do; End Do
       Deallocate(Mid)
       
       Case(3)
       Allocate(Mid(64,64))
       Do k=1,4; Do l=1,4
        Do i=1,16; Do j=1,16
         Mid((k-1)*16+i,(l-1)*16+j)=P2(i,j)*Matrix(k,l)
        End Do; End Do
       End Do; End Do
       
       Do k=1,64; Do l=1,64
        Do i=1,64; Do j=1,64
         ExpdMatrix((k-1)*64+i,(l-1)*64+j)=Mid(i,j)*Unit3(k,l)
        End Do; End Do
       End Do; End Do
       Deallocate(Mid)
       
       Case(4)
       Allocate(Mid(256,256))
       Do k=1,4; Do l=1,4
        Do i=1,64; Do j=1,64
         Mid((k-1)*64+i,(l-1)*64+j)=P3(i,j)*Matrix(k,l)
        End Do; End Do
       End Do; End Do
       
       Do k=1,16; Do l=1,16
        Do i=1,256; Do j=1,256
         ExpdMatrix((k-1)*256+i,(l-1)*256+j)=Mid(i,j)*Unit2(k,l)
        End Do; End Do
       End Do; End Do
       Deallocate(Mid)
       
       Case(5)
       Allocate(Mid(1024, 1024))
       Do k=1,4; Do l=1,4
        Do i=1,256; Do j=1,256
         Mid((k-1)*256+i,(l-1)*256+j)=P4(i,j)*Matrix(k,l)
        End Do; End Do
       End Do; End Do

       Do k=1,4; Do l=1,4
        Do i=1,1024; Do j=1,1024
         ExpdMatrix((k-1)*1024+i,(l-1)*1024+j)=Mid(i,j)*Unit1(k,l)
        End Do; End Do
       End Do; End Do
       
       Case(6)
       Do k=1,4; Do l=1,4
        Do i=1,1024; Do j=1,1024
         ExpdMatrix((k-1)*1024+i,(l-1)*1024+j)=P5(i,j)*Matrix(k,l)
        End Do; End Do
       End Do; End Do

       End Select
       
       END Subroutine DirectProduct
