from z3 import *

ADDR_BITS = 32

ALIGNMENT = {

    "uint16_t": 2,
    "uint32_t": 4,
    "uint64_t": 8

}


def concrete_check(offset, ptr_type):

    solver = Solver()

    align = ALIGNMENT[ptr_type]

    addr = BitVecVal(
        100 + offset,
        ADDR_BITS
    )

    solver.add(

        URem(
            addr,
            BitVecVal(
                align,
                ADDR_BITS
            )
        ) == 0

    )

    return solver.check()


def symbolic_check(ptr_type):

    solver = Solver()

    align = ALIGNMENT[ptr_type]

    i = BitVec("i", ADDR_BITS)

    solver.add(i >= 0)
    solver.add(i < 8)

    addr = BitVecVal(
        100,
        ADDR_BITS
    ) + i

    solver.add(

        URem(
            addr,
            BitVecVal(
                align,
                ADDR_BITS
            )
        ) != 0

    )

    return solver.check()
