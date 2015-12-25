// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>
#include <iostream>

using namespace std;



struct KeyAndValue {
	int key;
	int value;
	void* prev;
	void* next;
	KeyAndValue() {
		key = -1;
		value = -1;
		prev = NULL;
		next = NULL;
	}
};

class LRUCache {

private:
	unordered_map<int, struct KeyAndValue*> keyMap;
	struct KeyAndValue* head; //most recently used
	struct KeyAndValue* tail; //least recently used
	struct KeyAndValue** addrsHolder;
	int capacity;
	int remainings;

	void toHead(struct KeyAndValue* ptr) {
		if (ptr != head) {//not at head
			if (tail == ptr) {//tail
				tail = (struct KeyAndValue*)ptr->prev;
				((struct KeyAndValue*)ptr->prev)->next = NULL;
				ptr->prev = NULL;
				ptr->next = (void*)head;
				head->prev = ptr;
				head = ptr;
			}
			else {//in between
				((struct KeyAndValue*)ptr->prev)->next = ptr->next;
				((struct KeyAndValue*)ptr->next)->prev = ptr->prev;
				ptr->prev = NULL;
				ptr->next = head;
				head->prev = ptr;
				head = ptr;
			}
		}
	}

public:
	LRUCache(int capacity) {
		head = NULL;
		tail = NULL;
		addrsHolder = new struct KeyAndValue*[capacity];
		for (int i = 0; i < capacity; ++i) {
			addrsHolder[i] = new struct KeyAndValue();
		}
		this->capacity = capacity;
		this->remainings = capacity;
	}

	int get(int key) {
		unordered_map<int, struct KeyAndValue*>::const_iterator got = keyMap.find(key);
		if (got == keyMap.end()) {
			return -1;
		}
		else {
			struct KeyAndValue* ptr = got->second;
			toHead(ptr);
			return head->value;
		}
	}

	void set(int key, int value) {
		unordered_map<int, struct KeyAndValue*>::const_iterator got = keyMap.find(key);
		if (got == keyMap.end()) {
			if (remainings == capacity) {
				head = addrsHolder[remainings - 1];
				head->key = key;
				head->value = value;
				tail = head;
				--remainings;
			}
			else if (remainings > 0) {
				head->prev = (void*)addrsHolder[remainings - 1];
				addrsHolder[remainings - 1]->next = (void*)head;
				addrsHolder[remainings - 1]->key = key;
				addrsHolder[remainings - 1]->value = value;
				head = addrsHolder[remainings - 1];
				--remainings;
			}
			else {
				keyMap.erase(tail->key);
				struct KeyAndValue* prev = (struct KeyAndValue*)tail->prev;
				if (prev != NULL)
					((struct KeyAndValue*)tail->prev)->next = NULL;
				tail->key = key;
				tail->value = value;
				tail->prev = NULL;
				tail->next = (void*)head;
				head->prev = (void*)tail;
				head = tail;
				tail = prev;
			}
			keyMap[key] = head;
		}
		else {
			struct KeyAndValue* ptr = got->second;
			toHead(ptr);
			head->value = value;
		}

	}
};


int main()
{
	LRUCache* cache = new LRUCache(3);
	cache->set(1, 1);
	cache->set(2, 2);
	cache->set(3, 3);
	cache->set(4, 4);
	cout << cache->get(4) << endl;
	cout << cache->get(3) << endl;
	cout << cache->get(2) << endl;
	cout << cache->get(1) << endl;
	cache->set(5, 5);
	cout << cache->get(1) << endl;
	cout << cache->get(2) << endl;
	cout << cache->get(3) << endl;
	cout << cache->get(4) << endl;
	cout << cache->get(5) << endl;


	/*LRUCache* cache = new LRUCache(2);
	cache->set(2, 1);
	cache->set(1, 1);
	cout << cache->get(2) << endl;
	cache->set(4, 1);
	cout << cache->get(1) << endl;
	cout << cache->get(2) << endl;*/

	/*LRUCache* cache = new LRUCache(1);
	cache->set(2, 1);
	cout << cache->get(2) << endl;
	cache->set(3, 2);
	cout << cache->get(2) << endl;
	cout << cache->get(3) << endl; */

	/*LRUCache* cache = new LRUCache(2);
	cache->set(2, 1);
	cache->set(2, 2);
	cout << cache->get(2) << endl;
	cache->set(4, 1);
	cout << cache->get(1) << endl;
	cout << cache->get(2) << endl;*/

	return 0;
}

