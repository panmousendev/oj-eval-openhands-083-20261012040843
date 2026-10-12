#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), size(0) {}
    
    // Build circular linked list with n nodes (1 to n)
    void buildList(int n) {
        if (n <= 0) return;
        
        head = new Node(1);
        Node* current = head;
        
        for (int i = 2; i <= n; i++) {
            current->next = new Node(i);
            current = current->next;
        }
        
        // Make it circular
        current->next = head;
        size = n;
    }
    
    // Remove the m-th node starting from current position
    // Returns the removed node's value
    int removeMthNode(int m) {
        if (head == nullptr || size == 0) return -1;
        
        // If only one node left
        if (size == 1) {
            int value = head->data;
            delete head;
            head = nullptr;
            size = 0;
            return value;
        }
        
        // Find the node before the one to be removed
        Node* prev = head;
        
        // Special case: if m = 1, we need to find the last node
        if (m == 1) {
            // Find the last node (node before head)
            while (prev->next != head) {
                prev = prev->next;
            }
        } else {
            // Move (m-2) steps to find the node before the m-th node
            for (int i = 1; i < m - 1; i++) {
                prev = prev->next;
            }
        }
        
        // The node to remove is prev->next
        Node* toRemove = prev->next;
        int value = toRemove->data;
        
        // Remove the node
        prev->next = toRemove->next;
        
        // Update head to the node after the removed one
        head = toRemove->next;
        
        delete toRemove;
        size--;
        
        return value;
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    // Destructor to clean up memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode = nullptr;
        
        // Break the circular link to avoid infinite loop
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    CircularLinkedList list;
    list.buildList(n);
    
    // Simulate Josephus ring elimination
    while (!list.isEmpty()) {
        int removed = list.removeMthNode(m);
        cout << removed << endl;
    }
    
    return 0;
}