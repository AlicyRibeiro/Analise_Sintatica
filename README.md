# Compiladores
Trabalho I - Front-end 

# Analisador Sintático LR(0) para a Disciplina de Compiladores

## Descrição do Projeto
Este repositório contém a implementação de um analisador sintático LR(0) desenvolvido para a disciplina de Compiladores da Universidade Federal do Ceará (UFC) - Campus Quixadá. O objetivo do trabalho é aplicar os conceitos teóricos da análise sintática através da construção de um parser capaz de validar sentenças de uma gramática específica.

O projeto foi desenvolvido em C++ e está dividido em três partes principais.
1.  **Cálculo dos conjuntos FIRST e FOLLOW** para a gramática.
2.  **Construção do Autômato LR(0)**, com seus estados e transições.
3.  **Implementação do Parser LR(0)**, que utiliza as tabelas ACTION e GOTO para validar ou rejeitar sentenças de entrada.

### Autores
* Ana Alicy Ribeiro dos Santos 
* Ana Beatriz Leite Damascena 
* Kaylane Castro Evangelista 

###  Professor
* LUCAS ISMAILY BEZERRA FREITAS 

## Gramática Utilizada

O analisador foi construído com base na seguinte gramática LR(0):
* S' → S $
* S  → ( L )
* S  → x
* L  → S
* L  → L , S

Esta gramática foi consistentemente aplicada em todos os módulos do projeto.

## Estrutura do Projeto

O projeto está organizado na pasta `src/`, que contém os seguintes arquivos e executáveis:

* compiladores/
* └── src/
* ├── action_goto.cpp        # Gera as tabelas ACTION e GOTO
* ├── automato.cpp           # Constrói o autômato LR(0) canônico
* ├── first_follow/
* │   └── first_follow.cpp   # Calcula os conjuntos FIRST e FOLLOW
* ├── parserlr0.cpp          # Implementa o parser LR(0)
* ├── entrada_valida.txt     # Exemplos de sentenças válidas
* ├── entrada_invalida.txt   # Exemplos de sentenças inválidas
* └── saida.log              # Arquivo de log com os resultados da análise

## 0 Módulos do Analisador

### 1. Conjuntos FIRST e FOLLOW
O arquivo `first_follow/first_follow.cpp` implementa os algoritmos para calcular os conjuntos **FIRST** e **FOLLOW** da gramática. A saída gerada pelo programa foi:

**FIRST:**
* `L: { ( x }` 
* `S: { ( x }` 
* `S': { ( x }` 

**FOLLOW:**
* `L: { ) , }` 
* `S: { $ ) , }` 
* `S': { }`

### 2. Autômato LR(0)
O arquivo `automato.cpp` é responsável por gerar os estados canônicos (ou família de itens LR(0)) e as transições do autômato. Para isso, ele implementa as funções essenciais `fechamento` (closure) e `irPara` (goto).

### 3. Tabelas ACTION e GOTO
Com base nos estados do autômato, o `action_goto.cpp` constrói as tabelas de parsing:
* **Tabela ACTION**: Define a ação a ser tomada (shift, reduce, accept ou error) para um determinado estado e um símbolo terminal.
* **Tabela GOTO**: Indica o próximo estado para o qual o parser deve transitar após uma operação de redução.


### 4. Parser LR(0)
O `parserlr0.cpp` é o analisador sintático propriamente dito. Ele utiliza uma pilha de estados e as tabelas ACTION e GOTO para processar uma sequência de tokens. O parser lê um arquivo de entrada, analisa cada linha individualmente e informa se a sentença é sintaticamente correta ou não, exibindo "Sucesso" ou "Erro sintático".

## Como Compilar e Executar

Siga os passos abaixo para compilar e executar cada parte do projeto.

**1. Módulo FIRST e FOLLOW:**

Navegue até o diretório correspondente e utilize o `make`:
```bash
# Navegar para a pasta
cd src/first_follow

# Compilar com make
make

# Executar
./exe
```

**2. Autômato, Tabelas e Parser:**

Compile e execute os arquivos na pasta src/.
```bash
# Compilar os arquivos C++
g++ automato.cpp -o automato
g++ action_goto.cpp -o tabela
g++ parserlr0.cpp -o parser

# Executar os programas
./automato
./tabela
./parser
```

Ao executar o ./parser, o programa solicitará o nome do arquivo de entrada. Você pode usar entrada_valida.txt ou entrada_invalida.txt. 
