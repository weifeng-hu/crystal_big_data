from option_basic import *

# dmrg options
class DMRG_options:

    option_header = "dmrg"

    #key word
    nsites           =  REQUIRED 
    na               =  REQUIRED
    nb               =  REQUIRED
    nele             =  UNDEFINED
    num              =  UNDEFINED
    sz               =  UNDEFINED

    num_schedule     =  UNDEFINED
    num_sweep        =  UNDEFINED
    M                =  UNDEFINED
    david_threshold  =  UNDEFINED
    sweep_threshold  =  UNDEFINED

    max_sweep        =  UNDEFINED
    dmrg_threshold   =  UNDEFINED
    nroots           =  UNDEFINED
    weights          =  UNDEFINED

    oneintegral      =  REQUIRED
    twointegral      =  REQUIRED
    integral_format  =  REQUIRED

    reorder           = UNDEFINED
    reorder_algorithm = UNDEFINED
    init_guess        = UNDEFINED
    dot_algorithm     = UNDEFINED
    two_to_one_dot    = UNDEFINED

    pdm               = UNDEFINED
    onepdm            = UNDEFINED
    twopdm            = UNDEFINED
    pdm_outfile       = UNDEFINED
    diag_method       = UNDEFINED

dmrg = DMRG_options();
