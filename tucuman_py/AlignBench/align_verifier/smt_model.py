from z3 import *


ADDR_BITS = 64


def build_model(info):

    solver = Solver()

    align = info["alignment"]

    # ==================================================
    # ENDEREÇO BASE
    # ==================================================

    base = BitVecVal(
        100,
        ADDR_BITS
    )

    # ==================================================
    # CASO SIMBÓLICO
    # ==================================================

    if info["kind"] == "symbolic":

        i = BitVec(
            "i",
            ADDR_BITS
        )

        bound = info.get(
            "symbolic_bound",
            8
        )

        solver.add(
            ULT(
                i,
                BitVecVal(
                    bound,
                    ADDR_BITS
                )
            )
        )

        addr = base + i

        return {
            "solver": solver,
            "addr": addr,
            "align": align,
            "symbolic": True,
            "offset": None
        }

    # ==================================================
    # TODOS OS DEMAIS CASOS
    # ==================================================

    offset = info["offset"]

    addr = base + BitVecVal(
        offset,
        ADDR_BITS
    )

    return {
        "solver": solver,
        "addr": addr,
        "align": align,
        "symbolic": False,
        "offset": offset
    }


def add_alignment_property(model):

    solver = model["solver"]

    addr = model["addr"]

    align = model["align"]

    solver.add(

        URem(

            addr,

            BitVecVal(
                align,
                ADDR_BITS
            )

        ) == 0

    )

    return solver


def add_misalignment_property(model):

    solver = model["solver"]

    addr = model["addr"]

    align = model["align"]

    solver.add(

        URem(

            addr,

            BitVecVal(
                align,
                ADDR_BITS
            )

        ) != 0

    )

    return solver


def check_alignment(model):

    solver = Solver()

    solver.add(
        model["solver"].assertions()
    )

    solver.add(

        URem(

            model["addr"],

            BitVecVal(
                model["align"],
                ADDR_BITS
            )

        ) == 0

    )

    return solver.check()


def check_misalignment(model):

    solver = Solver()

    solver.add(
        model["solver"].assertions()
    )

    solver.add(

        URem(

            model["addr"],

            BitVecVal(
                model["align"],
                ADDR_BITS
            )

        ) != 0

    )

    return solver.check()
