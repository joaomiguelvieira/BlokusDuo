package com.joaomiguelvieira;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;

public class Node {
    private State state;
    private ArrayList<Node> childArray;
    private Node parent;

    public Node() {
        state = new State();
        childArray = new ArrayList<>();
    }

    public Node(State state) {
        this.state = state;
        childArray = new ArrayList<>();
    }

    public State getState() {
        return state;
    }

    public ArrayList<Node> getChildArray() {
        return childArray;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getRandomChildNode() {
        int noOfPossibleMoves = childArray.size();
        int selectRandom = (int) (Math.random() * noOfPossibleMoves);
        return childArray.get(selectRandom);
    }

    public Node getParent() {
        return parent;
    }

    public Node getChildWithMaxScore() {
        return Collections.max(childArray, Comparator.comparing(node -> node.getState().getStateViability()));
    }
}
