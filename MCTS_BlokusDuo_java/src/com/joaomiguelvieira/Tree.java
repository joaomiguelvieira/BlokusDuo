package com.joaomiguelvieira;

public class Tree {
    private Node root;

    public Tree() {
        root = new Node();
    }

    public Node getRoot() {
        return root;
    }

    public void setRoot(Node root) {
        this.root = root;

        Node tempNode = root.getParent();
        while (tempNode.getParent() != null) {
            tempNode.getChildArray().clear();
            tempNode = tempNode.getParent();
        }
    }
}
