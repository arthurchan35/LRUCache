#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

class LRUCache {

private:
	unordered_map<int, list<pair<int, int>>::iterator> match;
	list<pair<int, int>> storage;
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
		int res = iter->second;
		storage.erase(iter);
		storage.push_front(pair<int, int>(key, res));
		match[key] = storage.begin();
		return res;
	}

	void put(int key, int value) {
		auto find = match.find(key);
		if (find != match.end()) {
			storage.erase(find->second);
		}
		else {
			if (match.size() == capacity) {
				auto iter = prev(storage.end());
				match.erase(iter->first);
				storage.erase(iter);
			}
		}
		storage.push_front(pair<int, int>(key, value));
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