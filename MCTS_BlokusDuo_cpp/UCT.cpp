//
// Created by joaovieira on 12/25/19.
//

#include "UCT.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <cfloat>

Node *UCT::findBestNodeWithUCT(Node *node) {
    int parentVisit = node->getState()->getVisitCount();
    return *max_element(node->getChildArray()->begin(), node->getChildArray()->end(),
                        [parentVisit](Node *node1, Node *node2) -> bool {
                            return uctValue(parentVisit, node1->getState()->getWinCount(),
                                            node1->getState()->getVisitCount()) <
                                   uctValue(parentVisit, node2->getState()->getWinCount(),
                                            node2->getState()->getVisitCount());
                        }
    );
}

double UCT::uctValue(int totalVisit, double nodeWinScore, int nodeVisit) {
    if (nodeVisit == 0) {
        return DBL_MAX;
    }

    return (nodeWinScore / (double) nodeVisit) + 1.41 * sqrt(log(totalVisit) / (double) nodeVisit);
}
