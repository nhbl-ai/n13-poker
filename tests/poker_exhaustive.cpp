#include "LogicGame.h"
#include "PokerHand.h"
#include <array>
#include <iostream>

int main() {
    const auto deck = Logic().createDeck();
    std::array<unsigned long long,11> counts{};
    unsigned long long total=0;
    for (size_t a=0;a<48;++a) for(size_t b=a+1;b<49;++b)
        for(size_t c=b+1;c<50;++c) for(size_t d=c+1;d<51;++d) for(size_t e=d+1;e<52;++e) {
            const auto score=evaluateFiveCards({{deck[a],deck[b],deck[c],deck[d],deck[e]}});
            if (score.first<1 || score.first>10) return 1;
            ++counts[score.first];++total;
        }
    // Independent combinatorial counts of the ten existing ranking categories.
    const std::array<unsigned long long,11> expected{{0,1302540,1098240,123552,54912,10200,5108,3744,624,36,4}};
    for(size_t category=1;category<counts.size();++category) {
        if(counts[category]!=expected[category]) {
            std::cerr<<"Category "<<category<<": "<<counts[category]<<" expected "<<expected[category]<<'\n';return 1;
        }
    }
    std::cout<<"PASS: all "<<total<<" distinct five-card hands match category counts\n";
}
