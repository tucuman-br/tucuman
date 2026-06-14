// parser.c
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────
   Alinhamento natural por tipo
───────────────────────────────────────── */
uint64_t parser_alignment_of(const char *type_name) {
    if (strcmp(type_name, "uint8_t")  == 0) return 1;
    if (strcmp(type_name, "uint16_t") == 0) return 2;
    if (strcmp(type_name, "uint32_t") == 0) return 4;
    if (strcmp(type_name, "uint64_t") == 0) return 8;
    return 0;
}

/* ─────────────────────────────────────────
   Auxiliar — localiza o cast na linha
───────────────────────────────────────── */
static const char *find_cast(const char *line) {
    const char *p = line;
    while (*p) {
        if (*p == '(' && strncmp(p+1, "uint", 4) == 0)
            return p;
        p++;
    }
    return NULL;
}

/* ─────────────────────────────────────────
   Reconhecedores por grupo
───────────────────────────────────────── */

// Grupo A: (uint16_t*)(buf + 1)  — offset == 1
static int try_group_a(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "(char*)") != NULL) return 0;
    if (strstr(cast, "(void*)") != NULL) return 0;
    if (strstr(cast, "offsetof") != NULL) return 0;

    char type[16], base[64];
    uint64_t offset;

    if (sscanf(cast, "(%15[^*]*)(%63[^+]+%llu)",
               type, base, &offset) == 3) {
        if (parser_alignment_of(type) == 0) return 0;
        if (offset != 1) return 0;   // offset != 1 vai para Grupo G

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        out->alignment   = parser_alignment_of(type);
        out->offset      = offset;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_A;
        return 1;
    }
    return 0;
}

// Grupo B: (uint32_t*)((char*)&x + 1)
static int try_group_b(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "(char*)") == NULL) return 0;

    char type[16], base[64];
    uint64_t offset;

    if (sscanf(cast, "(%15[^*]*)((char*)&%63[^+]+%llu)",
               type, base, &offset) == 3) {
        if (parser_alignment_of(type) == 0) return 0;

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        out->alignment   = parser_alignment_of(type);
        out->offset      = offset;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_B;
        return 1;
    }
    return 0;
}

// Grupo C: (uint16_t*)&vec[1]
static int try_group_c(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;

    char type[16], base[64];
    uint64_t index;

    if (sscanf(cast, "(%15[^*]*) &%63[^[][%llu]",
               type, base, &index) == 3) {
        if (parser_alignment_of(type) == 0) return 0;

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        out->alignment   = parser_alignment_of(type);
        out->offset      = index;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_C;
        return 1;
    }
    return 0;
}

// Grupo D: (uint16_t*)(base + offsetof(struct S, b))
static int try_group_d(const char *line, ParsedCase *out) {
    if (strstr(line, "offsetof") == NULL) return 0;

    const char *cast = find_cast(line);
    if (!cast) return 0;

    char type[16], base[64], sname[64], field[64];

    if (sscanf(cast, "(%15[^*]*)(%63[^+]+",
               type, base) != 2) return 0;
    if (parser_alignment_of(type) == 0) return 0;

    const char *p_struct = strstr(cast, "struct ");
    if (!p_struct) return 0;
    p_struct += 7;
    if (sscanf(p_struct, "%63[^,]", sname) != 1) return 0;

    const char *p_comma = strchr(p_struct, ',');
    if (!p_comma) return 0;
    p_comma++;
    while (*p_comma == ' ') p_comma++;
    if (sscanf(p_comma, "%63[^)]", field) != 1) return 0;

    int blen = strlen(base);
    while (blen > 0 && base[blen-1] == ' ') base[--blen] = '\0';

    strncpy(out->ptr_type,    type,  sizeof(out->ptr_type));
    strncpy(out->struct_name, sname, sizeof(out->struct_name));
    strncpy(out->field_name,  field, sizeof(out->field_name));
    out->alignment   = parser_alignment_of(type);
    out->offset      = 0;
    out->offset_kind = OFFSET_CONSTANT;
    out->group       = GROUP_D;
    return 1;
}

