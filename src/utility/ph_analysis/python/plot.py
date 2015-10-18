import subprocess

printlevel = 4
execution = 1

orca_plot = "/home/wh288/Development/orca_lno/x86_exe/orca_plot";

num_pz = 10;
polyenes = [ "c10h12" ];

for i in range(0, len(polyenes) ):

 gbw_file = polyenes[i] + '.sih.gbw';

 pz_file = "orca.2pz_orbs";
 fpz = open( pz_file, "rt" );

 for iorb in range( 0, num_pz ):
  xpz = fpz.readline(); xpz = xpz.rstrip('\n');
  # write orca_plot config
  plot_infile = polyenes[i] + ".plot.inp";
  f = open( plot_infile, 'wt' );
  f.write('1			#PG.PlotType\n');
  f.write('7			#PG.Format\n');
  f.write( xpz + ' 0			#PG.MO PG.OP\n');
  f.write('0			#PG.State\n');
  f.write( plot_infile ); f.write( '		#PG.infile\n');
  f.write( polyenes[i] ); f.write( '.cube.'); f.write( str(iorb+1) ); f.write( '		#PG.outfile\n' );
  f.write( '200			#PG.ncont\n');
  f.write( '1			#PG.icont\n');
  f.write( '0			#PG.Skeleton\n');
  f.write( '0			#PG.Atoms\n');
  f.write( '0			#PG.usecol\n');
  f.write( '120 120 120		#PG.step1 PG.step2 PG.step3\n');
  f.write( '-20.0e0 20.0e0		#PG.min1 PG.max1\n');
  f.write( '-20.0e0 20.0e0		#PG.min2 PG.max2\n');
  f.write( '-20.0e0 20.0e0		#PG.min3 PG.max3\n');
  f.write( '-1 -1 -1		#PG.at1 PG.at2 PG.at3\n');
  f.write( '1.0 0.0 0.0		#PG.v1[0] PG.v1[1] PG.v1[2]\n' );
  f.write( '0.0 1.0 0.0		#PG.v2[0] PG.v2[1] PG.v2[2]\n' );
  f.write( '0.0 0.0 1.0		#PG.v3[0] PG.v3[1] PG.v3[2]\n' );
  f.close();


  if( printlevel > 3 ):
   print orca_plot, " ", gbw_file, " ", plot_infile;
  if( execution != 0 ):
   subprocess.call( [ orca_plot, gbw_file, plot_infile ] );

 fpz.close();
