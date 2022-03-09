#ifndef RADIX_TREE_H
#define RADIX_TREE_H


#include <map>
#include <string>


template<typename ValueType>
class RadixTree
{
public:
	RadixTree();

	~RadixTree();

	void insert(std::string key, const ValueType& value);

	ValueType* search(std::string key) const;
private:
	std::map<std::string, ValueType*> m_map;
};

template<typename ValueType>
RadixTree<ValueType>::RadixTree()
	:m_map(new std::map<std::string, ValueType*>())
{}

template<typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
	for (auto it = m_map->begin(); it != m_map->end(); ++it)
		delete it->second;
	delete m_map;
}

template<typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType & value)
{
	auto it = m_map->find(key);
	if (it != m_map->end())
	{
		delete it->second;
	}
	ValueType* val = new ValueType(value);
	m_map[key] = val;
}

template<typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
	auto it = m_map->find(key);
	//if the key is found, then return the corresponding value
	if (it != m_map->end())
	{
		return it->second;
	}
	//If not found, return null
	return nullptr;
}

#endif //RADIX_TREE_INCLUDED



