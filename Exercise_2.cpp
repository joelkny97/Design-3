// Time Complexity: O(1) for get and put operations
// Space Complexity: O(capacity) for the cache structure
// Were you able to solve the problem on Leetcode?: Yes
// Did you face any challenges while solving the problem? No

class Node {

public:
    int key, value;
    Node* next;
    Node* prev;
    Node(int key, int value):key(key), value(value), next(nullptr), prev(nullptr) {

    }
};

class LRUCache {
public:
    Node* head;
    Node* tail;

    // A map to store the key and its corresponding node in the doubly linked list
    // This allows for O(1) access to the nodes in the cache
    // The key is the integer key and the value is the pointer to the Node in the linked list
    std::unordered_map<int, Node*> lookup_map;

    int capacity;

    LRUCache(int capacity) {    
        // Initialize the cache with the given capacity
        // Create a dummy head and tail node to simplify the linked list operations
        // The head node points to the first element and the tail node points to the last element
        this->capacity = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
        
    }

    void addToHead(Node* node){
        
        // Empty List
        // if (head->next == tail){
        // }

        // Single Element
        // if (tail->prev == head){
        // }

        // Add the node to the head of the linked list
        // assign the next pointer of the new node to the current first element
        node->next = head->next;
        // assign the prev pointer of the new node to the head
        node->prev = head;
        // assign the current first element's prev pointer to the new node
        head->next->prev = node;
        // assign the head's next pointer to the new node
        head->next = node;
    
    }

    void removeNode(Node* node){

        // Remove the node from the linked list
        // Update the next pointer of the previous node to skip the current node
        node->prev->next = node->next;
        // Update the prev pointer of the next node to prev node of the current node
        node->next->prev = node->prev;

        // Clear the next and prev pointers of the node to be deleted
        node->next = nullptr;
        node->prev = nullptr;
        // delete node; 
        
    }
    
    int get(int key) {

        // If the key does not exist in the cache, return -1
        if (lookup_map.find(key) == lookup_map.end()){
            return -1;
        }

        // If the key exists in the cache, get the node from the lookup map
        Node* node = lookup_map[key];

        // Move the accessed node to the head of the linked list
        // This is done to mark it as recently used
        // if there is only one node in the cache, we don't need to move it
        if (lookup_map.size() > 1){
            removeNode(node);
            addToHead(node);
        }
        
        // Return the value of the node
        return node->value;
                
    }
    
    void put(int key, int value) {

        // If the key does not exist in the cache, create a new node
        if (lookup_map.find(key) == lookup_map.end()){
            // key does not exist in cache 

            // If the cache is full, remove the least recently used node
            // The least recently used node is the one before the tail
            if (lookup_map.size() == capacity){
                // Remove the last node from the linked list and the lookup map
                Node* lastNode = tail->prev;
                lookup_map.erase(lastNode->key);
                removeNode(lastNode);
                delete lastNode;
            
            }

            // Create a new node with the given key and value
            // Add the new node to the head of the linked list and update the lookup map
            Node* newNode = new Node(key, value);
            addToHead(newNode);
            lookup_map[key] = newNode;
        
        }
        else{

            // key exists in cache
            // Update the value of the existing node in the lookup map
            Node* node = lookup_map[key];
            node->value = value;
            // Move the accessed node to the head of the linked list
            // This is done to mark it as recently used
            // if there is only one node in the cache, we don't need to move it
            if (lookup_map.size() > 1){
                removeNode(node);
                addToHead(node);
            }
        }
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */