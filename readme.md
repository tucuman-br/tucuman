# Tucuman

**Tucuman** é uma ferramenta especializada de **Verificação Formal** para detectar **violações de alinhamento de memória em programas escritos em C**, por meio da **inferência automática** de propriedades de alinhamento e da verificação baseada em SMT utilizando o solver **Z3**.

Diferentemente dos verificadores de propósito geral, o Tucuman infere automaticamente as restrições de alinhamento diretamente da estrutura sintática do programa, eliminando a necessidade de inserir *assertions* ou outras anotações manuais.

Este projeto acompanha a pesquisa desenvolvida no Programa de Pós-Graduação em Engenharia Elétrica da Universidade Federal do Amazonas (UFAM).

---

## Motivação

Violações de alinhamento de memória constituem uma importante fonte de comportamento indefinido em programas escritos em C. Embora ferramentas tradicionais de verificação formal sejam capazes de detectar propriedades como:

- desreferenciamento de ponteiros nulos;
- estouro de buffer (*buffer overflow*);
- uso de memória liberada (*use-after-free*);
- acessos inválidos à memória;

a propriedade de **alinhamento de memória** normalmente só é verificada quando explicitamente fornecida pelo usuário ou quando faz parte do modelo interno da ferramenta.

O Tucuman foi desenvolvido para preencher essa lacuna, inferindo automaticamente propriedades de alinhamento e traduzindo-as em restrições SMT.

---

# Principais funcionalidades

- Inferência automática de propriedades de alinhamento;
- Reconhecimento de padrões sintáticos da linguagem C;
- Geração automática de fórmulas SMT utilizando BitVectors;
- Integração com o solver Z3;
- Detecção de acessos alinhados e desalinhados;
- Dispensa a inserção manual de *assertions*;
- Classificação dos programas em:
  - ✅ OK
  - ❌ VIOLATION
  - ⚠️ UNKNOWN

---

# Estrutura do projeto

```text
.
├── README.md
├── benchmark
│   ├── benchmark_com_assertions_com_alinhamento_v3
│   ├── benchmark_com_assertions_sem_alinhamento_v3
│   ├── benchmark_sem_assertions_com_alinhamento_v3
│   └── benchmark_sem_assertions_sem_alinhamento_v3
├── tucuman_c
│   ├── README.md
│   ├── benchmark_relatorio.csv
│   ├── benchmark_runner
│   ├── benchmark_runner.c
│   ├── main.c
│   ├── parser.c
│   ├── parser.h
│   ├── smt_model.c
│   ├── smt_model.h
│   ├── test_input.c
│   ├── tucuma.exe
│   ├── tucuman
│   ├── verifier.c
│   └── verifier.h
└── tucuman_py
    ├── __pycache__
    ├── benchmark_runner.py
    ├── parser.py
    ├── readme.md
    ├── smt_model.py
    ├── tucuman.py
    └── verifier.py
```

---

# Implementações

## 🐍 Versão em Python (Estável)

A implementação em Python corresponde à versão de referência utilizada nos experimentos apresentados no artigo científico.

### Recursos

- Parser completo;
- Inferência automática de alinhamento;
- Geração de fórmulas SMT;
- Integração com o solver Z3;
- Suporte completo ao benchmark.

**Status:** ✅ Estável

---

## ⚙️ Versão em C (Em desenvolvimento)

Uma implementação nativa em linguagem C encontra-se atualmente em desenvolvimento.

### Objetivos

- Melhor desempenho;
- Menor dependência de bibliotecas externas;
- Executável independente;
- Integração simplificada com fluxos de verificação.

**Status:** 🚧 Experimental

---

# Benchmark

O repositório inclui um benchmark original desenvolvido especificamente para avaliação de ferramentas de verificação de alinhamento de memória.

## Características

- 120 programas escritos em C;
- 10 grupos de testes (A–J);
- Casos alinhados e desalinhados;
- Tipos de 16, 32 e 64 bits.

Os programas contemplam padrões recorrentes da linguagem C, incluindo:

- Aritmética de ponteiros;
- Deslocamentos constantes;
- Deslocamentos simbólicos;
- Vetores;
- Estruturas (`struct`);
- Estruturas empacotadas (`packed`);
- Uso de `offsetof`;
- Conversões de ponteiros (*casts*);
- Acessos sensíveis ao alinhamento.

---

# Arquitetura da ferramenta

O Tucuman executa as seguintes etapas:

1. Leitura do programa C;
2. Identificação dos padrões sintáticos;
3. Inferência automática das propriedades de alinhamento;
4. Geração das restrições SMT;
5. Resolução utilizando o solver Z3;
6. Classificação do programa.

---

# Requisitos

## Versão Python

- Python 3.10+
- Z3 Solver

Instalação:

```bash
pip install z3-solver
```

---

## Versão C

- GCC ou Clang
- API C do Z3
- CMake (opcional)

---

# Execução

## Python

```bash
python tucuman.py programa.c
```

## C

```bash
./tucuman programa.c
```

---

# Contribuições científicas

O projeto apresenta as seguintes contribuições:

- Desenvolvimento de um verificador especializado para alinhamento de memória;
- Inferência automática de propriedades de alinhamento;
- Geração automática de restrições SMT;
- Benchmark original para avaliação de verificadores de alinhamento;
- Comparação experimental com:
  - CBMC;
  - ESBMC;
  - CPAchecker;
  - KLEE;
  - SeaHorn;
  - UBSan.

---

# Publicações

Caso utilize este projeto em trabalhos acadêmicos, cite:

> Antônio Carlos de Castro Silva, Bruna Tatiane Farias Ferreira e Wesley Victtorino.
>
> **Tucuman: Inferência Automática de Propriedades de Alinhamento de Memória para Verificação Formal de Programas C Baseada em SMT.**

---

# DOI

A versão arquivada deste projeto encontra-se disponível no Zenodo.

> **DOI:** *(https://doi.org/10.5281/zenodo.21385206)*

---

# Licença

Este projeto é distribuído sob a licença **MIT**.

Consulte o arquivo **LICENSE** para mais informações.

---

# Autores

- **Antônio Carlos de Castro Silva**
- **Wesley Victtorino**

---

# Como contribuir

Contribuições são bem-vindas.

Você pode colaborar de diversas formas:

- Relatando problemas (*Issues*);
- Corrigindo erros;
- Propondo melhorias;
- Expandindo o benchmark;
- Implementando novos padrões de alinhamento;
- Otimizando o parser;
- Melhorando a documentação.

---

# Agradecimentos

Este projeto foi desenvolvido no âmbito do **Programa de Pós-Graduação em Engenharia Elétrica (PPGEE)** da **Universidade Federal do Amazonas (UFAM)**, como parte da pesquisa em Verificação Formal de Programas C utilizando SMT.
Os autores agradecem ao Prof. Lucas Carvalho Cordeiro pela orientação no âmbito da disciplina PGENE549 — Verificação de Software e Sistemas do **Programa de Pós-Graduação em Engenharia Elétrica (PPGEE)** da **Universidade Federal do Amazonas (UFAM)**.
---

## Contato

Em caso de dúvidas, sugestões ou relatos de problemas, utilize a área de **Issues** deste repositório no GitHub.
