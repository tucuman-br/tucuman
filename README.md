# Tucumã - Verificador Formal de Alinhamento de Memória para Programas C usando Z3

## Visão Geral

O **Tucumã** é um protótipo de verificação formal desenvolvido para detectar violações de alinhamento de memória em programas escritos em C utilizando o solver SMT Z3.

Enquanto verificadores tradicionais frequentemente modelam a memória como uma sequência plana de bytes (*byte-level memory model*), o Tucumã introduz explicitamente restrições de alinhamento definidas pelo padrão ISO C, permitindo identificar acessos desalinhados que podem passar despercebidos em modelos convencionais.

O projeto foi desenvolvido no contexto da disciplina **PGENE549 – Verificação de Software e Sistemas** do Programa de Pós-Graduação em Engenharia Elétrica (PPGEE) da Universidade Federal do Amazonas (UFAM).

## Limitações

Nesta versão, o parser foi implementado como um reconhecedor sintático orientado aos padrões presentes no benchmark desenvolvido neste trabalho. Consequentemente, ele não cobre toda a gramática da linguagem C nem realiza análise semântica completa. Essa escolha reduz a complexidade da implementação e é suficiente para validar a hipótese de pesquisa proposta. Como trabalho futuro, pretende-se substituir esse componente por um front-end baseado na AST do Clang, ampliando a cobertura da linguagem e a robustez da extração das informações necessárias à geração das fórmulas SMT.

A versão em C está em desenvolvimento.
