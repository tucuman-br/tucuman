import os
import sys
from z3 import sat


from parser import parse_file

from smt_model import (
    concrete_check,
    symbolic_check
)


def verify(filename):

    info = parse_file(filename)

    name = os.path.basename(filename)

    print()
    print("=" * 50)
    print(name)
    print("=" * 50)

    print()

    print(
        "Tipo:",
        info["ptr_type"]
    )

    print(
        "Caso:",
        info["kind"]
    )

    print()

    # ------------------------------------
    # offsetof
    # ------------------------------------

    if info["kind"] == "offsetof":

        print("Resultado: OK")
        print(
            "offsetof produz offset alinhado"
        )

        return

    # ------------------------------------
    # alinhado
    # ------------------------------------

    if info["kind"] == "aligned":

        print("Resultado: OK")

        return

    # ------------------------------------
    # simbólico
    # ------------------------------------

    if info["kind"] == "symbolic":

        result = symbolic_check(
            info["ptr_type"]
        )

        print()

        if result == sat:

            print(
                "Resultado: POSSIVEL VIOLACAO"
            )

            print(
                "Existe i tal que ponteiro fica desalinhado"
            )

        else:

            print(
                "Resultado: SEGURO"
            )

        return

    # ------------------------------------
    # concreto
    # ------------------------------------

    result = concrete_check(
        info["offset"],
        info["ptr_type"]
    )

    print(
        "Offset:",
        info["offset"]
    )

    print()

    if result == sat:

        print(
            "Resultado: OK"
        )

    else:

        print(
            "Resultado: VIOLACAO"
        )


if __name__ == "__main__":

    if len(sys.argv) != 2:

        print(
            "Uso:"
        )

        print(
            "python3 verifier.py arquivo.c"
        )

        sys.exit(1)

    verify(sys.argv[1])
