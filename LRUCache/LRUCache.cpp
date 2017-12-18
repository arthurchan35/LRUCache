#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

class LRUCache {

private:
	unordered_map<int, list<int>::iterator> match;
	list<int> storage;
	int capacity;

public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	int get(int key) {
		auto find = match.find(key);
		if (find == match.end()) {
			return -1;
		}

		auto iter = find->second;
		int res = *iter;
		storage.erase(iter);
		storage.push_front(res);
		match[key] = storage.begin();
		return res;
	}

	void set(int key, int value) {
		auto find = match.find(key);
		if (find != match.end()) {
			storage.erase(find->second);
		}
		storage.push_front(value);
		match[key] = storage.begin();
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