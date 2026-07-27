import re


# =====================================================
# TIPOS SUPORTADOS
# =====================================================

# tamanho == alinhamento natural para todos os tipos usados
# (System V AMD64 ABI / AAPCS64: tipos inteiros tem alinhamento == tamanho)
TYPE_INFO = {
    "char":     (1, 1),
    "uint16_t": (2, 2),
    "uint32_t": (4, 4),
    "uint64_t": (8, 8),
}

ALIGNMENTS = {t: info[1] for t, info in TYPE_INFO.items()}


# =====================================================
# UTILITÁRIOS DE BAIXO NÍVEL
# =====================================================

def detect_ptr_type(code):
    """
    Detecta o tipo alvo do ponteiro verificado, procurando
    o padrao '(<tipo> *)' (o cast que efetivamente produz
    o ponteiro dereferenciado/atribuido).
    """

    for t in ["uint16_t", "uint32_t", "uint64_t"]:
        if re.search(r"\(\s*" + t + r"\s*\*\s*\)", code):
            return t

    raise Exception("Tipo nao suportado (nenhum cast uintN_t* encontrado)")


def detect_alignment(ptr_type):
    return ALIGNMENTS[ptr_type]


def _read_balanced(s, start):
    """
    A partir de s[start] == '(', retorna (texto_entre_parenteses_incluindo_parenteses, indice_apos_fecha).
    """

    assert s[start] == "("

    depth = 0

    for i in range(start, len(s)):

        if s[i] == "(":
            depth += 1

        elif s[i] == ")":
            depth -= 1

            if depth == 0:
                return s[start:i + 1], i + 1

    raise Exception("Parenteses desbalanceados na expressao de cast")


def extract_cast_expr(code, ptr_type):
    """
    Localiza '(<ptr_type> *)' e extrai a expressao C que sofre o cast,
    ex.:
        (uint32_t*)(buf + 1)            -> "buf + 1"
        (uint32_t*)&vec[0]              -> "&vec[0]"
        (uint32_t*)&sp.b                -> "&sp.b"
        (uint32_t*)(base + offsetof(...))-> "base + offsetof(...)"
        (uint32_t*)&((struct S*)p)->b   -> "&((struct S*)p)->b"
    """

    pat = re.compile(r"\(\s*" + re.escape(ptr_type) + r"\s*\*\s*\)")

    m = pat.search(code)

    if not m:
        raise Exception(f"Cast para {ptr_type}* nao encontrado")

    pos = m.end()

    while pos < len(code) and code[pos].isspace():
        pos += 1

    if pos < len(code) and code[pos] == "(":

        expr, _ = _read_balanced(code, pos)

        inner = expr[1:-1].strip()

        return inner

    end = code.index(";", pos)

    return code[pos:end].strip()


# =====================================================
# STRUCTS: parsing e calculo de layout (offsetof real)
# =====================================================

def _detect_pragma_packed_structs(code):
    """
    Retorna um set com os nomes de structs envolvidas por
    #pragma pack(push, 1) ... #pragma pack(pop).
    Usado por parse_struct_defs para complementar a deteccao
    de __attribute__((packed)).
    """

    packed_names = set()

    push_pat   = re.compile(r"#\s*pragma\s+pack\s*\(\s*push\s*,\s*1\s*\)")
    pop_pat    = re.compile(r"#\s*pragma\s+pack\s*\(\s*pop\s*\)")
    struct_pat = re.compile(r"struct\s+(\w+)\s*\{")

    pop_matches = list(pop_pat.finditer(code))

    for push_m in push_pat.finditer(code):

        # pop mais proximo apos o push
        pop_m = next((p for p in pop_matches if p.start() > push_m.end()), None)

        end   = pop_m.start() if pop_m else len(code)

        bloco = code[push_m.end():end]

        for sm in struct_pat.finditer(bloco):
            packed_names.add(sm.group(1))

    return packed_names


