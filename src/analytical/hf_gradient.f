      subroutine hf_gradient(nbas,norb,nocc, ha_ao,eria_ao, sa, eps,
     &                       gradient)

      integer::nbas,norb
      integer::nocc
      double precision::ha_ao(nbas,nbas)
      double precision::eria_ao(nbas,nbas,nbas,nbas)
      double precision::c(nbas,norb)
      double precision::sa(nbas,nbas)
      double precision::eps(norb)
      double precision::gradient

      integer mu, yu, rou, sigma

      gradient = 0.0d0

      do i = 1, nocc
       do mu = 1, nbas
         do yu = 1, nbas
          gradient = gradient + 2.0d0 * c(mu,i) * c(yu,i) * ha_ao(mu,yu)
      end do; end do; end do

      do i = 1, nocc
       do j = 1, nocc
        do mu = 1, nbas
         do yu = 1, nbas
          do rou = 1, nbas
           do sigma = 1, nbas
       gradient = gradient 
     & +2.0d0*
     &  c(mu,i)*c(yu,i)*c(rou,j)*c(sigma,j)*eria_ao(mu,yu,rou,sigma)
     & -1.0d0*
     &  c(mu,i)*c(yu,j)*c(rou,i)*c(sigma,j)*eria_ao(mu,yu,rou,sigma)

      end do; end do; end do; end do; end do; end do

      do i = 1, nocc
       do mu = 1, nbas
        do yu = 1, nbas
        gradient = gradient - 
     &      2.0d0*c(mu,i)*c(yu,i)*eps(i)*sa(mu,yu)
      end do; end do; end do

      end subroutine hf_gradient
