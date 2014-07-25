from option_basic import *

# scf options
class SCF_options:

    option_header = "scf"

    #key word
    nele       = REQUIRED
    na         = UNDEFINED
    nb         = UNDEFINED
    nbas       = UNDEFINED
    norb       = UNDEFINED

    coord      = REQUIRED

    diis       = UNDEFINED
    scf_tol    = UNDEFINED
    init_guess = UNDEFINED

scf = SCF_options();
