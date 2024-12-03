s# Vectors

**You do not know the size, dynamically allocates it**
vector<int> numbers;

**initialised with 5 elements**

vector<int> numbers(5);

**initialised with 5 elements with the given value (in this case 10)**

vector<int> numbers(5, 10);

**adding elements**

numbers.push_back(1);

**remove last element**

numbers.pop_back();

**access the element at the position**

numbers[0]

or

**bounds based**

numbers.at(0)

**iterating through**

for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
std::cout << *it << " ";
}

**2D array**

vector<vector<int>> vec2D;

**initialising 2d**

**vector<vector<int>> vec2D(3, vector<int>(4, 0));**

3 x 4 matrix filled with 0’s

**assign**

replace contents of vector with new elements.

```cpp
// Replace the contents of the vector with 'count' copies of 'value'
vector.assign(count, value);

// Replace the contents with elements from another range [first, last)
vector.assign(first, last);

// Replace the contents with elements from an initializer list
vector.assign({elem1, elem2, elem3, ...});

void assign(size_type count, const T& value);
// Description:
// Replaces the current contents of the vector with count copies of value.
// After this operation, the vector's size becomes count, 
// and each element is a copy of value.
```

# Array

**initialise an array (undefined values)**

int arr[10]; size of 10

**initialise with values**

int arr[5] = {1, 2, 3, 4, 5}

**implicit size**

int arr[] = {1,2,3,4,5};

**using fill**

fill(arr, arr + 5, 42);

arr + 5 is the ending address i think

# map

uses a red-black tree, log time for insertion deletoin and access

stored in ascending order, no duplicate keys

map<keytype, valuetype> mapname

| **Operation** | **Description** | **Complexity** |
| --- | --- | --- |
| `map[key]` | Access or modify the value associated with a key (inserts if key doesn't exist). | O(log n) |
| `map.at(key)` | Access value, throws `std::out_of_range` if the key doesn’t exist. | O(log n) |
| `map.insert({key, value})` | Inserts a key-value pair (fails if key exists). | O(log n) |
| `map.erase(key)` | Removes a key-value pair by key. | O(log n) |
| `map.find(key)` | Returns an iterator to the key, or `map.end()` if key not found. | O(log n) |

# unordered_map

no specific order

O(1) insertion, deletion and access

no dupes

hash table

| **Operation** | **Description** | **Average Complexity** |
| --- | --- | --- |
| `umap[key]` | Access or modify the value associated with a key (inserts if key doesn't exist). | O(1) |
| `umap.erase(key)` | Removes a key-value pair by key. | O(1) |
| `umap.insert({key, value})` | Inserts a key-value pair (fails if key exists). | O(1) |
| `umap.find(key)` | Returns an iterator to the key, or `umap.end()` if key not found. | O(1) |

# multiset

allows duplicate keys

sorted order

same as red black tree, log complexity for everything

# lower bound

```cpp
#include <algorithm> // Required header

std::lower_bound(start, end, value); // Default comparator
std::lower_bound(start, end, value, comparator); // Custom comparator

```

start is beginnign of range, end is the end

value is waht you search for

finds the first position in `[start, end)` where alue is not less than the elements at that position. Binary search

returns an iterator pointing to that element that is greater than or equal to the value.

if all the elements in the range is less than value it returns end.

{10, 20, 30, 30, 40, 50}

lowerbound(vec.begin(), vec.end(), 30);

this will return an iterator if it ≠ vec.end() then you find it

lower bound for 30 is at index 2 because first value ≥ 30.

{10, 20, 30, 40, 50};

std::lower_bound(vec.begin(), vec.end(), 35);

return index 3, which is 40.

can find index with `it - vec.begin()`

element is `*it` 

# priority_queue

`std::priority_queue<Type, Container, Comparator> pq;`

Container is underlying container which is like vector or smth

comparator is the ordering, will be a default max-heap behaviour

largest element at the top

making it 

`std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // Min-heap`

makes it a min heap

`push(value)` → O(logn)

`pop()` → O(logn)

`top()` → O(1)

`empty()` → O(1)

`size()` → O(1)

# using sort

`std::sort(start_iterator, end_iterator, custom_comparator);`

comparator, defines ordering of two elements a and b

it is a lambda function

`[](const pair<ll , ll>& a, const pair<ll, ll>& b) { }`

```cpp
std::vector<int> nums = {5, 2, 8, 1, 9};

std::sort(nums.begin(), nums.end(), [](int a, int b) {
return a > b; // Descending order
});
```

```cpp
bool customComparator(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

std::sort(pairs.begin(), pairs.end(), customComparator);
```

### Lambda function

```cpp
[](parameterList) -> return type {
 function body
}

most of the time leave capture list and return type empty

auto hey = [](double a) {
}
```

#