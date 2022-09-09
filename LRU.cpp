#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
public:
    int capacity;

    struct node
    {
        node *prev, *next;
        int key, value;

        node(int _key, int _value)
        {
            key = _key;
            value = _value;
        }
    };

    unordered_map<int, node *> tracker;

    struct node *HEAD;
    struct node *TAIL;

    LRUCache(int _capacity)
    {
        capacity = _capacity;
        HEAD = NULL;
        TAIL = NULL;
    }

    void add_to_dll(struct node *now)
    {
        if (HEAD == NULL && TAIL == NULL)
        {
            HEAD = TAIL = now;
        }
        else
        {
            // struct node *temp = HEAD;
            now->next = HEAD;
            HEAD = now;
        }
    }

    int get(int key)
    {
        return 0;
    }

    void put(int key, int value)
    {
        struct node *now = new node(key, value);
        tracker[key] = now;
        add_to_dll(now);
    }
};

int main()
{
    LRUCache *a = new LRUCache(3);
    (*a).put(1, 3);
}
