import subprocess

printlevel = 2;
execution  = 1;

print "printlevel: ", printlevel;
print "execution: ", execution;

#define the dmrg command
dmrg_command = "/home/wh288/Development/Block_pdm/block.spin_adapted";

#define the list of polyene
polyenes = [ "c10h12", "c12h14", "c14h16", "c16h18", "c18h20", "c20h22" ];
n_carbon = [ 10, 12, 14, 16, 18, 20 ];

#define states
states = [ "s0", "s1", "s2" ];

#define root directory
root_dir = "/home/wh288/Seagate_4TB/DATA/calculations/gradient.geo_opt/dmrgci/"

#define state files
s0_root_dir = root_dir + "ss_s0/";
s1_root_dir = root_dir + "ss_s1/";
s2_root_dir = root_dir + "ss_s2/";

#do trans pdm

#do s0-s1 at the begining of s1 geometry
# make a directory
for i in range(0, len(polyenes)):
 state_trans = "s0-s1";
 target_dir = root_dir + "/" + state_trans + "/" + polyenes[i] + "." + state_trans + "/";
 if printlevel > 2:
   print "computing transition pdm: ", polyenes[i], " " , state_trans;
 if printlevel > 3:
   print "   working directory:", target_dir;
 if execution != 0:
   subprocess.call( [ "mkdir", target_dir] );

 # get the ground state Rotation matrices and wavefunctions, statefile, FCIDUMP
 s0_dir = s0_root_dir + polyenes[i] + "_ss_s0" + "/" + "m1000" + "/" + "final" + "/";
 if printlevel > 3:
   print "   s0 state copy-from directory:", s0_dir;
 # Copy and rename Rotation, wavefunction and state file to 1( ket )
 if printlevel > 3:
  print "   copy and rename s0 files";
 for j in range( 1, ( n_carbon[i] - 1 ) ):
  sourcefile = s0_dir + "Rotation-0-" + str(j) + ".0.state0.tmp";
  targetfile = target_dir + "Rotation-0-" + str(j) + ".0.state1.tmp";
  s0_copycommand = "cp " + sourcefile + "  " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( [ "cp", sourcefile, targetfile ] );

  sourcefile = s0_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state0.tmp";
  targetfile = target_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile ] );

  sourcefile = s0_dir + "wave-0-" + str(j) + ".0.0.tmp";
  targetfile = target_dir + "wave-0-" + str(j) + ".0.1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( [ "cp", sourcefile, targetfile ] );

  sourcefile = s0_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.0.tmp";
  targetfile = target_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

 # rename s0 statefile
 sourcefile = s0_dir + "statefile.0.tmp";
 targetfile = target_dir + "statefile.0.1.tmp"
 s0_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s0_copycommand;
 if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

 # FCIDUMP
 sourcefile = s0_dir + polyenes[i] + ".qcdmrg.FCIDUMP";
 targetfile = target_dir + polyenes[i] + ".qcdmrg.FCIDUMP";
 s0_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s0_copycommand;
 if execution != 0:
   subprocess.call( ["cp", sourcefile, targetfile] );

 # get the s1 files;
 s1_dir = s1_root_dir + polyenes[i] + "_ss_s1" + "/" + "m1000" + "/" + "geo_cycle.0" + "/";
 if printlevel > 3:
   print "   s1 state copy-from directory:", s1_dir;
 # Copy and rename Rotation, wavefunction and state file to 0( bra )
 if printlevel > 3:
  print "   copy and rename s1 files";

 for j in range( 1, ( n_carbon[i] - 1 ) ):
  sourcefile = s1_dir + "Rotation-0-" + str(j) + ".0.state1.tmp";
  targetfile = target_dir + "Rotation-0-" + str(j) + ".0.state0.tmp";
  s1_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s1_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s1_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state1.tmp";
  targetfile = target_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state0.tmp";
  s1_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s1_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s1_dir + "wave-0-" + str(j) + ".0.1.tmp";
  targetfile = target_dir + "wave-0-" + str(j) + ".0.0.tmp";
  s1_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s1_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s1_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.1.tmp";
  targetfile = target_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.0.tmp";
  s1_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s1_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  # rename s1 statefile
 sourcefile = s1_dir + "statefile.0.tmp";
 targetfile = target_dir + "statefile.0.0.tmp"
 s1_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s1_copycommand;
 if execution != 0:
   subprocess.call( ["cp", sourcefile, targetfile] );

 # write input file
 if execution == 0:
  configfile = polyenes[i] + ".dmrginp.tmp";
 else:
  configfile = target_dir + polyenes[i] + ".dmrginp.tmp";
 f = open( configfile, 'wt' );
 f.write('orbitals '); f.write( target_dir + polyenes[i] + ".qcdmrg.FCIDUMP" ); f.write('\n');
 f.write('prefix ');f.write( target_dir ); f.write('\n');
 f.write('nelec '); f.write( str(n_carbon[i]) ); f.write('\n');
 f.write('spin 0\n');
 f.write('point_group c1\n');
 f.write('sweep_tol 1.0e-8\n');
 f.write('irrep 1\n');
 f.write('schedule\n');
 f.write('0 1000 1.0e-7 0.0e0\n');
 f.write('end\n');
 f.write('onedot\n');
 f.write('maxiter 2\n');
 f.write('nroots 1\n');
 f.write('outputlevel 1\n');
 f.write('docd\n');
 f.write('restart_transition_onepdm 0 1 1 1\n');
 f.close();
 
 outfile = target_dir + polyenes[i] + ".transpdm.out";
 if printlevel > 3:
   print "   configure file: ", configfile;
   print "   outfile: ", outfile;
 # execution of trans pdm 
 transpdm_command = dmrg_command + " " + configfile + " > " + outfile;
 if printlevel > 2:
   print transpdm_command;
 if execution != 0:
   subprocess.call( [ dmrg_command, configfile, outfile ] );

 if printlevel > 2:
   print "   done";

 state_trans = "s0-s2";
