import subprocess
import os
import time
import csv

TIMEOUT_SEC = 120
SEA_IMAGE = "seahorn-builder"

def run_cmd(cmd, timeout=TIMEOUT_SEC):
    start = time.time()
    try:
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, timeout=timeout)
        output = result.stdout
    except FileNotFoundError:
        return "NOT_INSTALLED: Docker/SeaHorn nao encontrado.", 0.0
    except subprocess.TimeoutExpired:
        return "TIMEOUT: Tempo limite excedido.", timeout
    end = time.time()
    return output, round(end - start, 4)

def main():
    bench_root = os.path.expanduser(input("Informe o diretório raiz dos benchmarks: ").strip())
    repetitions = int(input("Informe o número de repetições por arquivo: ").strip())

    if not os.path.exists(bench_root):
        print(f"\n[ERRO] Diretório não encontrado: {bench_root}")
        return

    logs_dir = "logs_brutos_seahorn"
    os.makedirs(logs_dir, exist_ok=True)

    results = []
    out_csv = "resultados_brutos_seahorn.csv"

    for root, _, files in os.walk(bench_root):
        c_files = sorted([f for f in files if f.endswith(".c")])
        if not c_files:
            continue

        subdir_name = os.path.basename(root) if os.path.basename(root) else "raiz"
        txt_filename = f"{subdir_name}.txt"
        txt_path = os.path.join(logs_dir, txt_filename)

        print(f"\n[SeaHorn] Processando diretório: {subdir_name}")

        with open(txt_path, "w", encoding="utf-8") as txt_file:
            for file in c_files:
                file_path = os.path.join(root, file)
                rel_path = os.path.relpath(file_path, bench_root)

                cmd = [
                    "sudo", "docker", "run", "--rm",
                    "-v", f"{os.path.abspath(bench_root)}:/bench",
                    SEA_IMAGE,
                    "sea", "pf", f"/bench/{rel_path}",
                ]

                for run_idx in range(1, repetitions + 1):
                    raw_output, t = run_cmd(cmd)

                    header = (
                        f"{'='*80}\n"
                        f"ARQUIVO: {rel_path}\n"
                        f"REPETICAO: {run_idx}/{repetitions}\n"
                        f"TEMPO: {t}s\n"
                        f"{'='*80}\n"
                    )
                    txt_file.write(header + raw_output + "\n\n")

                    print(f"  [{file}] Repetição {run_idx}/{repetitions} -> {t}s")
                    results.append([subdir_name, rel_path, file, run_idx, txt_path, t])

    with open(out_csv, "w", newline="", encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["directory", "path", "file", "run", "log_file_txt", "time_sec"])
        writer.writerows(results)

    print(f"\nResultados salvos em: {out_csv}")
    print(f"Logs agregados salvos na pasta: {logs_dir}/")

if __name__ == "__main__":
    main()
