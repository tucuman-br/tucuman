# Tucumã - Verificador Formal de Alinhamento de Memória para Programas C usando Z3

## Visão Geral

O **Tucumã** é um protótipo de verificação formal desenvolvido para detectar violações de alinhamento de memória em programas escritos em C utilizando o solver SMT Z3.

Enquanto verificadores tradicionais frequentemente modelam a memória como uma sequência plana de bytes (*byte-level memory model*), o Tucumã introduz explicitamente restrições de alinhamento definidas pelo padrão ISO C, permitindo identificar acessos desalinhados que podem passar despercebidos em modelos convencionais.

O projeto foi desenvolvido no contexto da disciplina **PGENE549 – Verificação de Software e Sistemas** do Programa de Pós-Graduação em Engenharia Elétrica (PPGEE) da Universidade Federal do Amazonas (UFAM).

---

## Motivação

Em C, um ponteiro para um tipo `T` deve apontar para um endereço compatível com o requisito de alinhamento desse tipo.

Por exemplo:

```c
char buf[4];
uint16_t *p = (uint16_t *)(buf + 1);
uint16_t x = *p;
```

O ponteiro `p` aponta para um endereço ímpar, violando o requisito de alinhamento de 2 bytes exigido por `uint16_t`.

Embora arquiteturas como x86-64 geralmente permitam esse acesso, o padrão C classifica essa operação como **Undefined Behavior (UB)**.

O objetivo do Tucumã é detectar automaticamente esse tipo de violação por meio de restrições SMT.

---

## Principais Características

- Modelagem formal de memória baseada em SMT.
- Verificação automática de alinhamento de ponteiros.
- Suporte a:
  - Offsets constantes;
  - Estruturas (`struct`) com padding;
  - Casts entre tipos;
  - Vetores de bytes;
  - Offsets simbólicos;
  - Assertivas explícitas de alinhamento.
- Geração de contraexemplos para violações encontradas.
- Implementado em Python utilizando o solver Z3.

---

## Arquitetura

O projeto é composto pelos seguintes módulos:

### parser.py

Responsável por analisar o programa de entrada e identificar:

- Casts de ponteiros;
- Offsets constantes;
- Uso de `offsetof`;
- Variáveis simbólicas (`nondet_uint()`).

---

### smt_model.py

Constrói as fórmulas SMT correspondentes ao modelo de memória.

Implementa:

- Modelo byte-level;
- Restrições explícitas de alinhamento;
- Tradução das propriedades para Z3.

---

### verifier.py

Executa a verificação formal.

Possíveis resultados:

| Resultado | Significado |
|------------|------------|
| OK | Nenhuma violação encontrada |
| VIOLAÇÃO | Alinhamento inválido |
| POSSÍVEL VIOLAÇÃO | Existe ao menos um contraexemplo |
| FALHA DE ASSERTIVA | Propriedade especificada não é garantida |

---

### benchmark_runner.py

Executa automaticamente todos os benchmarks e gera relatórios consolidados.

Saída:

```csv
benchmark,resultado,tempo,detalhes
A1,VIOLACAO,0.002,...
A2,VIOLACAO,0.001,...
...
```

---

## Modelo Formal

A contribuição central do Tucumã consiste na seguinte restrição SMT:

```text
Aligned(p,T) ≡ (addr(p) mod align(T)) = 0
```

Implementação em Z3:

```python
def aligned(addr, n):
    return URem(addr, BitVecVal(n, 64)) == BitVecVal(0, 64)
```

A violação ocorre quando não existe modelo que satisfaça simultaneamente:

- As restrições do programa;
- As regras de alinhamento.

---

## Benchmark Experimental

O benchmark utilizado contém dez programas organizados em cinco grupos.

| Grupo | Descrição |
|---------|---------|
| A | Offsets constantes |
| B | Structs e padding |
| C | Casts explícitos |
| D | Vetores de bytes |
| E | Offsets simbólicos |

### Exemplos

#### Grupo A

```c
uint16_t *p = (uint16_t *)(buf + 1);
```

#### Grupo B

```c
struct S {
    char a;
    uint16_t b;
};
```

#### Grupo E

```c
unsigned i = nondet_uint();
```

---

## Instalação

### Requisitos

- Python 3.10+
- Z3 Solver

### Instalar dependências

```bash
pip install z3-solver
```

---

## Execução

### Verificar um benchmark

```bash
python verifier.py benchmarks/A1.c
```

### Executar todos os benchmarks

```bash
python benchmark_runner.py
```

---

## Exemplo de Saída

```text
[Benchmark A1]

Tipo analisado: uint16_t
Endereço: base + 1
Alinhamento requerido: 2

Resultado: VIOLAÇÃO

Motivo:
(base + 1) mod 2 ≠ 0
```

---

## Comparação com Ferramentas Existentes

| Benchmark | Esperado | CBMC | ESBMC | Tucumã |
|------------|------------|------------|------------|------------|
| A1 | Violação | OK | Violação | Violação |
| A2 | Violação | OK | Violação | Violação |
| A3 | Violação | OK | Violação | Violação |
| B1 | Violação | OK | Violação | Violação |
| B2 | OK | OK | OK | OK |
| C1 | Violação | OK | - | Violação |
| C2 | OK | OK | OK | OK |
| D1 | Violação | OK | Violação | Violação |
| E1 | Possível Violação | OK | Violação | Possível Violação |
| E2 | Falha de Assertiva | - | - | Falha de Assertiva |

---

## Contribuições Científicas

O trabalho demonstra que a simples inclusão da restrição:

```text
addr(p) mod align(T) = 0
```

é suficiente para capturar formalmente violações de alinhamento que podem não ser detectadas por modelos byte-level tradicionais.

O Tucumã complementa verificadores existentes, fornecendo uma camada adicional de verificação focada em conformidade com as regras de alinhamento definidas pelo padrão C.

---

## Em desenvolvimento

- Integração com KLEE.
- Integração com SeaHorn.
- Suporte completo a:
  - unions;
  - bit-fields;
  - layouts complexos de memória.
- Avaliação em arquiteturas:
  - ARMv6;
  - RISC-V;
  - SPARC.
- Estudos de escalabilidade em programas reais.

---

## Autores

- Antônio Carlos de Castro Silva
- Bruna Tatiane Farias Ferreira
- Wesley Vitorino Teixeira

Programa de Pós-Graduação em Engenharia Elétrica (PPGEE)  
Universidade Federal do Amazonas (UFAM)

---

## Licença

Este projeto foi desenvolvido para fins acadêmicos e de pesquisa.
