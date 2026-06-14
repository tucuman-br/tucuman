import os
import sys

from z3 import sat

from parser import parse_file
from smt_model import build_model
from smt_model import check_alignment
from smt_model import check_misalignment


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

    print(
        "Alinhamento:",
        info["alignment"]
    )

    print(
        "Caso:",
        info["kind"]
    )

    if "offset" in info:

        print(
            "Offset:",
            info["offset"]
        )

    if info.get("packed", False):

        print(
            "Struct packed: SIM"
        )

    print()


# =====================================================
# VERIFICAÇÃO
# =====================================================

def verify(filename):

    info = parse_file(filename)

    print_header(filename)

    print_info(info)

    model = build_model(info)

    #
    # Procuramos um modelo que satisfaça:
    #
    # addr mod align == 0
    #
    aligned_result = check_alignment(
        model
    )

    #
    # Procuramos um modelo que satisfaça:
    #
    # addr mod align != 0
    #
    misaligned_result = check_misalignment(
        model
    )

    print(
        "SMT(alinhado):",
        aligned_result
    )

    print(
        "SMT(desalinhado):",
        misaligned_result
    )

    print()

    # -------------------------------------
    # classificação
    # -------------------------------------

    if (
        aligned_result == sat and
        misaligned_result != sat
    ):

        print(
            "RESULTADO: ALINHADO"
        )

    elif (
        aligned_result != sat and
        misaligned_result == sat
    ):

        print(
            "RESULTADO: VIOLACAO"
        )

    elif (
        aligned_result == sat and
        misaligned_result == sat
    ):

        print(
            "RESULTADO: PARCIALMENTE ALINHADO"
        )

    else:

        print(
            "RESULTADO: INCONSISTENTE"
        )

    print()


# =====================================================
# MAIN
# =====================================================

if __name__ == "__main__":

    if len(sys.argv) != 2:

        print()
        print(
            "Uso:"
        )
        print()

        print(
            "python3 verifier.py arquivo.c"
        )
        print()

        sys.exit(1)

    verify(
        sys.argv[1]
    )
