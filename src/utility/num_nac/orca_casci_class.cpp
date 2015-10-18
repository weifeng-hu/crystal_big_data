#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "utilities/num_nac/orca_casci.h"

namespace iquads {

namespace num_nac {

void orca_casci :: write_orca_input( string filename )
{

    ofstream ofs;
    ofs.open( filename.c_str(), std::ios::out );

    const int natom = coord.size();
    char comma = '"' ;
    ofs << "%" << "coords" << endl;
    ofs << " ctyp xyz" << endl;
    ofs << " units angs" << endl;
    ofs << " coords" << endl;
    ofs.precision(16);
    for( size_t i = 0; i < natom; i++ ){
     ofs << atoms.at(i) << " " << scientific << coord.at(i).at(0) << " " << coord.at(i).at(1) << " " << coord.at(i).at(2) << endl;
    }
    ofs << " end" << endl;
    ofs << "end" << endl;
    ofs << "!rhf 6-31g extremescf" << endl;

    ofs << "$new_job" << endl;
    ofs << "%" << "coords" << endl;
    ofs << " ctyp xyz" << endl;
    ofs << " units angs" << endl;
    ofs << " coords" << endl;
    ofs.precision(10);
    for( size_t i = 0; i < natom; i++ ){
     ofs << atoms.at(i) << " " << scientific << coord.at(i).at(0) << " " << coord.at(i).at(1) << " " << coord.at(i).at(2) << endl;
    }
    ofs << " end" << endl;
    ofs << "end" << endl;
    ofs << "!casscf 6-31g extremescf" << endl;
    ofs << "%" << "casscf nel " << nel << endl;
    ofs << "       norb " << norb << endl;
    ofs << "       mult " << 2*s+1 << endl;
    ofs << "       nroots 2" << endl;
    ofs << "       weights[0] = 1, 1" << endl;
    ofs << "       cistep dmrg" << endl;
    ofs << "       maxiter 1" << endl;
    ofs << " dmrg_para" << endl;
    ofs << "       sweeptol 1.0e-12" << endl;
    ofs << "       new_version true" << endl;
    ofs << "       nroots 2" << endl;
    ofs << "       weights = 0.5e0, 0.5e0" << endl;
    ofs << "       irrep 0" << endl;
    ofs << "       mult " << 2*s+1 << endl;
    ofs << "       use_mpi true" << endl;
    ofs << "       use_host false" << endl;
    ofs << "       np 1" << endl;
    ofs << "       pathname " << comma << "/home/wh288/Development/Block_stracking/block.spin_adapted" << comma << endl;
    ofs << "       nschedule 1" << endl;
    ofs << "       m = 200 " << endl;
    ofs << "       iteration = 0" << endl;
    ofs << "       david_tol = 1.0e-8" << endl;
    ofs << "       noise = 0.0e0" << endl;
    ofs << "       twodot true" << endl;
    ofs << "       twodot_to_onedot 4" << endl;
    ofs << "       maxiter 0" << endl;
    ofs << "       restart false" << endl;
    ofs << "       reset_iter false" << endl;
    ofs << "       savetransf false" << endl;
    ofs << "       mom false" << endl;
    ofs << "       prefix " << comma << "./" << comma << endl;
    ofs << "       hostfile " << comma << "hosts" << comma << endl;
    ofs << " end" << endl;
    ofs << "end" << endl;

    ofs.close();

}


}

}
