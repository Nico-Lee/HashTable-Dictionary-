#pragma once
#include<iostream>
#include<string>
using namespace std;
enum State
{
	EXIST,
	EMPTY,
	DELETE
};

template<class K,class V>
struct Key_Value
{
	K _key;
	V _value;
	Key_Value(const K& key=K(), const V& value=V())
		:_key(key)
		, _value(value)
	{}
};
template<class T>
struct DefaultFunc
{
	size_t operator()(const T& data)
	{
		return (size_t)data;
	}
};

struct StringFunc
{
	size_t operator()(const string& str)
	{
		size_t sum = 0;
		for (size_t i = 0; i < str.size(); ++i)
		{
			sum += str[i];
		}
		return sum;
	}
};


template<class K,class V,class FuncModel=DefaultFunc<K>>
class Dictionary
{
	typedef Key_Value<K, V> KV;
public:
	Dictionary();
	//~Dictionary();
	//可以传入数值初始化字典的大小，但是最好在内部用素数表控制_capacity，Mod素数的哈希冲突较少
	Dictionary(size_t size);
	Dictionary(const Dictionary<K,V,FuncModel>& d);
	Dictionary<K, V, FuncModel>& operator=(Dictionary<K, V, FuncModel> d);
	bool Add(const K& key, const V& value);
	bool Delete(const K& key);
	size_t Find(const K& key);
	bool Alter(const K& key,const K& newkey,const V& newvalue);
	void Print();
protected:
	size_t HashFunc(const K& key);
	void Swap(Dictionary<K, V, FuncModel>& d);
protected:
	KV* _table;
	State* _state;
	size_t _size;
	size_t _capacity;
};