#do s0-s2 at the begining of s2 geometry/end of s0 geometry
# make a directory
for i in range(0, len(polyenes)):
 target_dir = root_dir + "/" + state_trans + "/" + polyenes[i] + "." + state_trans + "/";
 if printlevel > 2:
   print "computing transition pdm: ", polyenes[i], " " , state_trans;
 if printlevel > 3:
   print "   working directory:", target_dir;
 if execution != 0:
   subprocess.call( [ "mkdir", target_dir] );

 # get the ground state Rotation matrices and wavefunctions, statefile, FCIDUMP
 s0_dir = s0_root_dir + polyenes[i] + "_ss_s0" + "/" + "m1000" + "/" + "final" + "/";
 if printlevel > 3:
   print "   s0 state copy-from directory:", s0_dir;

 # Copy and rename Rotation, wavefunction and state file to 1( ket )
 if printlevel > 3:
  print "   copy and rename s0 files";
 for j in range( 1, ( n_carbon[i] - 1 ) ):
  sourcefile = s0_dir + "Rotation-0-" + str(j) + ".0.state0.tmp";
  targetfile = target_dir + "Rotation-0-" + str(j) + ".0.state1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s0_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state0.tmp";
  targetfile = target_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s0_dir + "wave-0-" + str(j) + ".0.0.tmp";
  targetfile = target_dir + "wave-0-" + str(j) + ".0.1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s0_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.0.tmp";
  targetfile = target_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.1.tmp";
  s0_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s0_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

 # rename s0 statefile
 sourcefile = s0_dir + "statefile.0.tmp";
 targetfile = target_dir + "statefile.0.1.tmp"
 s0_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s0_copycommand;
 if execution != 0:
   subprocess.call( ["cp", sourcefile, targetfile] );

 # FCIDUMP
 sourcefile = s0_dir + polyenes[i] + ".qcdmrg.FCIDUMP";
 targetfile = target_dir + polyenes[i] + ".qcdmrg.FCIDUMP";
 s0_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s0_copycommand;
 if execution != 0:
   subprocess.call( ["cp", sourcefile, targetfile] );

 # get the s2 files;
 s2_dir = s2_root_dir + polyenes[i] + "_ss_s2" + "/" + "m1000" + "/" + "geo_cycle.0" + "/";
 if printlevel > 3:
   print "   s2 state copy-from directory:", s2_dir;
 # Copy and rename Rotation, wavefunction and state file to 0( bra )
 if printlevel > 3:
  print "   copy and rename s2 files";

 for j in range( 1, ( n_carbon[i] - 1 ) ):
  sourcefile = s2_dir + "Rotation-0-" + str(j) + ".0.state2.tmp";
  targetfile = target_dir + "Rotation-0-" + str(j) + ".0.state0.tmp";
  s2_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s2_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s2_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state2.tmp";
  targetfile = target_dir + "Rotation-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.state0.tmp";
  s2_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s2_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s2_dir + "wave-0-" + str(j) + ".0.2.tmp";
  targetfile = target_dir + "wave-0-" + str(j) + ".0.0.tmp";
  s2_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s2_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

  sourcefile = s2_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.2.tmp";
  targetfile = target_dir + "wave-" + str(j) + "-" + str( n_carbon[i] - 1 ) + ".0.0.tmp";
  s2_copycommand = "cp " + sourcefile + " " + targetfile;
  if printlevel > 5:
    print s2_copycommand;
  if execution != 0:
    subprocess.call( ["cp", sourcefile, targetfile] );

 # rename s2 statefile
 sourcefile = s2_dir + "statefile.0.tmp";
 targetfile = target_dir + "statefile.0.0.tmp"
 s2_copycommand = "cp " + sourcefile + " " + targetfile;
 if printlevel > 5:
   print s2_copycommand;
 if execution != 0:
   subprocess.call( ["cp", sourcefile, targetfile] );

 # write input file
 if execution == 0:
  configfile = polyenes[i] + ".dmrginp.tmp";
 else:
  configfile = target_dir + polyenes[i] + ".dmrginp.tmp";
 f = open( configfile, 'wt' );
 f.write('orbitals '); f.write( target_dir + polyenes[i] + ".qcdmrg.FCIDUMP" ); f.write('\n');
 f.write('prefix ');f.write( target_dir ); f.write('\n');
 f.write('nelec '); f.write( str(n_carbon[i]) ); f.write('\n');
 f.write('spin 0\n');
 f.write('point_group c1\n');
 f.write('sweep_tol 1.0e-8\n');
 f.write('irrep 1\n');
 f.write('schedule\n');
 f.write('0 1000 1.0e-7 0.0e0\n');
 f.write('end\n');
 f.write('onedot\n');
 f.write('maxiter 2\n');
 f.write('nroots 1\n');
 f.write('outputlevel 1\n');
 f.write('docd\n');
 f.write('restart_transition_onepdm 0 1 1 1\n');
 f.close();
 
 outfile = target_dir + polyenes[i] + ".transpdm.out";
 if printlevel > 3:
   print "   configure file: ", configfile;
   print "   outfile: ", outfile;
 # execution of trans pdm 
 transpdm_command = dmrg_command + " " + configfile + " > " + outfile;
 if printlevel > 2:
   print transpdm_command;
 if execution != 0:
   subprocess.call( [dmrg_command, configfile, outfile] );
 if printlevel > 2:
   print "   done";

#end 
