#include "first_follow.hpp"

void Follow() {
    FOLLOW[iniSimbol].insert("$");

    bool aux; // saber se já foi mudado
    do {
        aux = false;

        for (auto i = LR0.begin(); i != LR0.end(); ++i) {
            string le = i->first;

            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                const auto& prod = *j;

                for (size_t k = 0; k < prod.size(); ++k) {
                    string ld = prod[k];
                    if (!isTerminal(ld)) {
                        set<string> pos_ld;

                        if (k + 1 < prod.size()) {
                            string prox = prod[k + 1];
                            if (isTerminal(prox)) {
                                pos_ld.insert(prox);
                            } else {
                                for (auto l = FIRST[prox].begin(); l != FIRST[prox].end(); ++l) {
                                    if (*l != "ε")
                                        pos_ld.insert(*l);
                                }
                            }
                        } else {
                            pos_ld = FOLLOW[le];
                        }

                        size_t sizee = FOLLOW[ld].size();
                        FOLLOW[ld].insert(pos_ld.begin(), pos_ld.end());
                        if (FOLLOW[ld].size() > sizee) aux = true;
                    }
                }
            }
        }
    } while (aux);
}