def parse_struct_defs(code):
    """
    Encontra definicoes de struct no arquivo, incluindo as variantes:
      - com __attribute__((packed)) logo apos 'struct';
      - envolvidas por #pragma pack(push, 1) ... #pragma pack(pop).

    Retorna: { nome_struct: {"packed": bool, "fields": [(nome, tipo), ...]} }
    """

    pragma_packed = _detect_pragma_packed_structs(code)

    structs = {}

    pat = re.compile(
        r"struct\s+(?:__attribute__\s*\(\(\s*packed\s*\)\)\s+)?(\w+)\s*\{([^}]*)\}",
        re.DOTALL
    )

    for m in pat.finditer(code):

        packed = "__attribute__((packed))" in m.group(0).replace(" ", "") \
            .replace("\n", "") or "__attribute__ ((packed))" in m.group(0)

        # normaliza deteccao de 'packed' ignorando espacos; acrescenta
        # structs envolvidas por #pragma pack(push, 1)
        packed = bool(re.search(r"__attribute__\s*\(\(\s*packed\s*\)\)", m.group(0))) \
            or m.group(1) in pragma_packed

        name = m.group(1)

        body = m.group(2)

        fields = []

        for stmt in body.split(";"):

            stmt = stmt.strip()

            if not stmt:
                continue

            # Array com sizeof: char pad[sizeof(uint32_t) - 1]
            fm_arr_sizeof = re.match(
                r"(char|uint16_t|uint32_t|uint64_t)\s+(\w+)"
                r"\s*\[\s*sizeof\s*\(\s*(\w+)\s*\)\s*([+-]\s*\d+)?\s*\]",
                stmt
            )
            if fm_arr_sizeof:
                elem_type = fm_arr_sizeof.group(1)
                fname     = fm_arr_sizeof.group(2)
                sz_type   = fm_arr_sizeof.group(3)
                adj_str   = (fm_arr_sizeof.group(4) or "").replace(" ", "")
                base_size = TYPE_INFO.get(sz_type, TYPE_INFO.get(elem_type, (1, 1)))[0]
                adj_val   = int(adj_str) if adj_str else 0
                count     = base_size + adj_val
                fields.append((fname, elem_type, count))
                continue

            # Array com literal: char pad[3]
            fm_arr_lit = re.match(
                r"(char|uint16_t|uint32_t|uint64_t)\s+(\w+)\s*\[\s*(\d+)\s*\]",
                stmt
            )
            if fm_arr_lit:
                fields.append((fm_arr_lit.group(2), fm_arr_lit.group(1),
                                int(fm_arr_lit.group(3))))
                continue

            # Campo simples (sem colchetes)
            fm = re.match(r"(char|uint16_t|uint32_t|uint64_t)\s+(\w+)", stmt)

            if fm:
                fields.append((fm.group(2), fm.group(1), 1))

        structs[name] = {"packed": packed, "fields": fields}

    return structs


def compute_field_offset(struct_def, field_name):
    """
    Calcula o offset real do campo, respeitando regras de
    alinhamento/padding de C (structs nao-packed inserem padding
    para que cada campo comece em um endereco multiplo do seu
    proprio alinhamento; structs packed nao inserem padding).
    """

    offset = 0

    for entry in struct_def["fields"]:

        fname, ftype, count = entry

        size, align = TYPE_INFO[ftype]

        if not struct_def["packed"]:

            rem = offset % align

            if rem != 0:
                offset += (align - rem)

        if fname == field_name:
            return offset

        offset += size * count

    raise Exception(f"Campo '{field_name}' nao encontrado na struct")


def find_var_struct_type(code, varname):
    """
    Dado o nome de uma variavel, procura sua declaracao 'struct X varname;'
    para descobrir de qual struct ela e instancia.
    """

    m = re.search(r"struct\s+(\w+)\s*\*?\s*" + re.escape(varname) + r"\s*[;=]", code)

    if m:
        return m.group(1)

    raise Exception(f"Nao foi possivel determinar o tipo struct de '{varname}'")


# =====================================================
# AVALIACAO DA EXPRESSAO DE CAST -> offset / caso simbolico
# =====================================================

def _strip_pointer_casts(expr):

    return re.sub(r"\(\s*(?:char|void|struct\s+\w+)\s*\*\s*\)", "", expr)


