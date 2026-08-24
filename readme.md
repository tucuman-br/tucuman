# Tucuman

**Tucuman** é um protótipo especializado de **Verificação Formal** para detectar **violações de alinhamento de memória em programas escritos em C**, por meio da **inferência automática** de propriedades de alinhamento e da verificação baseada em SMT utilizando o solver **Z3**.

Diferentemente dos verificadores de propósito geral, o Tucuman infere automaticamente as restrições de alinhamento diretamente da estrutura sintática do programa, eliminando a necessidade de inserir *assertions* ou outras anotações manuais.

O Tucuman deve ser entendido como uma ferramenta complementar aos verificadores de propósito geral.

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
  - OK
  - PARCIALMENTE ALINHADO
  - VIOLATION
  - NKNOWN

---

# Estrutura do projeto

```text
.
tucuman
├── LICENSE
├── benchmark
│   ├── benchmark_com_assertions_alinhamento_natural_v4
│   ├── benchmark_com_assertions_com_alinhamento_explicito_v4
│   ├── benchmark_sem_assertions_alinhamento_natural_v4
│   ├── benchmark_sem_assertions_com_alinhamento_explicito_v4
│   ├── byte_level_memory.c
│   ├── byte_level_memory.py
│   └── validacao_experimental.c
├── readme.md
├── scripts_execucao
│   ├── dockerfile                    ← imagem Docker com todas as dependências
│   ├── environment.yml               ← ambiente Conda reprodutível
│   ├── logs_brutos_cbmc
│   ├── logs_brutos_cpachecker
│   ├── logs_brutos_esbmc
│   ├── logs_brutos_klee
│   ├── logs_brutos_seahorn
│   ├── logs_brutos_tucuman
│   ├── readme.md
│   ├── requirements.txt              ← dependências Python com versões fixadas
│   ├── run_cbmc.py
│   ├── run_cpachecker.py
│   ├── run_esbmc.py
│   ├── run_klee.py
│   ├── run_seahorn.py
│   └── run_tucuman.py
├── tucuman_c                         ← implementação C do tucuman (em desemvolvimento)
└── tucuman_py                        ← implementação Python do tucuman
    ├── parser.py
    ├── run_tucuman.py
    ├── smt_model.py
    ├── tucuman.py
    └── tucuman_runner.py

```

---

# Implementações

## Versão em Python (Estável)

A implementação em Python corresponde à versão de referência utilizada nos experimentos apresentados no artigo científico.

### Recursos

- Parser completo;
- Inferência automática de alinhamento;
- Geração de fórmulas SMT;
- Integração com o solver Z3;
- Suporte completo ao benchmark.

**Status:** ✅ Estável

---

### Versão em C (Em desenvolvimento)

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

- 240 programas escritos em C;
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

Nota:
O arquivo readme.md em tucuman/scripts_execucao/ contém os scripts de automação necessários para reproduzir a avaliação experimental dos
 verificadores formais comparados neste trabalho.

---

# Contribuições científicas

O projeto apresenta as seguintes contribuições:

- Desenvolvimento de um protótipo-verificador especializado para alinhamento de memória;
- Inferência automática de propriedades de alinhamento;
- Geração automática de restrições SMT;
- Benchmark original para avaliação de verificadores de alinhamento;
- Comparação experimental com:
  - CBMC;
  - ESBMC;
  - CPAchecker;
  - KLEE;
  - SeaHorn;

---

# Publicações

Caso utilize este projeto em trabalhos acadêmicos, cite:

> Antônio Carlos de Castro Silva e Wesley Vitorino Teixeira.
>
> **Tucuman: Inferência Automática de Propriedades de Alinhamento de Memória para Verificação Formal de Programas C Baseada em SMT.**

@article{teixeira2026tucuman,
  title  = {Verificação Formal de Modelos de Memória Alinhada em
             Programas C usando o Solver Z3},
  author = {Silva, Antônio Carlos de Castro and
            Teixeira, Wesley Vitorino},
  school = {PPGEE -- Universidade Federal do Amazonas},
  year   = {2026}
  orcid: https://orcid.org/0000-0000-0000-0000

---

# DOI

A versão arquivada deste projeto encontra-se disponível no Zenodo.

> **DOI:** *(https://doi.org/10.5281/zenodo.21424718)*

---

# Licença

Este projeto é distribuído sob a licença **MIT**.

Consulte o arquivo **LICENSE** para mais informações.

---

# Autores

- **Antônio Carlos de Castro Silva**
- **Wesley Vitorino Teixeira**

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
