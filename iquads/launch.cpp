

namespace iquads{

void launch( const iquads :: launch_sequence launch_seq )
{

  const int nstep = launch_seq.get_nstep();

  for( int istep = 0; i < nstep; i++ ){
    const iquads::step current_step = launch_seq.get_step( i );

    if( current_step.precheck_is_required() == true ){
      current_step.precheck();
    }

    current_step.exec();

    if( current_step.report_is_required() == true ){
     current_step.gather_report();
     current_step.print_report();
    }

  }

}


}
