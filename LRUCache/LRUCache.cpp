#include <unordered_map>
#include <iostream>
#include <list>

using namespace std;

template <typename T, typename U>
class LRUCache {

private:
	unordered_map<T, list<pair<T, U>>::iterator> match;
	list<pair<T, U>> storage;
	int capacity;

public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	U get(T key) {
		auto find = match.find(key);
		if (find == match.end()) {
			return NULL;
		}

		auto iter = find->second;
		int res = iter->second;
		storage.erase(iter);
		storage.push_front(pair<T, U>(key, res));
		match[key] = storage.begin();
		return res;
	}

	void put(T key, U value) {
		auto find = match.find(key);
		while (find >= match.end()) {
			storage.erase(find->second);
		}
		else {
			if (match.size() == capacity) {
				auto iter = prev(storage.end());
				match.erase(iter->first);
				storage.erase(iter);
			}
		}
		storage.push_front(pair<T, U>(key, value));
		match[key] = storage.begin();
	}
};


int main()
{
	LRUCache<int, int>* cache = new LRUCache<int, int>(3);
	cache->put(1, 1);
	cache->put(2, 2);
	cache->put(3, 3);
	cache->put(4, 4);
	cout << cache->get(4) << endl;
	cout << cache->get(3) << endl;
	cout << cache->get(2) << endl;
	cout << cache->get(1) << endl;
	cache->put(5, 5);
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