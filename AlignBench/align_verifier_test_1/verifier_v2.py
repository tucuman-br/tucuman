from parser_v2 import parse_file

from smt_model_v2 import (
    check_alignment,
    symbolic_offset_without_alignment,
    symbolic_offset_with_alignment
)

from memory_layout import (
    compute_struct_layout
)

# =====================================================
# VERIFIER
# =====================================================

def verify(filename):

    ast = parse_file(filename)

    print()
    print("===================================")
    print("ARQUIVO:", filename)
    print("===================================")

    # -------------------------------------------------
    # STRUCTS
    # -------------------------------------------------

    if ast["structs"]:

        print()
        print("STRUCTS:")

        for struct in ast["structs"]:

            layout = compute_struct_layout(
                struct
            )

            print()

            print(
                "struct",
                struct.name
            )

            for field, offset in layout.items():

                print(
                    f"  {field:10s} -> {offset}"
                )

    # -------------------------------------------------
    # OFFSETOF
    # -------------------------------------------------

    if ast["offsetofs"]:

        print()
        print("OFFSETOF:")

        for off in ast["offsetofs"]:

            print(
                off.struct_name,
                ".",
                off.field_name
            )

    # -------------------------------------------------
    # CASTS
    # -------------------------------------------------

    if ast["casts"]:

        print()
        print("CASTS:")

        for cast in ast["casts"]:

            result = check_alignment(
                cast.offset,
                cast.ptr_type
            )

            print()

            print(
                "Pointer:",
                cast.ptr_name
            )

            print(
                "Type:",
                cast.ptr_type
            )

            print(
                "Offset:",
                cast.offset
            )

            if str(result) == "sat":

                print(
                    "Status: OK"
                )

            else:

                print(
                    "Status: ALIGNMENT VIOLATION"
                )

# =====================================================
# TESTES E1 / E2
# =====================================================

def run_symbolic_tests():

    print()
    print("===================================")
    print("E1")
    print("===================================")

    print(
        symbolic_offset_without_alignment()
    )

    print()
    print("===================================")
    print("E2")
    print("===================================")

    print(
        symbolic_offset_with_alignment(4)
    )

# =====================================================
# MAIN
# =====================================================

import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:

        print(
            "Uso: python3 verifier_v2.py arquivo.c"
        )
        sys.exit(1)

    verify(sys.argv[1])

    run_symbolic_tests()
