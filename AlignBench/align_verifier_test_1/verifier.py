import sys

from parser import parse_file
from smt_model import verify_alignment

def main():

    if len(sys.argv) != 2:

        print(
            "Uso: python verifier.py arquivo.c"
        )
        return

    filename = sys.argv[1]

    info = parse_file(filename)

    print("\n=== PROGRAMA ANALISADO ===\n")

    print("Array      :", info["array_name"])
    print("Tipo       :", info["type"])
    print("Offset     :", info["offset"])
    print("Alinhamento:", info["alignment"])

    result = verify_alignment(
        info["offset"],
        info["alignment"]
    )

    print("\n=== RESULTADO ===\n")

    if str(result) == "sat":

        print("Nenhuma violação encontrada")

    else:

        print("VIOLAÇÃO DE ALINHAMENTO")

        print(
            f"Ponteiro do tipo {info['type']}"
        )

        print(
            f"Offset = {info['offset']}"
        )

        print(
            f"Alinhamento exigido = {info['alignment']}"
        )

if __name__ == "__main__":
    main()
