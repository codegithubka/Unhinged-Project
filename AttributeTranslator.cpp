#include <iostream>
#include <fstream>
#include <string>
#include "AttributeTranslator.h"

AttributeTranslator::AttributeTranslator()
	:m_matchPairs(new RadixTree<std::vector<AttValPair>>)
{}

AttributeTranslator::~AttributeTranslator()
{
	delete m_matchPairs;
}

//Load the translator file
bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream translatorFile(filename);
	translatorFile.open(filename);

	if (translatorFile.is_open())
	{
		std::string srcAt, srcVal;
		std::string destAt, destVal;
		std::string blank;

		while (translatorFile.good())
		{
			//source_attribute, source_value, 
			//compatible_attribute, compatible_value
			std::getline(translatorFile, srcAt, ',');
			std::getline(translatorFile, srcVal, ',');
			std::getline(translatorFile, destAt, ',');
			std::getline(translatorFile, destVal, ',');

			std::string srcPair(srcAt + srcVal);
			AttValPair destPair(destAt, destVal);

			std::vector<AttValPair>* searchSrc = m_matchPairs->search(srcPair);
			if (searchSrc == nullptr)
			{
				m_matchPairs->insert(srcAt, std::vector<AttValPair>());
			}

			auto it = searchSrc->begin();
			while (it != searchSrc->end())
			{
				if ((*it) == destPair)
				{
					break;
				}
				it++;
			}
			if (it == searchSrc->end())
			{
				std::vector<AttValPair>* newSearchSrc = new std::vector<AttValPair>(*searchSrc);

				newSearchSrc->push_back(destPair);
				m_matchPairs->insert(srcPair, *newSearchSrc);
				delete newSearchSrc;
			}
			


		}
	}
	return true;
}

std::vector<AttValPair>AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	//Identify all compatible a-v pairs for the specified source a-v pair in an efficient
//manner and return a vector containing them.

//If there are 0 compatible pairs, return empty vector. No order required. No duplicates!
	std::vector<AttValPair> myVec;

	std::string searchMe = source.attribute + source.value;
	std::vector<AttValPair>* compatibleVec = m_matchPairs->search(searchMe);

	if (compatibleVec != nullptr)
	{
		myVec = *compatibleVec;
	}
	//return a vector with 0 or more compatible pairs for the source a-v pair
	return myVec;
}




