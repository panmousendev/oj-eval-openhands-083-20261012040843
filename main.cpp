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
        if (n == 1) {
            // Only one node left
            cout << head->data << endl;
            delete head;
            break;
        }
        
        // Find the node before the one to be removed
        Node* prev;
        if (m == 1) {
            // Special case: m=1, find the last node
            prev = head;
            while (prev->next != head) {
                prev = prev->next;
            }
        } else {
            // Move (m-2) steps from head to find the previous node
            prev = head;
            for (int i = 1; i < m - 1; i++) {
                prev = prev->next;
            }
        }
        
        // The node to remove is prev->next
        Node* toRemove = prev->next;
        cout << toRemove->data << endl;
        
        // Remove the node
        prev->next = toRemove->next;
        head = toRemove->next;
        
        delete toRemove;
        n--;
    }
    
    return 0;
}