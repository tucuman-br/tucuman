import os
import sys

from z3 import sat

from parser import parse_file
from smt_model import build_model
from smt_model import check_alignment
from smt_model import check_misalignment
from smt_model import get_counterexample


# =====================================================
# RELATÓRIO
# =====================================================

def print_header(filename):

    print()
    print("=" * 50)
    print(os.path.basename(filename))
    print("=" * 50)
    print()


def print_info(info):

    print("Tipo:", info["ptr_type"])
    print("Alinhamento:", info["alignment"])
    print("Caso:", info["kind"])

    if info["kind"] == "symbolic":

        bound = info.get("symbolic_bound")

        if bound is not None:
            print("Offset simbolico: i, com 0 <= i <", bound)
        else:
            print("Offset simbolico: i (sem limite conhecido)")

    else:

        print("Offset:", info["offset"])

        if info.get("struct"):
            print(
                "Struct:", info["struct"],
                "(packed)" if info.get("packed") else "(nao-packed)",
                "campo:", info.get("field")
            )

    print()


# =====================================================
# CLASSIFICAÇÃO (compartilhada com benchmark_runner.py)
# =====================================================

STATUS_ALINHADO = "ALINHADO"
STATUS_VIOLACAO = "VIOLACAO"
STATUS_PARCIAL = "PARCIALMENTE_ALINHADO"
STATUS_INCONSISTENTE = "INCONSISTENTE"


def classify_result(aligned_result, misaligned_result):

    if aligned_result == sat and misaligned_result != sat:
        return STATUS_ALINHADO

    if aligned_result != sat and misaligned_result == sat:
        return STATUS_VIOLACAO

    if aligned_result == sat and misaligned_result == sat:
        return STATUS_PARCIAL

    return STATUS_INCONSISTENTE


# =====================================================
# VERIFICAÇÃO
# =====================================================

def verify(filename, verbose=True):

    info = parse_file(filename)

    if verbose:
        print_header(filename)
        print_info(info)

    model = build_model(info)

    #
    # Procuramos um modelo que satisfaça:
    #
    # addr mod align == 0
    #
    aligned_result = check_alignment(model)

    #
    # Procuramos um modelo que satisfaça:
    #
    # addr mod align != 0
    #
    misaligned_result = check_misalignment(model)

    status = classify_result(aligned_result, misaligned_result)

    counterexample = None

    if status in (STATUS_VIOLACAO, STATUS_PARCIAL):
        counterexample = get_counterexample(model, want_zero=False)

    if verbose:

        print("SMT(alinhado):", aligned_result)
        print("SMT(desalinhado):", misaligned_result)
        print()

        if status == STATUS_ALINHADO:
            print("RESULTADO: ALINHADO")

        elif status == STATUS_VIOLACAO:
            print("RESULTADO: VIOLACAO")
            if counterexample:
                print("Contraexemplo:", counterexample)

        elif status == STATUS_PARCIAL:
            print("RESULTADO: PARCIALMENTE ALINHADO (depende de valor simbolico)")
            if counterexample:
                print("Contraexemplo de violacao possivel:", counterexample)

        else:
            print("RESULTADO: INCONSISTENTE")

        print()

    return {
        "filename": filename,
        "status": status,
        "aligned_result": str(aligned_result),
        "misaligned_result": str(misaligned_result),
        "counterexample": counterexample,
    }


# =====================================================
# MAIN
# =====================================================

if __name__ == "__main__":

    if len(sys.argv) != 2:

        print()
        print("Uso:")
        print()
        print("python3 verifier.py arquivo.c")
        print()

        sys.exit(1)

    verify(sys.argv[1])
