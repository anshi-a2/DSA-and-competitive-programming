// PROBLEM :

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4



// SOLUTION :


// Node structure for Doubly Linked List
class Node {
public:
    int key;
    int val;
    Node* prev;
    Node* next;

    // Constructor to initialize node with key-value pair
    Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int cap; // Maximum capacity of the cache
    std::unordered_map<int, Node*> cache; // Maps keys to their corresponding nodes
    Node* oldest; // Dummy head node (LRU end)
    Node* latest; // Dummy tail node (MRU end)

public:
    // Constructor: Initialize dummy head and tail
    LRUCache(int capacity) : cap(capacity) {
        oldest = new Node(0, 0);  // dummy node at the beginning
        latest = new Node(0, 0);  // dummy node at the end
        oldest->next = latest;
        latest->prev = oldest;
    }

    // Get the value of the key if it exists in the cache
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);   // Remove node from current position
            insert(node);   // Re-insert at MRU position
            return node->val;
        }
        return -1;  // Key not found
    }

    // Insert node at the end (MRU position)
    void insert(Node* node) {
        Node* prev = latest->prev;
        Node* next = latest;
        prev->next = next->prev = node;
        node->next = next;
        node->prev = prev;
    }

    // Remove node from its current position
    void remove(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    // Add or update key-value pair in the cache
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);  // Remove old node if key exists
        }

        Node* newNode = new Node(key, value);
        cache[key] = newNode;    // Add to map
        insert(newNode);         // Insert at MRU position

        // If cache exceeds capacity, remove the least recently used node
        if (cache.size() > cap) {
            Node* lru = oldest->next;  // LRU node is right after dummy head
            remove(lru);
            cache.erase(lru->key);     // Remove from map
            delete lru;                // Free memory
        }
    }

    // Destructor to clean up all allocated nodes
    ~LRUCache() {
        Node* curr = oldest;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};