// Grupo E: (uint16_t*)(base + i)
/*static int try_group_e(const char *line, ParsedCase *out) {
    if (strstr(line, "offsetof") != NULL) return 0;
    if (strstr(line, "(char*)")  != NULL) return 0;
    if (strstr(line, "(void*)")  != NULL) return 0;

    const char *cast = find_cast(line);
    if (!cast) return 0;

    char type[16], base[64], sym[64];

    if (sscanf(cast, "(%15[^*]*) (%63[^+]+ %63[^)])",
               type, base, sym) == 3) {
        if (sym[0] >= '0' && sym[0] <= '9') return 0;
        if (parser_alignment_of(type) == 0)  return 0;

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        out->alignment   = parser_alignment_of(type);
        out->offset      = 0;
        out->offset_kind = OFFSET_SYMBOLIC;
        out->group       = GROUP_E;
        return 1;
    }
    return 0;
}*/
static int try_group_e(const char *line, ParsedCase *out) {
    if (strstr(line, "offsetof") != NULL) return 0;
    if (strstr(line, "(char*)")  != NULL) return 0;
    if (strstr(line, "(void*)")  != NULL) return 0;

    const char *cast = find_cast(line);
    if (!cast) return 0;

    char type[16], base[64], sym[64];

    if (sscanf(cast, "(%15[^*]*) (%63[^+]+ %63[^)])",
               type, base, sym) == 3) {
        if (sym[0] >= '0' && sym[0] <= '9') return 0;
        if (parser_alignment_of(type) == 0)  return 0;

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        out->alignment       = parser_alignment_of(type);
        out->offset          = 0;
        out->offset_kind     = OFFSET_SYMBOLIC;
        out->sym_upper_bound = 8;   // default — parametrizável
        out->group           = GROUP_E;
        return 1;
    }
    return 0;
}

// Grupo F: (uint16_t*)((char*)p + sizeof(char))
static int try_group_f(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "(char*)") == NULL) return 0;
    if (strstr(cast, "sizeof")  == NULL) return 0;

    char type[16], base[64];

    if (sscanf(cast, "(%15[^*]*)((char*)%63[^+]+",
               type, base) == 2) {
        if (parser_alignment_of(type) == 0) return 0;

        int blen = strlen(base);
        while (blen > 0 && base[blen-1] == ' ') base[--blen] = '\0';

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        strncpy(out->var_name, base, sizeof(out->var_name));
        out->alignment   = parser_alignment_of(type);
        out->offset      = 1;   // sizeof(char) == 1 por definição
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_F;
        return 1;
    }
    return 0;
}

// Grupo G: (uint16_t*)(buf + 3)  — offset != 1
static int try_group_g(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "(char*)") != NULL) return 0;
    if (strstr(cast, "(void*)") != NULL) return 0;
    if (strstr(cast, "offsetof") != NULL) return 0;

    char type[16], base[64];
    uint64_t offset;

    if (sscanf(cast, "(%15[^*]*)(%63[^+]+%llu)",
               type, base, &offset) == 3) {
        if (parser_alignment_of(type) == 0) return 0;
        if (offset == 1) return 0;   // offset == 1 é Grupo A

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        strncpy(out->var_name, base, sizeof(out->var_name));
        out->alignment   = parser_alignment_of(type);
        out->offset      = offset;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_G;
        return 1;
    }
    return 0;
}

// Grupo H: (uint16_t*)&s.b  ou  (uint16_t*)&sp.b
static int try_group_h(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "->") != NULL) return 0;  // seria Grupo J

    char type[16], var[64], field[64];

    if (sscanf(cast, "(%15[^*]*)&%63[^.].%63[^;, )]",
               type, var, field) == 3) {
        if (parser_alignment_of(type) == 0) return 0;

        int is_packed = (strcmp(var, "sp") == 0) ? 1 : 0;

        strncpy(out->ptr_type,   type,  sizeof(out->ptr_type));
        strncpy(out->var_name,   var,   sizeof(out->var_name));
        strncpy(out->field_name, field, sizeof(out->field_name));
        out->alignment   = parser_alignment_of(type);
        out->offset      = 0;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_H;
        out->is_packed   = is_packed;
        return 1;
    }
    return 0;
}

