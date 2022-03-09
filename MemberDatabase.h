#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H

#include <vector>
#include "PersonProfile.h"
#include <stdio.h>
#include <string>
#include "RadixTree.h"

struct AttValPair;

class MemberDatabase
{
public:
	MemberDatabase();

	bool LoadDatabase(std::string filename);

	std::vector<std::string>FindMatchingMembers(const AttValPair& input) const;

	const PersonProfile* GetMemberByEmail(std::string email) const;

	void findMemberByEmail(const MemberDatabase* md, std::string member_email) {}

	~MemberDatabase();

private:
	RadixTree<std::vector<std::string>*> AV_to_email;
	RadixTree<PersonProfile*> m_email_to_profile;
	std::set<std::string> m_emails;
	std::set<std::string> m_avs;
};

#endif //MEMBER_DATABASE_H

