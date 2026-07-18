from z3 import *


ADDR_BITS = 64

# System V AMD64 ABI e AAPCS64 garantem, na entrada de uma funcao,
# alinhamento de pilha de 16 bytes; variaveis locais (arrays, structs,
# escalares) tipicamente herdam esse alinhamento minimo do frame.
# Modelamos o endereco-base como uma variavel simbolica sujeita apenas
# a essa restricao -- em vez de um valor concreto arbitrario (o antigo
# BitVecVal(100, 64), que nao era sequer multiplo de 8 e por isso
# invalidava silenciosamente casos de alinhamento de 8 bytes).
BASE_ALIGNMENT = 16


def build_model(info):

    solver = Solver()

    align = info["alignment"]

    base = BitVec("base", ADDR_BITS)

    solver.add(
        URem(base, BitVecVal(BASE_ALIGNMENT, ADDR_BITS)) == 0
    )

    # ==================================================
    # CASO SIMBÓLICO (offset desconhecido em tempo de analise)
    # ==================================================

    if info["kind"] == "symbolic":

        i32 = BitVec("i", 32)

        i = ZeroExt(32, i32)

        bound = info.get("symbolic_bound")

        if bound is not None:

            solver.add(
                ULT(i32, BitVecVal(bound, 32))
            )

        addr = base + i

        return {
            "solver": solver,
            "addr": addr,
            "align": align,
            "symbolic": True,
            "offset": None,
            "sym_var": i32,
        }

    # ==================================================
    # TODOS OS DEMAIS CASOS (offset constante conhecido)
    # ==================================================

    offset = info["offset"]

    addr = base + BitVecVal(offset, ADDR_BITS)

    return {
        "solver": solver,
        "addr": addr,
        "align": align,
        "symbolic": False,
        "offset": offset,
        "base_var": base,
    }


def _check(model, want_zero):

    solver = Solver()

    solver.add(model["solver"].assertions())

    cond = URem(model["addr"], BitVecVal(model["align"], ADDR_BITS)) == 0

    solver.add(cond if want_zero else Not(cond))

    return solver


def check_alignment(model):
    return _check(model, want_zero=True).check()


def check_misalignment(model):
    return _check(model, want_zero=False).check()


def get_counterexample(model, want_zero):
    """
    Retorna um dicionario com valores concretos (base, offset/indice
    simbolico e endereco final) que satisfazem a condicao pedida,
    ou None se UNSAT.
    """

    solver = _check(model, want_zero=want_zero)

    if solver.check() != sat:
        return None

    m = solver.model()

    example = {}

    if model["symbolic"]:

        i_val = m.eval(model["sym_var"], model_completion=True)

        example["i"] = i_val.as_long()

    example["addr"] = m.eval(model["addr"], model_completion=True).as_long()

    return example
