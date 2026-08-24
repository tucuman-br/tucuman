#tucuman — Verificação Formal de Alinhamento de Memória em Programas C

Repositório do experimento comparativo entre verificadores formais para detecção de violações de alinhamento de memória em programas C, desenvolvido no âmbito do PPGEE/UFAM.

---

Estrutura do repositório
```
.
tucuman
├── benchmark/
│   ├── benchmark_com_assertions_alinhamento_natural_v4/
│   ├── benchmark_com_assertions_com_alinhamento_explicito_v4/
│   ├── benchmark_sem_assertions_alinhamento_natural_v4/
│   ├── benchmark_sem_assertions_com_alinhamento_explicito_v4/
│   ├── byte_level_memory.c
│   ├── byte_level_memory.py
│   └── validacao_experimental.c
├── scripts_execucao/
|   ├── dockerfile                   ← imagem Docker com todas as dependências
|   ├── environment.yml	              ← ambiente Conda reprodutível
|   ├── logs_brutos_cbmc
|   ├── logs_brutos_cpachecker
|   ├── logs_brutos_esbmc
|   ├── logs_brutos_klee
|   ├── logs_brutos_seahorn
|   ├── logs_brutos_tucuman
|   ├── readme.md
|   ├── requirements.txt             ← dependências Python com versões fixadas
|   ├── run_cbmc.py
|   ├── run_cpachecker.py
|   ├── run_esbmc.py
|   ├── run_klee.py
|   ├── run_seahorn.py
|   └── run_tucuman.py
├── tucuman_c/                       ← implementação C do tucuman (em desemvolvimento)
├── tucuman_py/                      ← implementação Python do tucuman
│   └── tucuman.py
└── readme.md
```
---
## Reprodução do Experimento

Para reproduzir os experimentos, execute os scripts de cada verificador individualmente localizados no diretório `scripts_execucao/`. 

Ao executar qualquer um dos scripts, o sistema solicitará interativamente os caminhos necessários (como o diretório raiz do benchmark e executáveis/propriedades) e o número de repetições por arquivo.

### Executores Disponíveis

| Verificador | Script de Execução | Logs Gerados | Relatório CSV |
| :--- | :--- | :--- | :--- |
| **CBMC** | `python3 scripts_execucao/run_cbmc.py` | `logs_brutos_cbmc/` | `resultados_brutos_cbmc.csv` |
| **ESBMC** | `python3 scripts_execucao/run_esbmc.py` | `logs_brutos_esbmc/` | `resultados_brutos_esbmc.csv` |
| **CPAchecker** | `python3 scripts_execucao/run_cpachecker.py` | `logs_brutos_cpachecker/` | `resultados_brutos_cpachecker.csv` |
| **KLEE** | `python3 scripts_execucao/run_klee.py` | `logs_brutos_klee/` | `resultados_brutos_klee.csv` |
| **SeaHorn** | `python3 scripts_execucao/run_seahorn.py` | `logs_brutos_seahorn/` | `resultados_brutos_seahorn.csv` |
| **Tucuman** | `python3 scripts_execucao/run_tucuman.py` | `logs_brutos_tucuman/` | `resultados_brutos_tucuman.csv` |

---

### Reprodução via Conda (Recomendado)

```bash
# 1. Clona o repositório e acesse a pasta raiz
git clone <url-do-repositorio>
cd tucuman

# 2. Cria e ativa o ambiente virtual
conda env create -f environment.yml
conda activate tucuman

# 3. Executa o script do verificador desejado (exemplo: CBMC)
python3 scripts_execucao/run_cbmc.py


### Reprodução via pip / venv

# 1. Clona o repositório e acesse a pasta raiz
git clone <url-do-repositorio>
cd tucuman

# 2. Instala as dependências necessárias
pip install -r requirements.txt

# 3. Executa o script do verificador desejado (exemplo: Tucuman)
python3 scripts_execucao/run_tucuman.py

### Reprodução via Docker

Para ferramentas que utilizam imagens Docker encapsuladas (como KLEE ou SeaHorn), certifique-se de que o serviço do Docker está ativo no ambiente hospedeiro antes de rodar os scripts:

# Execução do KLEE via Docker runner
python3 scripts_execucao/run_klee.py

# Execução do SeaHorn via Docker runner
python3 scripts_execucao/run_seahorn.py


### Estrutura dos Resultados

Ao finalizar a execução de um script:

Logs agregados por diretório: Um único arquivo .txt contendo a saída bruta sequencial de todos os benchmarks do diretório será gerado no diretório logs_brutos_<ferramenta>/.

Índice Mapeado: Um arquivo .csv correspondente (resultados_brutos_<ferramenta>.csv) mapeará o tempo de execução, caminho do arquivo .c e o ponteiro para o log .txt gerado.


---
# Pré-requisitos adicionais (além do Python/Z3)

Verificadores Prontos (Via Conda ou Docker do Projeto): Tucuman, CBMC e CPAchecker.

Verificadores que Exigem Docker no Host: KLEE (docker pull klee/klee) e SeaHorn (docker pull seahorn-builder).

Verificador Nativo: ESBMC (deve ser baixado e o caminho informado no prompt do script).

CBMC
```bash
# Ubuntu/Debian
sudo apt install cbmc