def _sum_constant_offset(expr):
    """
    Soma literais inteiros e sizeof(tipo) somados na expressao,
    apos remover casts de ponteiro. Cobre padroes como:
        buf + 1
        (char*)buf + 0
        (void*)buf + 1
        (char*)buf + sizeof(char)
        base + 4

    IMPORTANTE: e estrita de proposito. Cada termo aditivo (separado por
    '+' no nivel superior) precisa ser reconhecido explicitamente como um
    literal inteiro ou como sizeof(<tipo conhecido>); qualquer termo que
    nao se encaixe (ex.: multiplicacao "2*sizeof(x)", deslocamento de bit,
    variavel desconhecida, macro) faz a funcao levantar excecao em vez de
    ignorar silenciosamente o termo -- isso evita calcular um offset
    numericamente errado sem sinalizar erro algum.
    """

    cleaned = _strip_pointer_casts(expr)

    # isola o primeiro identificador base (buf, base, &x, ...) do resto
    # da expressao, que deve ser uma soma de termos aditivos conhecidos
    m = re.match(r"\s*&?\s*\w+\s*(.*)$", cleaned)

    rest = m.group(1) if m else cleaned

    rest = rest.strip()

    if not rest:
        return 0

    total = 0

    for term in re.split(r"(?=[+])", rest):

        term = term.strip()

        if not term:
            continue

        term = term.lstrip("+").strip()

        if not term:
            continue

        tm = re.fullmatch(r"\d+", term)

        if tm:
            total += int(term)
            continue

        sm = re.fullmatch(r"sizeof\s*\(\s*(\w+)\s*\)", term)

        if sm:

            t = sm.group(1)

            if t not in TYPE_INFO:
                raise Exception(f"sizeof de tipo desconhecido: {t}")

            total += TYPE_INFO[t][0]
            continue

        raise Exception(
            f"Termo de offset nao reconhecido: '{term}' "
            f"(expressao completa: '{expr}'). "
            f"Estenda evaluate_expr/_sum_constant_offset para suportar este idioma."
        )

    return total


