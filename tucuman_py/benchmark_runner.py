import os
import sys
import csv
import time
import glob

from parser import parse_file
from smt_model import build_model
from smt_model import check_alignment
from smt_model import check_misalignment

from verifier import classify_result
from verifier import STATUS_INCONSISTENTE


# =====================================================
# EXECUÇÃO DE UM ÚNICO CASO
# =====================================================

def run_one(filepath):
    """
    Executa parsing + modelagem SMT + verificacao para um unico
    arquivo .c, medindo o tempo gasto. Erros de parsing/modelagem
    sao capturados e reportados como status ERRO, sem interromper
    o restante do benchmark.
    """

    t0 = time.perf_counter()

    try:

        info = parse_file(filepath)

        model = build_model(info)

        aligned_result = check_alignment(model)

        misaligned_result = check_misalignment(model)

        status = classify_result(aligned_result, misaligned_result)

    except Exception as e:

        status = f"ERRO: {e}"

    t1 = time.perf_counter()

    time_sec = t1 - t0

    return status, time_sec


# =====================================================
# EXECUÇÃO DO BENCHMARK COMPLETO
# =====================================================

def run_benchmark(input_dir, output_csv="results.csv"):

    pattern = os.path.join(input_dir, "*.c")

    files = sorted(glob.glob(pattern))

    if not files:
        raise Exception(f"Nenhum arquivo .c encontrado em '{input_dir}'")

    rows = []

    for filepath in files:

        benchmark_name = os.path.basename(filepath)

        status, time_sec = run_one(filepath)

        rows.append({
            "benchmark": benchmark_name,
            "status": status,
            "time_sec": f"{time_sec:.6f}",
        })

        print(f"{benchmark_name:35s} status={status:25s} time_sec={time_sec:.6f}")

    with open(output_csv, "w", newline="") as f:

        writer = csv.DictWriter(f, fieldnames=["benchmark", "status", "time_sec"])

        writer.writeheader()

        writer.writerows(rows)

    print()
    print(f"Total de casos: {len(rows)}")
    print(f"Resultados salvos em: {output_csv}")

    return rows


# =====================================================
# MAIN
# =====================================================

if __name__ == "__main__":

    if len(sys.argv) < 2:

        print()
        print("Uso:")
        print()
        print("python3 benchmark_runner.py <diretorio_benchmark> [saida.csv]")
        print()
        print("Exemplo:")
        print("python3 benchmark_runner.py benchmark_completo results.csv")
        print()

        sys.exit(1)

    input_dir = sys.argv[1]

    output_csv = sys.argv[2] if len(sys.argv) > 2 else "results.csv"

    run_benchmark(input_dir, output_csv)
