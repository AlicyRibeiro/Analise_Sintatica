#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Estruturas principais
struct Producao {
    string esquerda;
    vector<string> direita;
};

struct Item {
    int indiceProducao;
    int posPonto;

    bool operator<(const Item& outro) const {
        if (indiceProducao != outro.indiceProducao)
            return indiceProducao < outro.indiceProducao;
        return posPonto < outro.posPonto;
    }

    bool operator==(const Item& outro) const {
        return indiceProducao == outro.indiceProducao && posPonto == outro.posPonto;
    }
};

vector<Producao> producoes = {
    {"S'", {"S", "$"}},
    {"S", {"(", "L", ")"}},
    {"S", {"x"}},
    {"L", {"S"}},
    {"L", {"L", ",", "S"}}
};

set<string> obterNaoTerminais() {
    set<string> nt;
    for (auto& p : producoes)
        nt.insert(p.esquerda);
    return nt;
}

set<string> obterTerminais() {
    set<string> term;
    set<string> nt = obterNaoTerminais();
    for (auto& p : producoes) {
        for (auto& s : p.direita)
            if (!nt.count(s)) term.insert(s);
    }
    return term;
}

set<Item> fechamento(const set<Item>& itens) {
    set<Item> resultado = itens;
    queue<Item> fila;
    for (auto it : itens) fila.push(it);

    set<string> naoTerminais = obterNaoTerminais();
    while (!fila.empty()) {
        Item item = fila.front(); fila.pop();
        auto prod = producoes[item.indiceProducao];

        if (item.posPonto < prod.direita.size()) {
            string B = prod.direita[item.posPonto];
            if (naoTerminais.count(B)) {
                for (int i = 0; i < producoes.size(); i++) {
                    if (producoes[i].esquerda == B) {
                        Item novo = {i, 0};
                        if (!resultado.count(novo)) {
                            resultado.insert(novo);
                            fila.push(novo);
                        }
                    }
                }
            }
        }
    }
    return resultado;
}

set<Item> irPara(const set<Item>& itens, const string& simbolo) {
    set<Item> prox;
    for (auto& item : itens) {
        auto prod = producoes[item.indiceProducao];
        if (item.posPonto < prod.direita.size() && prod.direita[item.posPonto] == simbolo) {
            prox.insert({item.indiceProducao, item.posPonto + 1});
        }
    }
    return fechamento(prox);
}

bool conjuntosIguais(const set<Item>& a, const set<Item>& b) {
    return a == b;
}

int main() {
    vector<set<Item>> estados;
    map<pair<int, string>, int> transicoes;
    map<pair<int, string>, string> ACTION;
    map<pair<int, string>, int> GOTO;

    set<Item> inicial = {{0, 0}};
    inicial = fechamento(inicial);
    estados.push_back(inicial);

    queue<int> fila;
    fila.push(0);

    while (!fila.empty()) {
        int estadoAtual = fila.front(); fila.pop();
        set<Item> estado = estados[estadoAtual];

        set<string> simbolos;
        for (auto& item : estado) {
            auto& prod = producoes[item.indiceProducao];
            if (item.posPonto < prod.direita.size()) {
                simbolos.insert(prod.direita[item.posPonto]);
            }
        }

        for (auto& simbolo : simbolos) {
            set<Item> proximo = irPara(estado, simbolo);
            if (proximo.empty()) continue;

            int indiceProx = -1;
            for (int i = 0; i < estados.size(); i++) {
                if (conjuntosIguais(estados[i], proximo)) {
                    indiceProx = i;
                    break;
                }
            }
            if (indiceProx == -1) {
                indiceProx = estados.size();
                estados.push_back(proximo);
                fila.push(indiceProx);
            }

            transicoes[{estadoAtual, simbolo}] = indiceProx;
            if (obterTerminais().count(simbolo))
                ACTION[{estadoAtual, simbolo}] = "s" + to_string(indiceProx);
            else
                GOTO[{estadoAtual, simbolo}] = indiceProx;
        }

        for (auto& item : estado) {
            auto& prod = producoes[item.indiceProducao];
            if (item.posPonto == prod.direita.size()) {
                if (prod.esquerda == "S'") {
                    ACTION[{estadoAtual, "$"}] = "acc";
                } else {
                    set<string> seguir = { ",", ")", "$" }; // Follow simbólico para esse parser
                    for (auto& t : seguir) {
                        ACTION[{estadoAtual, t}] = "r" + to_string(item.indiceProducao);
                    }
                }
            }
        }
    }

    cout << "Tabela ACTION:\n";
    for (auto& [chave, acao] : ACTION) {
        cout << "ACTION[" << chave.first << ", " << chave.second << "] = " << acao << endl;
    }

    cout << "\nTabela GOTO:\n";
    for (auto& [chave, destino] : GOTO) {
        cout << "GOTO[" << chave.first << ", " << chave.second << "] = " << destino << endl;
    }

    return 0;
}


