import csv
import glob
import os

from parser import parse_file

from smt_model import (
    concrete_check,
    symbolic_check
)


def classify(filename):

    info = parse_file(filename)

    if info["kind"] == "offsetof":

        return "OK"

    if info["kind"] == "aligned":

        return "OK"

    if info["kind"] == "symbolic":

        result = symbolic_check(
            info["ptr_type"]
        )

        if result.r == 1:

            return "POSSIBLE_VIOLATION"

        return "SAFE"

    result = concrete_check(
        info["offset"],
        info["ptr_type"]
    )

    if result.r == 1:

        return "OK"

    return "VIOLATION"


def run(path):

    files = sorted(

        glob.glob(
            os.path.join(
                path,
                "*.c"
            )
        )

    )

    rows = []

    for f in files:

        rows.append(

            [
                os.path.basename(f),
                classify(f)
            ]

        )

    with open(
        "results.csv",
        "w",
        newline=""
    ) as csvfile:

        writer = csv.writer(csvfile)

        writer.writerow(
            [
                "Benchmark",
                "Result"
            ]
        )

        writer.writerows(rows)

    print()
    print(
        "Arquivo results.csv gerado."
    )


if __name__ == "__main__":

    run("../benchmarks")
