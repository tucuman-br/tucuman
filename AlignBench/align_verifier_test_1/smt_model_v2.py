from z3 import *

ADDR_BITS = 32

# =====================================================
# ALINHAMENTO
# =====================================================

ALIGNMENTS = {

    "char": 1,
    "uint8_t": 1,

    "uint16_t": 2,

    "uint32_t": 4,

    "uint64_t": 8

}

# =====================================================
# VERIFICAÇÃO
# =====================================================

def check_alignment(offset, type_name):

    alignment = ALIGNMENTS[type_name]

    solver = Solver()

    base_addr = BitVecVal(
        100,
        ADDR_BITS
    )

    ptr_addr = (
        base_addr
        +
        BitVecVal(
            offset,
            ADDR_BITS
        )
    )

    solver.add(

        URem(
            ptr_addr,
            BitVecVal(
                alignment,
                ADDR_BITS
            )
        ) == 0

    )

    return solver.check()

# =====================================================
# E1
# OFFSET SIMBÓLICO
# =====================================================

def symbolic_offset_without_alignment():

    solver = Solver()

    offset = BitVec(
        "offset",
        ADDR_BITS
    )

    solver.add(offset >= 0)
    solver.add(offset < 8)

    return solver.check()

# =====================================================
# E2
# OFFSET SIMBÓLICO + ALIGNMENT
# =====================================================

def symbolic_offset_with_alignment(
    alignment
):

    solver = Solver()

    offset = BitVec(
        "offset",
        ADDR_BITS
    )

    base = BitVecVal(
        100,
        ADDR_BITS
    )

    ptr = base + offset

    solver.add(offset >= 0)
    solver.add(offset < 8)

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
