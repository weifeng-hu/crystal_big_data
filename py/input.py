from dmrg import *

dmrg.nsites    = 12
dmrg.na        = 12
dmrg.nb        = 12
dmrg.guess     = "hf"
dmrg.nroots    = 1
dmrg.weights   = 1.00
dmrg.num_schedule      =  4
dmrg.M               = [ 100,    200,    300,    400    ]
dmrg.david_threshold = [ 1.0e-4, 1.0e-5, 1.0e-5, 1.0e-6 ]
dmrg.sweep_threshold = [ 1.0e-3, 1.0e-4, 1.0e-4, 1.0e-5 ]
dmrg.oneintegral = "porphin.qcdmrg.int1"
dmrg.twointegral = "porphin.qcdmrg.int2"
dmrg.dmrg_threshold   = 1.0e-4
dmrg.pdm         = True
