#ifndef ATTRIBUTE_TRANSLATOR_INCLUDED
#define ATTRIBUTE_TRANSLATOR_INCLUDED

#include <stdio.h>
#include <string>
#include "provided.h"
#include "RadixTree.h"
#include <vector>

class AttributeTranslator
{
public:
	AttributeTranslator();

	~AttributeTranslator();

	bool Load(std::string filename);

	std::vector<AttValPair>FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<std::vector<AttValPair>>* m_matchPairs;

};

#endif //ATTRIBUTE_TRANSLATOR_INCLUDED