def evaluate_expr(expr, code, struct_defs, ptr_type):
    """
    Resolve a expressao extraida do cast para um dicionario parcial
    contendo 'kind' e, dependendo do caso, 'offset' ou dados simbolicos.
    """

    # ----------------------------------------------------------------
    # 1) acesso via seta com cast explicito: &((struct X*)p)->campo
    # ----------------------------------------------------------------

    m = re.search(
        r"\(\s*struct\s+(\w+)\s*\*\s*\)\s*\w+\s*\)\s*->\s*(\w+)",
        expr
    )

    if m:

        struct_name, field = m.group(1), m.group(2)

        if struct_name not in struct_defs:
            raise Exception(f"Struct '{struct_name}' nao definida no arquivo")

        sdef = struct_defs[struct_name]

        offset = compute_field_offset(sdef, field)

        return {
            "kind": "packed_field" if sdef["packed"] else "field",
            "offset": offset,
            "packed": sdef["packed"],
            "struct": struct_name,
            "field": field,
        }

    # ----------------------------------------------------------------
    # 2) acesso via seta sem cast explicito: ptr->campo
    # ----------------------------------------------------------------

    m = re.search(r"(\w+)\s*->\s*(\w+)", expr)

    if m:

        ptrvar, field = m.group(1), m.group(2)

        struct_name = None

        dm = re.search(r"struct\s+(\w+)\s*\*\s*" + re.escape(ptrvar) + r"\s*=\s*&\s*(\w+)", code)

        if dm:

            struct_name, objvar = dm.group(1), dm.group(2)

        else:

            struct_name = find_var_struct_type(code, ptrvar)

        sdef = struct_defs[struct_name]

        offset = compute_field_offset(sdef, field)

        return {
            "kind": "packed_field" if sdef["packed"] else "field",
            "offset": offset,
            "packed": sdef["packed"],
            "struct": struct_name,
            "field": field,
        }

    # ----------------------------------------------------------------
    # 3) acesso direto a campo: &var.campo
    # ----------------------------------------------------------------

    m = re.search(r"&\s*(\w+)\s*\.\s*(\w+)", expr)

    if m:

        varname, field = m.group(1), m.group(2)

        struct_name = find_var_struct_type(code, varname)

        sdef = struct_defs[struct_name]

        offset = compute_field_offset(sdef, field)

        return {
            "kind": "packed_field" if sdef["packed"] else "field",
            "offset": offset,
            "packed": sdef["packed"],
            "struct": struct_name,
            "field": field,
        }

    # ----------------------------------------------------------------
    # 4) offsetof(struct X, campo) [+ literal opcional]
    # ----------------------------------------------------------------

    m = re.search(r"offsetof\s*\(\s*struct\s+(\w+)\s*,\s*(\w+)\s*\)", expr)

    if m:

        struct_name, field = m.group(1), m.group(2)

        if struct_name not in struct_defs:
            raise Exception(f"Struct '{struct_name}' nao definida no arquivo")

        sdef = struct_defs[struct_name]

        offset = compute_field_offset(sdef, field)

        remainder = expr[:m.start()] + expr[m.end():]

        offset += _sum_constant_offset(remainder)

        return {
            "kind": "offsetof",
            "offset": offset,
            "packed": sdef["packed"],
            "struct": struct_name,
            "field": field,
        }

    # ----------------------------------------------------------------
    # 5) indexacao de vetor: &vec[N]
    # ----------------------------------------------------------------

    m = re.search(r"&\s*(\w+)\s*\[\s*(\d+)\s*\]", expr)

    if m:

        varname, idx = m.group(1), int(m.group(2))

        tm = re.search(
            r"(char|uint16_t|uint32_t|uint64_t)\s+" + re.escape(varname) + r"\s*\[",
            code
        )

        if not tm:
            raise Exception(f"Nao foi possivel determinar o tipo do vetor '{varname}'")

        elem_type = tm.group(1)

        elem_size = TYPE_INFO[elem_type][0]

        return {
            "kind": "array",
            "offset": idx * elem_size,
        }

    # ----------------------------------------------------------------
    # 6) offset simbolico: variavel vinda de nondet_uint()
    # ----------------------------------------------------------------

    # aceita tanto 'nondet_uint()' quanto variantes com prefixo, ex.:
    # 'VERIFIER_nondet_uint()' (nome real usado no corpus/verifier.h).
    # Tenta primeiro casar com o '% N' colado na propria chamada, ja
    # que e ali (na atribuicao) que o modulo realmente aparece:
    # 'k = VERIFIER_nondet_uint() % 6;' -> o '%' fica apos '()', nao
    # apos 'k'.
    dm_mod = re.search(
        r"(\w+)\s*=\s*\w*nondet_uint\s*\(\s*\)\s*%\s*(\d+)", code
    )

    dm = dm_mod or re.search(r"(\w+)\s*=\s*\w*nondet_uint\s*\(\s*\)", code)

    if dm:

        symvar = dm.group(1)

        if re.search(r"\b" + re.escape(symvar) + r"\b", expr):

            bound = None

            if dm_mod:
                # 'k = nondet() % N' -> valores possiveis em [0, N-1]
                bound = int(dm_mod.group(2))
            else:
                bm = re.search(r"\b" + re.escape(symvar) + r"\s*<\s*(\d+)", code)

                if bm:
                    bound = int(bm.group(1))
                else:
                    bm = re.search(r"(\d+)\s*<\s*" + re.escape(symvar), code)
                    if bm:
                        bound = int(bm.group(1))

            # termo 'symvar * sizeof(tipo)' na propria expressao do cast:
            # o offset e sempre um multiplo de sizeof(tipo), simbolico em k
            mult_type = None

            mm = re.search(
                re.escape(symvar) + r"\s*\*\s*sizeof\s*\(\s*(\w+)\s*\)",
                expr,
            )

            if not mm:
                mm = re.search(
                    r"sizeof\s*\(\s*(\w+)\s*\)\s*\*\s*" + re.escape(symvar),
                    expr,
                )

            # offset constante residual somado ao termo simbolico, ex.:
            # em 'k * sizeof(uint16_t) + 1' o residual e 1 -- e' esse
            # valor que decide se o caso e alinhado (residual multiplo
            # do sizeof) ou desalinhado (residual nao-multiplo).
            residual_offset = None

            if mm:
                mult_type = mm.group(1)

                residual_expr = expr[:mm.start()] + "0" + expr[mm.end():]

                try:
                    residual_offset = _sum_constant_offset(residual_expr)
                except Exception:
                    residual_offset = None

            return {
                "kind": "symbolic",
                "symbolic_var": symvar,
                "symbolic_bound": bound,
                "symbolic_multiple_of": mult_type,
                "symbolic_residual_offset": residual_offset,
            }

    # ----------------------------------------------------------------
    # 7) caso generico: soma de literais/sizeof apos remover casts
    #    cobre: buf+N, base+N, (void*)buf+N, (char*)buf+N,
    #           (char*)&x+N, &x (offset 0)
    # ----------------------------------------------------------------

    offset = _sum_constant_offset(expr)

    return {
        "kind": "offset",
        "offset": offset,
    }


# =====================================================
# PARSER PRINCIPAL
# =====================================================

def parse_file(filename):

    with open(filename, "r") as f:
        code = f.read()

    ptr_type = detect_ptr_type(code)

    alignment = detect_alignment(ptr_type)

    struct_defs = parse_struct_defs(code)

    expr = extract_cast_expr(code, ptr_type)

    partial = evaluate_expr(expr, code, struct_defs, ptr_type)

    result = {
        "filename": filename,
        "ptr_type": ptr_type,
        "alignment": alignment,
        "packed": partial.get("packed", False),
    }

    result.update(partial)

    return result
