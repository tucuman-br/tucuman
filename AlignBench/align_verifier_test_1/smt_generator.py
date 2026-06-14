from z3 import *

ADDR_BITS = 32

def check_alignment(offset, alignment):

    solver = Solver()

    base = BitVecVal(100, ADDR_BITS)

    ptr = base + BitVecVal(
        offset,
        ADDR_BITS
    )

    solver.add(
        URem(
            ptr,
            BitVecVal(
                alignment,
                ADDR_BITS
            )
        ) == 0
    )

    return solver.check()
