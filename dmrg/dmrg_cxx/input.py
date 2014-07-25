from options import *

dmrg.nsites         = 10
dmrg.na             = 5
dmrg.nb             = 5
dmrg.nele           = 10
dmrg.num            = 10
dmrg.sz             = 0.0
dmrg.num_schedule   = 3
dmrg.schedule.num_sweep       = [ 4,  4,  4  ]
dmrg.schedule.M               = [ 20, 40, 60 ]
dmrg.schedule.david_threshold = [ 1.0e-4, 1.0e-4, 1.0e-5 ]
dmrg.schedule.sweep_threshold = [ 1.0e-3, 1.0e-3, 1.0e-4 ]
dmrg.max_sweep      = 15
dmrg.dmrg_threshold = 1.e-7
dmrg.nroots         = 1
dmrg.weights        = [1.00]

dmrg.oneintegral    = "h2.int1"
dmrg.twointegral    = "h2.int2"
dmrg.integral_format  = "text"

dmrg.reorder            = True
dmrg.reorder_algorithm   = "rcm"
dmrg.init_guess     = "nrg"
dmrg.dot_algrithm   = "two_dot"
dmrg.two_to_one_dot = 12
dmrg.pdm = True
dmrg.onepdm = True
dmrg.twopdm = True
dmrg.pdm_outfile = [ "1.pdm", "2.pdm" ]

dmrg.diag_method = "lanczos"
