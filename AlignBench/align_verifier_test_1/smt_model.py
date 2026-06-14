from z3 import *

ADDR_BITS = 32

def verify_alignment(offset, alignment):

    solver = Solver()

    base_addr = BitVecVal(100, ADDR_BITS)

    ptr_addr = base_addr + BitVecVal(offset, ADDR_BITS)

    solver.add(
        URem(
            ptr_addr,
            BitVecVal(alignment, ADDR_BITS)
        ) == 0
    )

    result = solver.check()

    return result
