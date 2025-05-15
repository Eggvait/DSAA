#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Insertion into BST
Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data)
        root = insert(root->left, val);
    else
        root = insert(root->right, val);
    return root;
}

// Find minimum value node in a BST
Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

// Deletion from BST
Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder Traversal (Ascending Sort)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Preorder Traversal
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// BFS (Level Order Traversal)
void bfs(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// DFS using stack
void dfs(Node* root) {
    if (!root) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->data << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

// Height of the tree
int height(Node* root) {
    if (!root) return -1;
    return 1 + max(height(root->left), height(root->right));
}

// Main
int main() {
    Node* root = nullptr;
    int choice, value;

    while (true) {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Inorder Traversal\n4. Preorder Traversal\n5. Postorder Traversal\n";
        cout << "6. BFS (Level Order)\n7. DFS\n8. Height of Tree\n9. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                cout << "Inorder (Ascending Sort): ";
                inorder(root);
                cout << endl;
                break;
            case 4:
                cout << "Preorder (Root-Left-Right): ";
                preorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Postorder (Left-Right-Root): ";
                postorder(root);
                cout << endl;
                break;
            case 6:
                cout << "BFS (Level Order): ";
                bfs(root);
                cout << endl;
                break;
            case 7:
                cout << "DFS (using Stack): ";
                dfs(root);
                cout << endl;
                break;
            case 8:
                cout << "Height of tree: " << height(root) << endl;
                break;
            case 9:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