# verificar instalação
cbmc --version   # testado com 6.6.0
```
CPAchecker
Baixe a versão Unix em: https://cpachecker.sosy-lab.org/download.php
```bash
tar -xzf CPAchecker-4.1-unix.tar.gz -C /opt/
export CPACHECKER_DIR=/opt/CPAchecker-4.1-unix
```
SeaHorn (via Docker)
```bash
git clone https://github.com/seahorn/seahorn.git
cd seahorn && docker build -t seahorn-builder .
```
> **Nota:** O SeaHorn apresenta limitação estrutural para este benchmark — não suporta `uintptr_t` em modo `-m32` e não detecta violações de alinhamento via aritmética de ponteiros. Está documentado no artigo como caso de contraste.
KLEE (via Docker)
```bash
docker pull klee/klee
```
ESBMC (Windows)

Baixe em: https://github.com/esbmc/esbmc/releases (testado com 8.2.0)
Execute via `scripts_execucao/benchmark_esbmc_runner.py`.
---
Configuração via variáveis de ambiente

O script infere automaticamente a raiz do repositório a partir de sua própria localização. Nenhuma variável precisa ser definida para o tucuman se o repositório for clonado sem mover arquivos.
Variável        Descrição       Padrão
`TUCUMAN_DIR`   Diretório do `tucuman_py/`      `<repo>/tucuman_py`
`CPACHECKER_DIR`        Diretório raiz do CPAchecker    `/opt/cpachecker`
`SEA_IMAGE`     Nome da imagem Docker do SeaHorn        `seahorn-builder`
`KLEE_IMAGE`    Nome da imagem Docker do KLEE   `klee/klee`
---

Grupos do benchmark

Grupo   Padrão  Tipos   Casos
A       `(T*)(buf + 1)` u16, u32, u64   6
B       `(T*)((char*)&x + 1)`   u16, u32, u64   6
C       `(T*)&vec[1]`   u16, u32, u64   6
D       `(T*)(base + offsetof(...))`    u16, u32, u64   6
E       `(T*)(base + i)` simbólico      u16, u32, u64   6
F       `(T*)((char*)p + sizeof(char))` u16, u32, u64   6
G       `(T*)(buf + N)` ímpar   u16, u32, u64   6
H       `(T*)&s.b` acesso bruto u16, u32, u64   6
I       `(T*)((void*)buf + 1)`  u16, u32, u64   6
J       `(T*)&((struct packed_s*)p)->b` u16, u32, u64   6
Cada grupo contém um caso alinhado (esperado: OK) e um desalinhado (esperado: VIOLATION) para cada um dos tipos.
---

### Resumo de Compatibilidade das Ferramentas
*Resultados consolidados das rodadas v3 a v4.3.*

| Ferramenta | Sem Asserções | Com Asserções | Detecta Alinhamento |
| :--- | :--- | :--- | :--- |
| **Tucuman** | ✅ 90% (estável) | ✅ 90% (idêntico) | ⚠️ Todos os grupos, exceto Grupo E (sempre UNKNOWN) |
| **CBMC** | ⚠️ Maioria UNKNOWN (10% acc.) | ✅ 95% | ⚠️ Todos, exceto Grupo E (falso negativo recorrente) |
| **ESBMC** | ✅ 93–95% | ⚠️ Instável* — baixo desempenho com alinhamento natural (50%, 100% FP), recupera com explícito (83%) | ✅ Mas sensível à forma (natural × explícito) |
| **CPAchecker** | ❌ Não detecta nenhuma violação (FN=30) | ⚠️ Parcial (65%), FP concentrado em A/E/F/G/I | ⚠️ Instável entre rodadas (chegou a 100% UNKNOWN em versões anteriores) |
| **KLEE** | ❌ Não detecta nenhuma violação (FN=30) | ✅ 93–95% | ✅ Com asserções, exceto Grupo B |
| **SeaHorn** | ❌ Não detecta nenhuma violação (FN=30) | ⚠️ Só falso positivo, nunca falso negativo (67–83%) | ⚠️ Melhora bastante com alinhamento explícito |

> **Legenda:**  
> ✅ Funciona bem &nbsp;|&nbsp; ⚠️ Funciona com ressalvas &nbsp;|&nbsp; ❌ Não funciona

---
Esta matriz está ancorada principalmente na rodada mais recente e estável (v4.3).
---
*ESBMC: ticket aberto
esbmc#6949: #pragma packé honrado em`sizeof` mas ignorado nos offsets dos campos; acesso desalinhado real passa como seguro (confirmado por UBSan).
esbmc#6950: _Alignas é descartado quando aplicado a variável de tipo struct
esbmc#6951: check_alignment e o modelo de espaço de endereços discordam sobre o alinhamento do endereço-base, na mesma execução

---
Citação
Se utilizar este benchmark em sua pesquisa, por favor cite:
```bibtex
@article{teixeira2026tucuma,
  title  = {Verificação Formal de Modelos de Memória Alinhada em
             Programas C usando o Solver Z3},
  author = {Silva, Antônio Carlos de Castro and
            Teixeira, Wesley Vitorino},
  school = {PPGEE -- Universidade Federal do Amazonas},
  year   = {2026}
}
```
