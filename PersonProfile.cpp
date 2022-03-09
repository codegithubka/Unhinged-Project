#include "PersonProfile.h"
#include "provided.h"
#include <iostream>
#include <vector>
#include <string>

PersonProfile::PersonProfile(std::string name, std::string email)
	:m_name(name), m_email(email)
{
	m_tree = new RadixTree<std::set<std::string>>;
	myVec = std::vector<AttValPair*>();
}

PersonProfile::~PersonProfile()
{
	for (auto it = myVec.begin(); it != myVec.end(); it++)
	{
		std::set<std::string>* as = m_tree->search((*it)->value);
		if (as != nullptr)
		{
			delete as;
		}
		delete (*it);
	}
	delete m_tree;
}

std::string PersonProfile::GetName() const
{
	return m_name;
}

std::string PersonProfile::GetEmail() const
{
	return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	//add a-v pair; if the pair already exists do nothing
	std::set<std::string>* findAtt;
	findAtt = m_tree->search(attval.attribute);

	if (findAtt == nullptr)
	{
		m_tree->insert(attval.attribute, std::set<std::string>());
		findAtt = m_tree->search(attval.attribute);
	}

	//An attribute can map to more than one value as long as the
	//corresponding values are different

	if (findAtt->find(attval.value) == findAtt->end())
	{
		//the new value does not exist

		std::set<std::string>* newAV = new std::set<std::string>(*findAtt);
		newAV->insert(attval.value);

		//insert the new pair into the tree
		m_tree->insert(attval.attribute, *newAV);
		myVec.push_back(new AttValPair(attval));

		delete newAV;
	}
}

int PersonProfile::GetNumAttValPairs() const
{
	return myVec.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	//if the attribute is successfully retrieved
		//get the pair attribute_num and place it in the attval param
		//return true
	//return false
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
		return false;

	attval = *myVec[attribute_num];
	return true;
}