// Grupo I: (uint16_t*)((void*)buf + 1)
static int try_group_i(const char *line, ParsedCase *out) {
    const char *cast = find_cast(line);
    if (!cast) return 0;
    if (strstr(cast, "(void*)") == NULL) return 0;

    char type[16], base[64];
    uint64_t offset;

    if (sscanf(cast, "(%15[^*]*)((void*)%63[^+]+%llu)",
               type, base, &offset) == 3) {
        if (parser_alignment_of(type) == 0) return 0;

        int blen = strlen(base);
        while (blen > 0 && base[blen-1] == ' ') base[--blen] = '\0';

        strncpy(out->ptr_type, type, sizeof(out->ptr_type));
        strncpy(out->var_name, base, sizeof(out->var_name));
        out->alignment   = parser_alignment_of(type);
        out->offset      = offset;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_I;
        return 1;
    }
    return 0;
}

// Grupo J: (uint16_t*)&((struct packed_s*)p)->b
static int try_group_j(const char *line, ParsedCase *out) {
    if (strstr(line, "->") == NULL) return 0;

    const char *cast = find_cast(line);
    if (!cast) return 0;

    char type[16], sname[64], var[64], field[64];

    if (sscanf(cast, "(%15[^*]*)&((struct %63[^*]*)%63[^)])->%63[^;, )]",
               type, sname, var, field) == 4) {
        if (parser_alignment_of(type) == 0) return 0;

        // remove espaço final do sname
        int slen = strlen(sname);
        while (slen > 0 && sname[slen-1] == ' ') sname[--slen] = '\0';

        strncpy(out->ptr_type,    type,  sizeof(out->ptr_type));
        strncpy(out->struct_name, sname, sizeof(out->struct_name));
        strncpy(out->var_name,    var,   sizeof(out->var_name));
        strncpy(out->field_name,  field, sizeof(out->field_name));
        out->alignment   = parser_alignment_of(type);
        out->offset      = 0;
        out->offset_kind = OFFSET_CONSTANT;
        out->group       = GROUP_J;
        out->is_packed   = 1;  // J é sempre packed
        return 1;
    }
    return 0;
}

/* ─────────────────────────────────────────
   Geração de ID sequencial por grupo
───────────────────────────────────────── */
static const char *group_prefix[] = {
    "A","B","C","D","E","F","G","H","I","J"
};
static int group_counter[10] = {0};

static void assign_id(ParsedCase *c) {
    int g = (int)c->group;
    group_counter[g]++;
    snprintf(c->id, sizeof(c->id), "%s%d",
             group_prefix[g], group_counter[g]);
}

/* ─────────────────────────────────────────
   API pública
───────────────────────────────────────── */
#define MAX_CASES 64
#define MAX_LINE  512

ParsedCase *parser_parse_file(const char *filepath, int *count) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "parser: nao foi possivel abrir '%s'\n", filepath);
        *count = 0;
        return NULL;
    }

    ParsedCase *cases = calloc(MAX_CASES, sizeof(ParsedCase));
    if (!cases) { fclose(fp); *count = 0; return NULL; }

    memset(group_counter, 0, sizeof(group_counter));

    char line[MAX_LINE];
    int  found  = 0;
    int  lineno = 0;

    while (fgets(line, sizeof(line), fp) && found < MAX_CASES) {
        lineno++;
        line[strcspn(line, "\n")] = '\0';

        ParsedCase c = {0};
        c.line_number = lineno;
        strncpy(c.raw, line, sizeof(c.raw) - 1);

        // ordem importa: mais específicos primeiro
        int matched =
            try_group_j(line, &c) ||
            try_group_f(line, &c) ||
            try_group_i(line, &c) ||
            try_group_d(line, &c) ||
            try_group_b(line, &c) ||
            try_group_h(line, &c) ||
            try_group_c(line, &c) ||
            try_group_a(line, &c) ||
            try_group_g(line, &c) ||
            try_group_e(line, &c);

        if (matched) {
            assign_id(&c);
            cases[found++] = c;
        }
    }

    fclose(fp);
    *count = found;
    return cases;
}

void parser_free(ParsedCase *cases) {
    free(cases);
}