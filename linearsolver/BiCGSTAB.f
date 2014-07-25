       SUBROUTINE BICGSTAB(dim1, dim2, A, U, B)

       integer::dim1, dim2
       double precision::A(dim1, dim2)
       double precision::B(dim2)
       double precision::U(dim2)

       double precision,allocatable::r(:,:)
       double precision,allocatable::rou(:)
       double precision,allocatable::omega(:)
       double precision alpha,beta
       double precision,allocatable::v(:,:),p(:,:)
       double precision,allocatable::xx(:,:)

       double precision ddot, dnrm2

       double precision norm_now, norm_last
       character trans
       integer n, incx, incy
       double precision numer,denor,res, aa
       double precision,allocatable::x(:),y(:)
       double precision,allocatable::s(:),t(:)


       allocate(r(dim2,100))
       allocate(rou(100),omega(100))
       allocate(p(dim2,100),v(dim2,100))
       allocate(xx(dim2,100))

       allocate(x(dim2),y(dim2))
       allocate(s(dim2),t(dim2))

       iseed = 2012
       do i = 1, dim2
          u(i) = ran(iseed)
       end do

       xx(:,1) = u(:)
!	write(*,*)u
       incx = 1; incy = 1
       m = dim1; n = dim2
       lda = dim1
       trans = 'N'
       incx = 1; incy = 1
       x(:) = xx(:,1)
       call dgemv(trans, m, n, 1.0d0, a, lda, x, incx, 0.0d0, y, incy)
       r(:,1) = B(:) - y(:)

       rou(1) = 1.0d0
       alpha  = 1.0d0
       omega(1) = 1.0d0

       v(:,1) = 0.0d0
       p(:,1) = 0.0d0

c start iteration
       norm_last = 0.0d0
       i = 2
       do while( .true. )

       n = dim2; incx = 1; incy = 1
       x(:) = r(:,1)
       y(:) = r(:,i-1)
       res = ddot( n, x, incx, y, incy )
       rou(i) = res

       beta = ( rou(i)/rou(i-1) ) * ( alpha/omega(i-1) )
       p(:,i) = r(:,i-1) + beta * ( p(:,i-1) - omega(i-1) * v(:,i-1) )

       trans = 'N'; m = dim1; n = dim2; 
       lda = dim1; incx = 1;
       x(:) = p(:,i);
       incy = 1
       call dgemv(trans, m , n, 1.0d0, a, lda, x, incx, 0.0d0, y, incy)
       v(:,i) = y(:)


       n = dim2; incx = 1; incy = 1
       x(:) = r(:,1) ; y(:) = v(:,i)
       denor = ddot( n, x, incx, y, incy)
       alpha = rou(i) / denor

       s(:)  = r(:,i-1) - alpha * v(:,i)

       trans = 'N'
       m = dim1; n = dim2;
       lda = dim1; 
       x(:) = s(:)
       incx = 1; incy = 1
       call dgemv( trans, m, n, 1.0d0, a, lda, x, incx, 0.0d0, y, incy)
       t(:) = y(:)

       x(:) = t(:); y(:) = s(:)
       numer = ddot(n, x, incx, y, incy )
       denor = dnrm2(n, x, incx)
       omega(i) = numer/denor

       xx(:,i) = xx(:,i-1) + alpha * p(:,i) + omega(i) * s(:)

       x(:) = xx(:,i)
!	write(*,*)x
       res = dnrm2( n, x, incx )
       norm_now = res;
       if( (dabs(norm_now - norm_last).le.1.0d-10) 
     &       .or. (i.ge.100) )then
            u(:) = xx(:,i)
!       write(*,*)u
            exit
       else
         norm_last = norm_now
       end if

       r(:,i) = s(:) - omega(i) * t(:)

       i = i + 1

       end do

       deallocate(x,y)
       deallocate(s,t)
       deallocate(r, rou, omega)
       deallocate(p,v)
       deallocate(xx)

       END SUBROUTINE BICGSTAB
