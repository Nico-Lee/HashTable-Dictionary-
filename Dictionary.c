#define _CRT_SECURE_NO_WARNINGS 1
#include"Dictionary.h"

template<class K, class V, class FuncModel = DefaultFunc<K>>
Dictionary<K, V, FuncModel>::Dictionary()
	:_table(NULL)
	, _state(NULL)
	, _size(0)
	, _capacity(0)
{}

//template<class K, class V, class FuncModel = DefaultFunc<K>>
//Dictionary<K, V, FuncModel>::~Dictionary()
//{
//	if (_table != NULL)
//	{
//		delete _table;
//		_table = NULL;
//	}
//	if (_state != NULL)
//	{
//		delete _state;
//		_state = NULL;
//	}
//	_size = 0;
//	_capacity = 0;
//}

template<class K, class V, class FuncModel = DefaultFunc<K>>
Dictionary<K, V, FuncModel>::Dictionary(size_t size)
	:_table(new KV[size])
	, _state(new State[size])
	, _size(0)
	, _capacity(size)
{
	for (size_t i = 0; i < _capacity; ++i)
	{
		_state[i] = EMPTY;
	}
}
template<class K, class V, class FuncModel = DefaultFunc<K>>
size_t Dictionary<K, V, FuncModel>::HashFunc(const K& key)
{
	FuncModel _HF;
	return _HF(key) % _capacity;
}
//template<class K, class V, class FuncModel = DefaultFunc<K>>
//Dic::Dictionary(const Dic& d)
//{
//	
//}
//template<class K, class V, class FuncModel = DefaultFunc<K>>
//Dictionary<K, V, FuncModel>::Dictionary<K, V, FuncModel>& operator=(Dictionary<K, V> d);
template<class K, class V, class FuncModel = DefaultFunc<K>>
void Dictionary<K, V, FuncModel>::Swap(Dictionary<K, V, FuncModel>& d)
{
	swap(_table, d._table);
	swap(_state, d._state);
	swap(_size, d._size);
	swap(_capacity, d._capacity);
}


template<class K, class V, class FuncModel = DefaultFunc<K>>
bool Dictionary<K, V, FuncModel>::Add(const K& key, const V& value)
{
	if (_size * 10 >= _capacity * 8)//载荷因子超过0.8，增容
	{
		Dictionary<K, V, FuncModel> tmp(_capacity * 2 + 1);
		for (size_t i = 0; i < _capacity; ++i)
		{
			if (_state[i] == EXIST)
			{
				KV node(_table[i]._key, _table[i]._value);
				size_t adress = HashFunc(_table[i]._key);
				size_t index = adress;
				size_t flag = 0;
				while (tmp._state[index] == EXIST)
				{
					index = adress + flag*flag;
					while (index >= _capacity)//如果到了散列表的末尾，要返回表的头
					{
						index -= _capacity;
					}
					flag++;
				}
				tmp._table[index] = node;
				tmp._size++;
				tmp._state[index] = EXIST;
			}
		}
		Swap(tmp);
	}
	size_t adress = HashFunc(key);
	size_t index = adress;//adress是不能变的，用index来标记最后的位置
	size_t flag = 0;
	while (_state[index] == EXIST)//二次探测
	{
		index = adress + flag*flag;
		while(index >= _capacity)//如果到了散列表的末尾，要返回表的头
		{
			index -= _capacity;
		}
		flag++;
	}
	KV tmp(key, value);
	_table[index] = tmp;
	_state[index] = EXIST;
	_size++;
	return true;
}
template<class K, class V, class FuncModel = DefaultFunc<K>>
bool Dictionary<K, V, FuncModel>::Delete(const K& key)
{
	size_t index = Find(key);
	if (index >= 0)
	{
		_state[index] = DELETE;
		_size--;
		return true;
	}
	return false;
}

template<class K, class V, class FuncModel = DefaultFunc<K>>
size_t Dictionary<K, V, FuncModel>::Find(const K& key)
{
	size_t adress = HashFunc(key);
	size_t index = adress;
	for (size_t flag = 0; flag < _capacity;)
	{
		if (_table[index]._key == key)//二次探测
		{
			return index;
		}
		index = adress + flag*flag;
		while (index >= _capacity)
		{
			index -= _capacity;
		}
		flag++;
	}
	return -1;
}


template<class K, class V, class FuncModel = DefaultFunc<K>>
bool Dictionary<K, V, FuncModel>::
Alter(const K& key,const K& newkey,const V& newvalue)
{
	size_t index = Find(key);
	if (index > 0)
	{
		_table[index]._key = newkey;
		_table[index]._value = newvalue;
		return true;
	}
	return false;
}
template<class K, class V, class FuncModel = DefaultFunc<K>>
void Dictionary<K, V, FuncModel>::Print()
{
	for (size_t i = 0; i < _capacity; i++)
	{
		if (_state[i] == EXIST)
		{
			printf("Table[%d]->Exist:  ", i);
			cout << _table[i]._key << "——" << _table[i]._value;
		}
		else if (_state[i] == DELETE)
		{
			printf("Table[%d]->Delete:  ", i);
			cout << _table[i]._key << "——" << _table[i]._value;
		}
		else
		{
			printf("Table[%d]->Empty", i);
		}
		cout << endl;
	}
}
