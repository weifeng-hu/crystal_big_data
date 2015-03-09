		
      subroutine EIGTQL(mdimx, ndimx, dzxmat, deigen, dworkx)
      implicit double precision (a-h,o-z)
      parameter(dtorle = 1.0d-12, mitera = 50)
      dimension dzxmat(mdimx, mdimx), deigen( mdimx), dworkx( mdimx)
      call TRED2(mdimx, ndimx, dzxmat, deigen, dworkx)
      do 10 jdimi=2,ndimx
  10  dworkx(jdimi-1)=dworkx(jdimi)
      dworkx(ndimx)=0.0D0

      dfactf=0.0D0
      dfactb=0.0D0
      do 20 jdiml=1,ndimx
         nitera=0
         dfacth=dtorle*(dabs(deigen(jdiml))+dabs(dworkx(jdiml)))
         jdiml1=jdiml+1
         if (dfactb-dfacth) 30,40,40
  30     dfactb=dfacth
  40     do 50 jdimm=jdiml,ndimx
            if (dabs(dworkx(jdimm))-dfactb) 60,60,50
  50     continue
  60     if (jdimm-jdiml) 70,80,70
  70     if (nitera-mitera) 90,100,90
  90     nitera = nitera + 1
         dfactp=(deigen(jdiml1)-deigen(jdiml))/(2*dworkx(jdiml))
         dfactr=dsqrt(dfactp*dfactp+1.0d+0)
         if (dfactp) 110,111,111
  110    dfacth = deigen(jdiml)-dworkx(jdiml)/(dfactp-dfactr)
         goto 130
  111    dfacth = deigen(jdiml)-dworkx(jdiml)/(dfactp+dfactr)
  130    do 140 jdimi = jdiml, ndimx
  140    deigen(jdimi)=deigen(jdimi)-dfacth
         dfactf = dfactf + dfacth
         dfactp =deigen(jdimm)
         dfactc =1.0D0
         dfacts =0.0D0
         jdimm1 = jdimm - 1
         if (jdimm1-jdiml) 270,280,280
  280    do 120 jdimx=jdiml, jdimm1
            jdimi = jdiml + jdimm1 - jdimx
            jdimi1 = jdimi + 1
            dfactg = dfactc * dworkx(jdimi)
            dfacth = dfactc * dfactp
            if (dabs(dfactp)-dabs(dworkx(jdimi))) 160,170,170

  170       dfactc = dworkx(jdimi)/dfactp
            dfactr = dsqrt(dfactc*dfactc + 1.0D0)
            dworkx(jdimi1)=dfacts*dfactp*dfactr
            dfacts = dfactc / dfactr
            dfactc = 1.0d+0 / dfactr
            goto 180

  160       dfactc = dfactp/dworkx(jdimi)
            dfactr = dsqrt(dfactc*dfactc+1.0d+0)
            dworkx(jdimi1)=dfacts*dworkx(jdimi)*dfactr
            dfacts = 1.0d+0 / dfactr
            dfactc = dfactc / dfactr

  180       dfactp = dfactc * deigen(jdimi) - dfacts * dfactg
            deigen(jdimi1)=dfacth
     &                    +dfacts*(dfactc*dfactg+dfacts*deigen(jdimi))
            do 190 jdimk=1,ndimx
               dfacth=dzxmat(jdimk, jdimi1)
               dzxmat(jdimk, jdimi1)=dfacts*dzxmat(jdimk, jdimi)
     &                              +dfactc*dfacth
               dzxmat(jdimk, jdimi )=dfactc*dzxmat(jdimk, jdimi)
     &                     -dfacts*dfacth
  190       continue
  120    continue
  270    dworkx(jdiml)=dfacts*dfactp
         deigen(jdiml)=dfactc*dfactp
         if (dabs(dworkx(jdiml))-dfactb) 80,80,70
   80    deigen(jdiml)=deigen(jdiml)+dfactf
   20 continue

      do 112 jdimi=1,ndimx
         jdimi1=jdimi+1
         jdimk =jdimi
         dfactp=deigen(jdimi)
         if (ndimx-jdimi) 230,230,300
  300    do 210 jdimj=jdimi1,ndimx
            if (deigen(jdimj)-dfactp) 220,210,210
  220    jdimk = jdimj
         dfactp=deigen(jdimj)
  210    continue
  230    if (jdimk - jdimi) 240,112,240
  240    deigen(jdimk)=deigen(jdimi)
         deigen(jdimi)=dfactp
         do 260 jdimj=1,ndimx
            dfactp=dzxmat(jdimj, jdimi)
            dzxmat(jdimj, jdimi)=dzxmat(jdimj, jdimk)
            dzxmat(jdimj, jdimk)=dfactp
  260    continue
  112 continue
      return
  100 write(*,9001)
 9001 format(' fail in EIGTQL ')
      stop
      end

      subroutine TRED2(mdimx, ndimx, dzxmat, deigen, dworkx)
      implicit double precision (a-h,o-z)
      parameter( dtorle = 1.0d-30)

       dimension dzxmat(mdimx,mdimx), deigen(mdimx), dworkx(mdimx)
      do 20 jdimx=2,ndimx
         jdimi=ndimx+2-jdimx
         jdimi1=jdimi-1
         jdimi2=jdimi-2
         jdiml =jdimi2
         dfactf = dzxmat(jdimi, jdimi1)
         dfactg =0.0D0
         if (jdiml) 30,30,40
  40     do 50 jdimk = 1, jdiml
  50     dfactg = dfactg + dzxmat(jdimi, jdimk)*dzxmat(jdimi, jdimk)
  30     dfacth = dfactg + dfactf * dfactf
         if (dfactg-dtorle) 60,60,70
  60     dworkx(jdimi)=dfactf
         dfacth=0.0D0
         goto 180
  70     jdiml = jdiml + 1
         if (dfactf) 80,90,90
  90     dworkx(jdimi)=-dsqrt(dfacth)
         dfactg=dworkx(jdimi)
         goto 100
  80     dworkx(jdimi)=dsqrt(dfacth)
         dfactg = dworkx(jdimi)
 100     dfacth = dfacth - dfactf*dfactg
         dzxmat(jdimi, jdimi1)=dfactf-dfactg
         dfactf=0.0D0
         do 110 jdimj = 1, jdiml
            dzxmat(jdimj, jdimi)=dzxmat(jdimi, jdimj)/dfacth
            dfactg=0.0D0
            do 201 jdimk = 1, jdimj
  201       dfactg = dfactg + dzxmat(jdimj,jdimk)*dzxmat(jdimi,jdimk)
            jdimj1 = jdimj + 1
            if (jdimj1 - jdiml) 130,130,140
  130       do 120 jdimk = jdimj1, jdiml
  120       dfactg = dfactg + dzxmat(jdimk,jdimj)*dzxmat(jdimi,jdimk)
  140       dworkx(jdimj)=dfactg / dfacth
            dfactf = dfactf + dfactg * dzxmat(jdimj, jdimi)
  110    continue
         dhh = dfactf / ( dfacth + dfacth)
         do 160 jdimj = 1, jdiml
            dfactf = dzxmat(jdimi, jdimj)
            dworkx(jdimj) = dworkx(jdimj)- dhh * dfactf
            dfactg = dworkx(jdimj)
            do 170 jdimk = 1, jdimj
  170       dzxmat(jdimj, jdimk)=dzxmat(jdimj, jdimk)
     &          -dfactf*dworkx(jdimk)-dfactg*dzxmat(jdimi, jdimk)
  160    continue
  180    deigen(jdimi)=dfacth
  20  continue

      deigen(1)=0.0D0
      dworkx(1)=0.0D0
      do 190 jdimi=1,ndimx
         jdiml=jdimi-1
         if (deigen(jdimi)) 202,210,202
  202    if (jdiml) 210,210,220
  220    do 230 jdimj=1,jdiml
            dfactg=0.0D0
            DO 240 jdimk = 1, jdiml
  240       dfactg=dfactg+dzxmat(jdimi,jdimk)*dzxmat(jdimk, jdimj)
            do 250 jdimk = 1, jdiml
  250       dzxmat(jdimk, jdimj)=dzxmat(jdimk, jdimj)
     &                          -dfactg*dzxmat(jdimk, jdimi)
  230    continue
  210    deigen(jdimi)=dzxmat(jdimi, jdimi)
         dzxmat(jdimi, jdimi)=1.0D0
         if (jdiml) 260,260,270
  270    do 280 jdimj = 1, jdiml
            dzxmat(jdimi, jdimj)=0.0D0
  280       dzxmat(jdimj, jdimi)=0.0D0
  260    continue
  190 continue
      return
      end

