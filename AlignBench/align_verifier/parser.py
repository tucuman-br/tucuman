import re


def parse_file(filename):

    with open(filename, "r") as f:
        code = f.read()

    result = {
        "kind": None,
        "ptr_type": None,
        "offset": None
    }

    # ---------------------------------------
    # tipo do ponteiro
    # ---------------------------------------

    m = re.search(
        r'(uint16_t|uint32_t|uint64_t)\s*\*\s*p',
        code
    )

    if m:
        result["ptr_type"] = m.group(1)

    else:

        m = re.search(
            r'(uint16_t|uint32_t|uint64_t)\s*\*\s*pb',
            code
        )

        if m:
            result["ptr_type"] = m.group(1)

    # ---------------------------------------
    # E1 / E2
    # ---------------------------------------

    if "nondet_uint" in code:

        result["kind"] = "symbolic"

        return result

    # ---------------------------------------
    # offsetof
    # ---------------------------------------

    if "offsetof" in code:

        result["kind"] = "offsetof"

        return result

    # ---------------------------------------
    # C2
    # ---------------------------------------

    if re.search(
        r'\(uint16_t \*\)\s*&x',
        code
    ):

        result["kind"] = "aligned"

        result["offset"] = 0

        return result

    # ---------------------------------------
    # +1
    # ---------------------------------------

    if re.search(
        r'\+\s*1',
        code
    ):

        result["kind"] = "offset"

        result["offset"] = 1

        return result

    # ---------------------------------------
    # vec[1]
    # ---------------------------------------

    if "&vec[1]" in code:

        result["kind"] = "offset"

        result["offset"] = 1

        return result

    return result
