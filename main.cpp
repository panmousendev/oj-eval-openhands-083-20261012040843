#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Build circular linked list
    Node* head = new Node(1);
    Node* current = head;
    
    for (int i = 2; i <= n; i++) {
        current->next = new Node(i);
        current = current->next;
    }
    
    // Make it circular
    current->next = head;
    
    // Josephus elimination
    while (n > 0) {
        // Find the (m-1)-th node (node before the one to remove)
        Node* prev = nullptr;
        current = head;
        
        // Move (m-1) steps
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // Remove current node
        cout << current->data << endl;
        
        if (n == 1) {
            // Last node, just delete it
            delete current;
            break;
        }
        
        // Remove current from the list
        if (prev == nullptr) {
            // This happens when m = 1, need to find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            prev = last;
        }
        
        prev->next = current->next;
        head = current->next;
        
        delete current;
        n--;
    }
    
    return 0;
}