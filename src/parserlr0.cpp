
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <string>
#include <fstream>

using namespace std;

// Regras da gramática
struct Regra {
    string esquerda;
    vector<string> direita;
};


// Produções da gramática LR(0) fornecida
vector<Regra> regras = {
    {"S'", {"S", "$"}},
    {"S", {"(", "L", ")"}},
    {"S", {"x"}},
    {"L", {"S"}},
    {"L", {"L", ",", "S"}}
};

// Tabela ACTION: define ações (shift, reduce ou accept) para pares (estado, símbolo)
map<pair<int, string>, string> ACTION = {
    {{0, "("}, "s1"}, {{0, "x"}, "s3"},
    {{1, "("}, "s1"}, {{1, "x"}, "s3"},
    {{2, "$"}, "s6"},
    {{3, "$"}, "r2"}, {{3, ")"}, "r2"}, {{3, ","}, "r2"},
    {{4, ")"}, "s7"}, {{4, ","}, "s8"},
    {{5, "$"}, "r3"}, {{5, ")"}, "r3"}, {{5, ","}, "r3"},
    {{6, "$"}, "acc"},
    {{7, "$"}, "r1"}, {{7, ")"}, "r1"}, {{7, ","}, "r1"},
    {{8, "("}, "s1"}, {{8, "x"}, "s3"},
    {{9, "$"}, "r4"}, {{9, ")"}, "r4"}, {{9, ","}, "r4"}
};

// Tabela GOTO: define o próximo estado ao reduzir e empilhar um não-terminal
map<pair<int, string>, int> GOTO = {
    {{0, "S"}, 2},
    {{1, "L"}, 4},
    {{1, "S"}, 5},
    {{8, "S"}, 9}
};

// Função para separar uma linha em tokens usando espaços como delimitador
vector<string> separarTokens(const string& linha) {
    vector<string> tokens;
    string token;
    for (char c : linha) {
        if (isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

int main() {
    string nomeArquivo;
    cout << "Arquivo de entrada (.txt): ";
    cin >> nomeArquivo;

    ifstream arq(nomeArquivo); // Abre arquivo de entrada
    ofstream log("saida.log"); // Abre arquivo de saida
    if (!arq) {
        cout << "Erro: Arquivo não encontrado.\n";
        return 1;
    }

    string linha;
    int linhaNum = 1;
    while (getline(arq, linha)) {   // Lê linha por linha do arquivo
        vector<string> entrada = separarTokens(linha);
        entrada.push_back("$");    // Adiciona símbolo terminal $
        if (entrada.size() <= 1) continue; // Ignora linhas vazias


        bool erro = false;
        stack<int> pilha; // Pilha de estados do parser
        pilha.push(0);
        int ip = 0; // Índice do símbolo atual na entrada


        while (true) {
            int estado = pilha.top();                                   // estado atual
            string simbolo = (ip < entrada.size()) ? entrada[ip] : "$"; //próximo simbolo
            string acao = ACTION.count({estado, simbolo}) ? ACTION[{estado, simbolo}] : "erro";

            if (acao == "erro") {
                erro = true; 
                break;                  //simbolo inesperado
            } else if (acao == "acc") {
                break;                 //entrada aceita
            } else if (acao[0] == 's') {
                int novoEstado = stoi(acao.substr(1)); //shift: vai para novo estado
                pilha.push(novoEstado);
                ip++;                                 // Avança simbolo de entrada
            } else if (acao[0] == 'r') {
                int r = stoi(acao.substr(1));        //reduce: aplica regra r
                int tamanho = regras[r].direita.size();
                for (int i = 0; i < tamanho; ++i) pilha.pop(); // Remove estados da pilha
                int topo = pilha.top();                        // Estado após redução
                pilha.push(GOTO[{topo, regras[r].esquerda}]);  // Vai para o estado destino após empilhar o não-terminal
            }
        }

        // exibe e grava o resultado
        if (erro) {
            cout << "Teste " << linhaNum << ": Erro sintático\n";
            log << "Teste " << linhaNum << ": Erro sintático\n";
        } else {
            cout << "Teste " << linhaNum << ": Sucesso\n";
            log << "Teste " << linhaNum << ": Sucesso\n";
        }
        linhaNum++;
    }

    return 0;
}