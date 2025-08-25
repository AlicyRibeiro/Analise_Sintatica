#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Produção da gramática
struct Producao {
    string esquerda;
    vector<string> direita;
};

// Item LR(0)
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

// Lista de produções 
vector<Producao> producoes = { //implementação da gramática no código
    {"S'", {"S", "$"}},
    {"S", {"(", "L", ")"}},
    {"S", {"x"}},
    {"L", {"S"}},
    {"L", {"L", ",", "S"}}
};

// Retorna os não-terminais da gramática
set<string> obterNaoTerminais() {
    set<string> naoTerminais;
    for (const auto& prod : producoes)
        naoTerminais.insert(prod.esquerda);
    return naoTerminais;
}

// Função de fechamento (closure)
set<Item> fechamento(const set<Item>& itens) {
    set<Item> resultado = itens;
    queue<Item> fila;
    for (const auto& it : itens) fila.push(it);

    set<string> naoTerminais = obterNaoTerminais();

    while (!fila.empty()) {
        Item item = fila.front(); fila.pop();
        const auto& prod = producoes[item.indiceProducao];

        if (item.posPonto < prod.direita.size()) {
            string simbolo = prod.direita[item.posPonto];
            if (naoTerminais.count(simbolo)) {
                for (int i = 0; i < producoes.size(); ++i) {
                    if (producoes[i].esquerda == simbolo) {
                        Item novoItem = {i, 0};
                        if (resultado.find(novoItem) == resultado.end()) {
                            resultado.insert(novoItem);
                            fila.push(novoItem);
                        }
                    }
                }
            }
        }
    }

    return resultado;
}

// Função goto
set<Item> irPara(const set<Item>& itens, const string& simbolo) {
    set<Item> prox;
    for (const auto& item : itens) {
        const auto& prod = producoes[item.indiceProducao];
        if (item.posPonto < prod.direita.size() && prod.direita[item.posPonto] == simbolo) {
            prox.insert({item.indiceProducao, item.posPonto + 1});
        }
    }
    return fechamento(prox);
}

// Verifica se dois conjuntos de itens são iguais
bool conjuntosIguais(const set<Item>& a, const set<Item>& b) {
    return a == b;
}

int main() {
    vector<set<Item>> estados;
    map<pair<int, string>, int> transicoes;

    // Estado inicial
    set<Item> inicial = {{0, 0}};
    inicial = fechamento(inicial);
    estados.push_back(inicial);

    queue<int> fila;
    fila.push(0);

    while (!fila.empty()) {
        int indiceEstado = fila.front(); fila.pop();
        set<Item> estado = estados[indiceEstado];

        set<string> simbolos;
        for (const auto& item : estado) {
            const auto& prod = producoes[item.indiceProducao];
            if (item.posPonto < prod.direita.size()) {
                simbolos.insert(prod.direita[item.posPonto]);
            }
        }

        for (const auto& simbolo : simbolos) {
            set<Item> proximo = irPara(estado, simbolo);
            if (proximo.empty()) continue;

            int indiceProximo = -1;
            for (int i = 0; i < estados.size(); ++i) {
                if (conjuntosIguais(estados[i], proximo)) {
                    indiceProximo = i;
                    break;
                }
            }
            if (indiceProximo == -1) {
                indiceProximo = estados.size();
                estados.push_back(proximo);
                fila.push(indiceProximo);
            }
            transicoes[{indiceEstado, simbolo}] = indiceProximo;
        }
    }

    // Exibir os estados
    for (int i = 0; i < estados.size(); ++i) {
        cout << "Estado " << i << ":\n";
        for (const auto& item : estados[i]) {
            const auto& prod = producoes[item.indiceProducao];
            cout << "  " << prod.esquerda << " → ";
            for (int j = 0; j < prod.direita.size(); ++j) {
                if (j == item.posPonto) cout << "• ";
                cout << prod.direita[j] << " ";
            }
            if (item.posPonto == prod.direita.size()) cout << "•";
            cout << "\n";
        }
        cout << "\n";
    }

    // Exibir transições
    cout << "Transições:\n";
    for (const auto& [chave, destino] : transicoes) {
        cout << "  (" << chave.first << ", " << chave.second << ") → " << destino << "\n";
    }

    return 0;
}
