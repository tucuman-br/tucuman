# Tucuman

**Tucuman** é um protótipo de verificação formal para detecção de violações de alinhamento de memória em programas escritos em C.

O projeto utiliza modelagem baseada em SMT (Satisfiability Modulo Theories) com o solver Z3 para inferir automaticamente restrições de alinhamento a partir da estrutura do programa, sem exigir assertivas ou anotações inseridas pelo programador.

## Status do Projeto

> ⚠️ **Versão Alpha**

A implementação em linguagem **C** encontra-se atualmente em **fase Alpha de desenvolvimento**.

Nesta etapa, o objetivo principal é validar o modelo proposto e avaliar sua eficácia na identificação de acessos desalinhados em comparação com verificadores formais de propósito geral.

Consequentemente:

- novas funcionalidades estão sendo implementadas;
- a API ainda pode sofrer alterações;
- alguns padrões de código C ainda não são reconhecidos;
- erros e limitações são esperados.

## Objetivos

O projeto busca:

- detectar automaticamente acessos potencialmente desalinhados;
- inferir propriedades de alinhamento sem modificações no código-fonte;
- modelar operações com ponteiros, casts e aritmética de endereços utilizando SMT;
- servir como plataforma experimental para pesquisas em verificação formal.

## Estado Atual

Atualmente o Tucuman é capaz de reconhecer diversos padrões de acesso envolvendo:

- offsets constantes;
- offsets simbólicos;
- `offsetof`;
- `sizeof`;
- ponteiros `void *`;
- estruturas `packed`;
- vetores;
- conversões de tipos (*casts*);
- acesso por operadores `.` e `->`.

Novos padrões serão adicionados nas próximas versões.

## Contribuições

Contribuições da comunidade são muito bem-vindas.

Você pode colaborar de diversas formas:

- reportando problemas (*Issues*);
- sugerindo melhorias;
- implementando novos padrões de reconhecimento;
- propondo novos benchmarks;
- corrigindo bugs;
- enviando *Pull Requests*.

Toda contribuição será analisada e, quando apropriado, incorporada ao projeto.

## Benchmark

O repositório inclui um conjunto de programas em C destinados à avaliação de ferramentas de verificação formal quanto à detecção de violações de alinhamento de memória.

O benchmark é utilizado para comparação entre diferentes verificadores, incluindo:

- Tucuman
- CBMC
- ESBMC
- CPAchecker
- SeaHorn
- KLEE

## Licença

Este projeto está sendo desenvolvido para fins de pesquisa acadêmica.

A definição da licença definitiva será publicada em uma versão futura do projeto.
