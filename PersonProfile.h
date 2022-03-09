#ifndef PERSONPROFILE_H
#define PERSONPROFILE_H

#include "RadixTree.h"
#include <set>
#include <vector>

struct AttValPair;

class PersonProfile
{
public:
	PersonProfile(std::string name, std::string email);

	~PersonProfile();

	std::string GetName() const;

	std::string GetEmail() const;

	void AddAttValPair(const AttValPair& attval);

	int GetNumAttValPairs() const;

	bool GetAttVal(int attribute_num, AttValPair&  attval) const;
private:

	std::string m_name;
	std::string m_email;

	RadixTree<std::set<std::string>>*m_tree;
	std::vector<AttValPair*> myVec;
};

#endif //PERSON_PROFILE_H
