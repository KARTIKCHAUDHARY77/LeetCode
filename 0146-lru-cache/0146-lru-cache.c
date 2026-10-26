#include <stdlib.h>

typedef struct Node {
    int key, value;
    struct Node *prev, *next;
} Node;

typedef struct {
    int capacity, size;
    Node *head, *tail;
    Node **hash;
} LRUCache;

#define HASH_SIZE 10007

int hash(int key) {
    return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

Node* createNode(int key, int value) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->value = value;
    n->prev = n->next = NULL;
    return n;
}

void removeNode(LRUCache *obj, Node *n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
}

void insertFront(LRUCache *obj, Node *n) {
    n->next = obj->head->next;
    n->prev = obj->head;
    obj->head->next->prev = n;
    obj->head->next = n;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *obj = (LRUCache*)malloc(sizeof(LRUCache));

    obj->capacity = capacity;
    obj->size = 0;

    obj->head = createNode(0, 0);
    obj->tail = createNode(0, 0);

    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;

    obj->hash = (Node**)calloc(HASH_SIZE, sizeof(Node*));

    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node *n = obj->hash[hash(key)];

    while (n != NULL && n->key != key)
        return -1;

    if (n == NULL)
        return -1;

    removeNode(obj, n);
    insertFront(obj, n);

    return n->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node *n = obj->hash[hash(key)];

    while (n != NULL && n->key != key)
        return;

    if (n != NULL) {
        n->value = value;
        removeNode(obj, n);
        insertFront(obj, n);
        return;
    }

    n = createNode(key, value);
    insertFront(obj, n);
    obj->hash[hash(key)] = n;
    obj->size++;

    if (obj->size > obj->capacity) {
        Node *old = obj->tail->prev;
        removeNode(obj, old);
        obj->hash[hash(old->key)] = NULL;
        free(old);
        obj->size--;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node *n = obj->head;

    while (n != NULL) {
        Node *temp = n;
        n = n->next;
        free(temp);
    }

    free(obj->hash);
    free(obj);
}