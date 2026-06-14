import csv
import os
import subprocess
from pathlib import Path


# =====================================================
# CONFIGURAÇÃO
# =====================================================

BENCHMARK_DIR = "../benchmarks"

OUTPUT_CSV = "results.csv"


# =====================================================
# EXECUTA UM BENCHMARK
# =====================================================

def run_benchmark(filename):

    result = subprocess.run(
        [
            "python3",
            "verifier.py",
            filename
        ],
        capture_output=True,
        text=True
    )

    output = result.stdout

    verdict = "UNKNOWN"

    if "RESULTADO: ALINHADO" in output:
        verdict = "ALINHADO"

    elif "RESULTADO: VIOLACAO" in output:
        verdict = "VIOLACAO"

    elif "RESULTADO: PARCIALMENTE_ALINHADO" in output:
        verdict = "PARCIALMENTE_ALINHADO"

    return verdict


# =====================================================
# MAIN
# =====================================================

def main():

    benchmark_path = Path(
        BENCHMARK_DIR
    )

    files = sorted(
        benchmark_path.glob("*.c")
    )

    rows = []

    for f in files:

        print(
            f"Executando {f.name}..."
        )

        verdict = run_benchmark(
            str(f)
        )

        rows.append(
            [
                f.name,
                verdict
            ]
        )

    with open(
        OUTPUT_CSV,
        "w",
        newline=""
    ) as csvfile:

        writer = csv.writer(
            csvfile
        )

        writer.writerow(
            [
                "Benchmark",
                "Resultado"
            ]
        )

        writer.writerows(rows)

    print()
    print(
        f"CSV gerado: {OUTPUT_CSV}"
    )


if __name__ == "__main__":
    main()
