import subprocess

printlevel = 4;
execution  = 0;

orca_bin = "/home/wh288/Development/orca_lno/x86_exe/orca";
ph_trans = "/home/wh288/Development/iqs/utilities/ph_analysis/ph_trans";

dir_root = "/home/wh288/Development/examples/1pdm_analysis/";
polyenes = [ "c10h12", "c12h14", "c14h16", "c16h18", "c18h20" ,"c20h22" ];
nbas = [ 200, 238, 276, 314, 352, 390 ];
nact = [ 10, 12, 14, 16, 18, 20 ];
natom = [ 22, 26, 30, 34, 38, 42 ];
npolyene = len( polyenes );

 # compute transformed transition density matrices of polyenes

 # A. compute transition density matrices in canonical orbitals
 #transpdm_script = "ph_run.py";
 #if printlevel > 3:
 # print "running", " python ", transpdm_script;
 #if execution != 0:
 # subprocess.call( [ "python",  transpdm_script ] );

for i in range( 0, 1 ):

 # get coordinates
 coord_file = dir_root + polyenes[i] + ".coord";
 f_coord = open( coord_file );
 coord = [];
 for icoord in range( 0, natom[i] );
  line = f_coord.readline(); line.rstrip('\n');
  coord.append( line ); 
 f_coord.close();

 # make main directory
 dir_main = dir_root + polyenes[ i ] + "/";
 if printlevel > 3:
  print " main directory: ", dir_main;
 if execution != 0:
  subprocess.call( "mkdir", polyenes[i] );

 # 1. compute canonical orbital C matrix, and overlap
 # ===============================================================================================
 # make sub directory for fcidump
 print " FCIDUMP";
 dir_fcidump = dir_main + "/fcidump/";
 if printlevel > 3:
  print "  fcidump directory: ", dir_fcidump;
 if execution != 0:
  subprocess.call( [ "mkdir", dir_fcidump ] );

 # write input for orca
 fcidump_infile = dir_fcidump + polyenes[i] + ".inp";
 f_dump = open( fcidump_infile, "wt" );
 f_dump.write('%coords\n');
 f_dump.write(' CTyp xyz\n');
 f_dump.write(' Units Angs\n');
 f_dump.write(' coords\n');
 for icoord in range( 0, natom[i] ):
  f_dump.write( coord[icoord] ); f_dump.write('\n');
 f_dump.write(' end\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_dump.write('!rhf cc-pvdz extremescf moread\n');
 f_dump.write('\n');
 f_dump.write('%output\n');
 f_dump.write('  print[P_ReducedOrbPopMO_L] 1\n');
 f_dump.write('  pi_threshold  40.0e0\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_dump.write('$new_job\n');
 f_dump.write('%coords\n');
 f_dump.write(' CTyp xyz\n');
 f_dump.write(' Units Angs\n');
 f_dump.write(' coords\n');
 for icoord in range( 0, natom[i] ):
  f_dump.write( coord[icoord] ); f_dump.write('\n');
 f_dump.write(' end\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_dump.write('!casscf cc-pvdz extremescf moread\n');
 f_dump.write('%moinp '); f_dump.write('"'); f_dump.write(polyenes[i]); f_dump.write('.copy.gbw"\n');
 f_dump.write('%casscf nel '); f_dump.write( str(nact[i]) ); f_dump.write('\n');
 f_dump.write('	norb '); f_dump.write( str( nact[i]) ); f_dump.write('\n');
 f_dump.write(' mult 1\n');
 f_dump.write(' nroots 2\n');
 f_dump.write(' weights[0] = 0, 1\n');
 f_dump.write(' cistep dmrg\n');
 f_dump.write(' maxiter 0\n');
 f_dump.write(' etol 1.0e-14\n');
 f_dump.write(' doct 1\n');
 f_dump.write(' dmrg_para\n');
 f_dump.write('  SweepTol 1.0e-12\n');
 f_dump.write('  new_version true\n');
 f_dump.write('  Nroots 2\n');
 f_dump.write('  weights = 0.0e0, 1.0e0\n');
 f_dump.write('  irrep 0\n');
 f_dump.write('  use_mpi true\n');
 f_dump.write('  use_host false\n');
 f_dump.write('  np 8\n');
 f_dump.write('  pathname "/home/wh288/Block_stracking/block.spin_adapted"\n ');
 f_dump.write('  nschedule 4\n');
 f_dump.write('  m = 200, 600, 1000, 1000\n');
 f_dump.write('  iteration = 0, 4, 8, 12\n');
 f_dump.write('  david_tol = 1.0e-7, 1.0e-7, 1.0e-7, 1.0e-8\n');
 f_dump.write('  noise = 1.0e-4, 1.0e-5, 1.0e-8, 0.0e0\n');
 f_dump.write('  twodot true\n');
 f_dump.write('  Twodot_to_Onedot 14\n');
 f_dump.write('  Maxiter 20\n')
 f_dump.write('  Restart true\n');
 f_dump.write('  Reset_iter false\n');
 f_dump.write('  Savetransf false\n');
 f_dump.write('  MOM false\n');
 f_dump.write('  prefix "/scratch/wh288/'); f_dump.write( polyenes[i] ); f_dump.write('_ss_s1/m1000/"\n');
 f_dump.write('  hostfile "hosts"\n');
 f_dump.write(' end\n');
 f_dump.write('end\n');
 f_dump.close();

 # run orca
 fcidump_outfile = dir_fcidump + polyenes[i] + ".scf.out";
 if printlevel > 3:
  print "  run ", orca_bin, " ", fcidump_infile, " > ", fcidump_outfile;
 if execution != 0:
  subprocess.call( [ orca_bin, fcidump_infile, " > ", fcidump_outfile ] );

 # get cmo and sa files
 cmo_file_source = dir_fcidump + polyenes[i] + "." + "orca" + "." + "mo";
 sov_file_source = dir_fcidump + polyenes[i] + "." + "orca" + "." + "sa";
 active_file_source = dir_fcidump + "/" + polyenes[i] + "." + "orca" + "." + "act_orbs";
 # ===============================================================================================

 # 2. copy files to ph_analysis and compute S^(-1/2)
 # ===============================================================================================
 # make sub directory for ph_analysis
 print " COMPUTE S INVERSE HALF";
 dir_ph_analysis = dir_main + "/ph_analysis/";
 if printlevel > 3:
  print "  ph_analysis directory: ", dir_ph_analysis;
 if execution != 0:
  subprocess.call( [ "mkdir", dir_ph_analysis ] );

 # define cmo and sa and active files in ph_analysis
 cmo_file_destination = dir_ph_analysis + polyenes[i] + "." + "orca" + "." + "mo";
 sov_file_destination = dir_ph_analysis + polyenes[i] + "." + "orca" + "." + "sa";
 active_file_destination = dir_ph_analysis + polyenes[i] + "." + "orca" + "." + "act_orbs";

 if printlevel > 3:
  print "cp ", cmo_file_source, " ", cmo_file_destination;
  print "cp ", sov_file_source, " ", sov_file_destination;
  print "cp ", active_file_source, " ", active_file_destination;
 if execution != 0:
  subprocess.call( [ "cp", cmo_file_source, cmo_file_destination ] );
  subprocess.call( [ "cp", sov_file_source, sov_file_destination ] );
  subprocess.call( [ "cp", active_file_source, active_file_destination ] );

 # write ph.conf and run ph_trans for S^(-1/2)
 ph_configure = dir_ph_analysis + "/" + "ph.conf";
 f_conf = open( ph_configure, "wt" );
 f_conf.write('basename	'); f_conf.write( polyenes[i] ); f_conf.write('\n');
 f_conf.write('norb		'); f_conf.write( nbas[i] ); f_conf.write( '\n' );
 f_conf.write('nact		'); f_conf.write( nact[i] ); f_conf.write( '\n' );
 f_conf.write('t1_thresh	1.0e-1\n');
 f_conf.write('t2_thresh	1.0e-1\n');
 f_conf.write('solve_u		2\n');
 f_conf.write('compute_s_only	1\n');
 f_conf.close();
 ph_out = dir_ph_analysis + "/" + "ph.sih.out";

 if printlevel > 3:
  print ph_trans, " ", ph_configure, " >  ",  ph_out;
 if execution != 0:
  subprocess.call( [ ph_trans, ph_configure, ph_out ] );

 # next we need s_inversehalf.txt
 sih_file_source = dir_ph_analysis + "/" + "s_inversehalf.txt";

 # ===============================================================================================

 # 3. copy s_inversehalf and run orca to label pz orbitals
 # ===============================================================================================
 print " FIND AND LABEL Pz";
 # make orthgonalized AO directory
 dir_orth = dir_main + "/orth_ao/";
 if printlevel > 3:
  print "  orthgonalize AO directory: ", dir_orth;
 if execution != 0:
  subprocess.call( [ "mkdir", dir_orth ] );

 # next we copy s_inversehalf.txt
 sih_file_destination = dir_orth + "/" + "s_inversehalf.txt";

 if printlevel > 3:
  print "cp ", sih_file_source, " ", sih_file_destination;
 if execution != 0:
  subprocess.call( [ "cp", sih_file_source, sih_file_destination ] );

 # write orca input file
 orthao_infile = dir_orth + polyenes[i] + ".inp";
 f_orth = open( orthao_infile );
 f_dump.write('%coords\n');
 f_dump.write(' CTyp xyz\n');
 f_dump.write(' Units Angs\n');
 f_dump.write(' coords\n');
 for icoord in range( 0, natom[i] ):
  f_dump.write( coord[icoord] ); f_dump.write('\n');
 f_dump.write(' end\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_dump.write('!rhf cc-pvdz extremescf moread\n');
 f_dump.write('\n');
 f_dump.write('%scf\n');
 f_dump.write(' maxiter 0\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_dump.write('%output\n');
 f_dump.write('  print[P_ReducedOrbPopMO_L] 1\n');
 f_dump.write('  pi_threshold  40.0e0\n');
 f_dump.write('end\n');
 f_dump.write('\n');
 f_orth.close();

 # run orca
 orthao_outfile = dir_orth + polyenes[i] + ".sih.out";
 if printlevel > 3:
  print "  run", orca_bin, " ", orthao_infile, " > ", orthao_outfile;
 if execution != 0:
  subprocess.call( [ orca_bin, orthao_infile, " > ", orthao_outfile  ] );

 # get pz labels
 pz_file_source = dir_orth + "orca.2pz_orbs";
 # ===============================================================================================

 # 4. go back to ph_analysis and run ph_analysis to get AO PDMs
 # ===============================================================================================
 print " COMPUTE PDM";
 # copy pz label file
 pz_file_destination = dir_ph_analysis + "orca.2pz_orbs"; 
 if printlevel > 3:
  print "cp ", pz_file_source, " ", pz_file_destination;
 if execution != 0:
  subprocess.call( [ "cp", pz_file_source, pz_file_destination ] );

 # write ph.conf
 ph_configure = dir_ph_analysis + "/" + "ph.conf";
 f_conf = open( ph_configure, "wt" );
 f_conf.write('basename	'); f_conf.write( polyenes[i] ); f_conf.write('\n');
 f_conf.write('norb		'); f_conf.write( nbas[i] ); f_conf.write( '\n' );
 f_conf.write('nact		'); f_conf.write( nact[i] ); f_conf.write( '\n' );
 f_conf.write('t1_thresh	1.0e-1\n');
 f_conf.write('t2_thresh	1.0e-1\n');
 f_conf.write('solve_u		2\n');
 f_conf.write('compute_s_only	0\n');
 f_conf.close();
 ph_out = dir_ph_analysis + "/" + "ph.out_pdm";

 # execute ph_trans
 if printlevel > 3:
  print ph_trans, " ", ph_configure, " >  ",  ph_out;
 if execution != 0:
  subprocess.call( [ ph_trans, ph_configure, ph_out ] );
