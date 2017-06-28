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

void Spell::write(Parcel &in, Spell *obj) {
    unordered_map<SpellNode *, int> nodes;
    vector<pair<int, int>> pairs;
    int id = 0;

    obj->getRootNode()->iterrator([&nodes, &id](SpellNode *node) -> void {
        nodes[node] = id++;
        return;
    });

    obj->getRootNode()->iterrator([&nodes, &pairs](SpellNode *node) -> void {
        int curId = nodes[node];
        for (SpellNode *child: node->getConnectedNodes())
            pairs.push_back(pair<int, int>(curId, nodes[child]));
        return;
    });

    in.put((int) nodes.size());
    for (pair<SpellNode *const, int> &key : nodes) {
        in.put(key.second);
        SpellNode::write(in, key.first);
    }

    in.put<int>((int) pairs.size());
    for (pair<int, int> pr : pairs) {
        in.put(pr.first);
        in.put(pr.second);
    }
}

Spell *Spell::read(Parcel &out) {
    unordered_map<int, SpellNode *> nodes;
    int countNodes = out.readInt();

    for (int i = 0; i < countNodes; i++) {
        int id = out.readInt();
        nodes[id] = SpellNode::read(out);
    }

    int countPair = out.readInt();

    for (int i = 0; i < countPair; i++) {
        nodes[out.readInt()]->connectNode(nodes[out.readInt()]);
    }

    return new Spell((*nodes.begin()).second);
}
