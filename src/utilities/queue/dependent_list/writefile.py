
sweep_end = 14;
dimer_name = 'aa';
scratch_dir = "/scratch/weifeng/benzene_dim_" +  dimer_name + "/48e_114o/"

f2 = open( "submit.2", "w" );
f2.write( "#!/bin/bash\n" );

x = 12;

job_name = "JOB_" + str(x);
cmd_name = "dimer_" + dimer_name + "." + str(x);
dmrg_input_name = "benzene_dim.dmrginp.tmp." + str(x);
dmrg_output_name = "benzene_dim.dmrg.out_0." + str(x+1);

f2.write( job_name ); f2.write( "=$(qsub " ); f2.write( cmd_name ); f2.write( ")\n" );
f2.write( "echo " ); f2.write( "$" ); f2.write( job_name ); f2.write("\n");

print "job_name = ", job_name, "   cmd_name = ", cmd_name, "   dmrg_input_name = ", dmrg_input_name, "   dmrg_output_name = ", dmrg_output_name;
f = open( cmd_name, 'w' );
f.write( "#PBS -l nodes=19:ppn=6,mem=1140gb\n" );
f.write( "#PBS -l walltime=4:00:00\n" );
f.write( "#PBS -m abe\n" );
f.write( "#PBS -M weifeng@princeton.edu\n" );
f.write( "#PBS -d " ); f.write( scratch_dir );
f.write("\n");
f.write("\n");
execution_cmd = "mpirun -np 114 /home/weifeng/Block_warmup/block.spin_adapted " + scratch_dir + dmrg_input_name + " > " + scratch_dir + dmrg_output_name;
f.write(execution_cmd);
f.close();  

f = open( dmrg_input_name, 'w' );
f.write( "orbitals benzene_dim.qcdmrg.FCIDUMP\n" );
f.write( "prefix " ); f.write(scratch_dir); f.write("\n");
f.write( "nelec 48\n" );
f.write( "spin 0\n" );
f.write( "point_group c1\n" );
f.write( "gaopt genetic_reorder.dat\n" );
f.write( "sweep_tol 1.00000e-5\n" );
f.write( "irrep 1\n" );
f.write( "schedule\n" );
f.write( "0 500 1.000000e-05 1.000000e-04\n");
f.write( "end\n" );
f.write( "twodot\n");
f.write( "warmup_end " ); f.write( str(x+1) ); f.write("\n");
f.write( "maxiter 1\n" );
f.write( "nroots 1\n" );
f.write( "outputlevel 1\n" );
f.write( "restart\n" );
f.write( "restart_warm" );
f.close();


for x in range ( 13, sweep_end ):

  job_name = "JOB_" + str(x);
  job_name_last = "JOB_" + str(x-1);
  cmd_name = "dimer_" + dimer_name + "." + str(x);
  dmrg_input_name = "benzene_dim.dmrginp.tmp." + str(x);
  dmrg_output_name = "benzene_dim.dmrg.out_0." + str(x+1);

  f2.write( job_name ); f2.write( "=$(qsub -W depend=afterok:$" ); f2.write( job_name_last ); f2.write(" "); f2.write( cmd_name ); f2.write( ")\n" );
  f2.write( "echo " ); f2.write( "$" ); f2.write( job_name ); f2.write("\n");

  print "job_name = ", job_name, "   cmd_name = ", cmd_name, "   dmrg_input_name = ", dmrg_input_name, "   dmrg_output_name = ", dmrg_output_name;
  f = open( cmd_name, 'w' );
  f.write( "#PBS -l nodes=19:ppn=6,mem=1140gb\n" );
  f.write( "#PBS -l walltime=4:00:00\n" );
  f.write( "#PBS -m abe\n" );
  f.write( "#PBS -M weifeng@princeton.edu\n" );
  f.write( "#PBS -d " ); f.write( scratch_dir );
  f.write("\n");
  f.write("\n");
  execution_cmd = "mpirun -np 114 /home/weifeng/Block_warmup/block.spin_adapted " + scratch_dir + dmrg_input_name + " > " + scratch_dir + dmrg_output_name;
  f.write(execution_cmd);
  f.close();  

  f = open( dmrg_input_name, 'w' );
  f.write( "orbitals benzene_dim.qcdmrg.FCIDUMP\n" );
  f.write( "prefix " ); f.write(scratch_dir); f.write("\n");
  f.write( "nelec 48\n" );
  f.write( "spin 0\n" );
  f.write( "point_group c1\n" );
  f.write( "gaopt genetic_reorder.dat\n" );
  f.write( "sweep_tol 1.00000e-5\n" );
  f.write( "irrep 1\n" );
  f.write( "schedule\n" );
  f.write( "0 500 1.000000e-05 1.000000e-04\n");
  f.write( "end\n" );
  f.write( "twodot\n");
  f.write( "warmup_end " ); f.write( str(x+1) ); f.write("\n");
  f.write( "maxiter 1\n" );
  f.write( "nroots 1\n" );
  f.write( "outputlevel 1\n" );
  f.write( "restart\n" );
  f.write( "restart_warm" );
  f.close();


f2.close();
print "end";
