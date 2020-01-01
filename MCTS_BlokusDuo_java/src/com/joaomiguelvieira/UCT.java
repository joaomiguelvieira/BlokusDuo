package com.joaomiguelvieira;

import java.util.Collections;
import java.util.Comparator;

public class UCT {
    private static double uctValue(int totalVisit, double nodeWinScore, int nodeVisit) {
        if (nodeVisit == 0)
            return Double.MAX_VALUE;

        return (nodeWinScore / (double) nodeVisit) + 1.41 * Math.sqrt(Math.log(totalVisit) / (double) nodeVisit);
    }

    public static Node findBestNodeWithUCT(Node node) {
        int parentVisit = node.getState().getVisitCount();
        return Collections.max(
                node.getChildArray(),
                Comparator.comparing(child -> uctValue(parentVisit, child.getState().getWinCount(), child.getState().getVisitCount())));
    }
}
