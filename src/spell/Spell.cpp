/**
 * @file Spell.cpp
 * @author LionZXY
 * @project Recast-server
 * @date 21.06.17
 * @email nikita@kulikof.ru
 **/
#include <unordered_map>
#include <vector>
#include "spells/nodes/SpellNode.hpp"
#include "spells/Spell.hpp"

void Spell::tickSpell(SpellEventListener &listener) {
    rootNode->tick(listener, NULL);
}

Spell::~Spell() {
    delete rootNode;
}

using namespace std;

void Spell::des() {
    unordered_map<SpellNode *, int> nodes;
    vector<pair<int, int>> pairs;
    int id = 0;
    rootNode->iterrator([&nodes, &id](SpellNode *node) -> void {
        nodes[node] = id++;
        return;
    });
    rootNode->iterrator([&nodes, &pairs](SpellNode *node) -> void {
        int curId = nodes[node];
        for (SpellNode *child: node->getConnectedNodes())
            pairs.push_back(pair<int, int>(curId, nodes[child]));
        return;
    });
}
