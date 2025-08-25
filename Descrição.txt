Trabalho I - Compiladores (Análise Sintática LR(0))

Discentes: Ana Alicy Ribeiro dos Santos
	   Ana Beatriz Leite Damascena  
	   Kaylane Castro Evangelista 
Curso: Engenharia da Computação
Disciplina: Compiladores
Professor: LUCAS ISMAILY BEZERRA FREITAS


-Objetivo do Trabalho
Desenvolver um analisador sintático LR(0) baseado em uma gramática simplificada inspirada na linguagem LangB. O trabalho é dividido em três partes:
	1.Cálculo dos conjuntos FIRST e FOLLOW.
	2.Construção do Autômato LR(0).
	3.Implementação do Parser LR(0) capaz de reconhecer ou rejeitar entradas sintáticas.

-Estrutura do Projeto
	compiladores/
	├── src/
	│   ├── automato.cpp         # Constrói o autômato LR(0)
	│   ├── parserlr0.cpp        # Implementa o analisador sintático LR(0)
	│   ├── action_goto.cpp      # Gera a tabela ACTION e GOTO
	│   ├── entrada.txt          # Entradas de teste (válidas e inválidas)
	│   ├── saida.log            # Saída gerada pelo parser
	│   └──  src/first_follow/
	│    ├── first_follow.cpp     # Calcula os conjuntos FIRST e FOLLOW

-Gramática Utilizada (LangB)
	0. S' → S $
	1. S  → ( L )
	2. S  → x
	3. L  → S
	4. L  → L , S

Essa gramática permite expressões como:
	x
	( x )
	( x , x )
	( x , ( x , x ) )
Essa gramática foi utilizada em todos os módulos do trabalho (cálculo de FIRST/FOLLOW, autômato e parser).



-Parte I: Algoritmo de FIRST e FOLLOW
O arquivo first_follow.cpp contém a implementação do cálculo dos conjuntos FIRST e FOLLOW. Ao executar ./exe após make, a saída gerada foi:
	FIRST:
	L: { ( x }
	S: { ( x }
	S': { ( x }

	FOLLOW:
	L: { ) , }
	S: { $ ) , }
	S': { }
Esses conjuntos são fundamentais para prever quais produções aplicar durante reduções e também auxiliam na construção da tabela de parsing (em versões mais completas como SLR ou LALR).
	Esses conjuntos são essenciais para verificações de redução e construção de parsers preditivos.
	Esses conjuntos são essenciais para análises preditivas e validação de reduções.



-Parte II: Autômato LR(0)
O arquivo automato.cpp gera todos os estados e transições do autômato LR(0), com base na gramática. Ele implementa a função closure e goto, essenciais para o reconhecimento de itens LR(0).

A saída mostra:
	Os estados (conjuntos de itens LR(0))
	As transições entre os estados
	
Esses dados são usados para construir a tabela de parsing.



Parte III: Construção da Tabela ACTION e GOTO
A geração da tabela de parsing é feita com base nos estados do autômato LR(0).
	O arquivo action_goto.cpp constrói duas tabelas:
		ACTION: define as ações (shift, reduce, accept ou erro) para símbolos terminais.
		GOTO: define as transições entre estados ao empilhar não-terminais.
A saída mostra todas as entradas das tabelas, por exemplo:
	ACTION[0, (] = s1
	ACTION[3, )] = r2
	...
	GOTO[1, L] = 4
	GOTO[2, S] = 5
Essas tabelas são utilizadas diretamente pelo parser LR(0).



-Parte IV: Analisador Sintático LR(0)
O arquivo parser_lr0.cpp utiliza:
	Tabela ACTION: com ações de shift, reduce, accept e erro;
	Tabela GOTO: com transições para não-terminais após reduções;
	Pilha de estados: simula o comportamento da máquina LR(0).

O parser lê um arquivo entrada.txt com várias linhas e:
	Analisa cada linha como uma entrada;
	Exibe Teste N. Sucesso ou Teste N. Erro sintático no terminal;
	Registra esses mesmos resultados no arquivo saida .log, esse arquivo se encontra na pasta src.

Arquivos de Entrada Válidas e Inválidas
Para validar o funcionamento do analisador sintático LR(0), foram criados dois arquivos de entrada localizados na pasta src:
    entrada_valida.txt — contém exemplos de expressões válidas de acordo com a gramática LangB.
    entrada_invalida.txt — contém expressões que violam as regras da gramática, resultando em erro sintático.
    
Cada linha dos arquivos é lida e analisada separadamente pelo parser. A saída é mostrada no terminal com a mensagem:
	Teste N. Sucesso
ou
	Teste N. Erro sintático
Os mesmos resultados também são registrados automaticamente no arquivo saida.log, criado na pasta src.



-Como Compilar e Executar
	# Compilar
	$ g++ automato.cpp -o automato
	$ g++ action_goto.cpp -o tabela
	$ g++ parserlr0.cpp -o parser
	
	# Executar
	$ ./automato
	$ ./tabela
	$ ./parser
	
Informe entrada.txt quando solicitado pelo parser. Essa entrada seria 'entrada_valida.txt' e entrada_invalida.txt', esse arquivos estão dentro da pasta src.	

	
	#compilar o fisrt_follow
	Para compilar e executar esta parte, foram utilizados os seguintes comandos dentro da pasta first_follow que estar dentro da pasta src:
		cd first_follow
		make
		./exe
	
	
-Considerações Finais
	O trabalho implementa  todas as três etapas propostas.
	A gramática foi aplicada fielmente conforme a linguagem LangB fornecida.
	O parser LR(0) foi testado com várias entradas, e a tabela ACTION/GOTO foi montada com base no autômato.
	O algoritmo de FIRST e FOLLOW foi construído com base nos princípios clássicos de análise sintática.
	Os arquivos estão organizados e a execução é reproduzível.


-Autoria
Trabalho desenvolvido por Ana Alicy Ribeiro dos Santos, Ana Beatriz Leite Damascena e Kaylane Castro Evangelista  para a disciplina de Compiladores no curso de Engenharia da Computação - UFC Quixadá.
