#include "MemberDatabase.h"
#include "provided.h"
#include <fstream>
#include <iostream>
//#include <sstream>
using namespace std;

MemberDatabase::MemberDatabase()
	:m_email_to_profile(RadixTree<PersonProfile*>()), AV_to_email(RadixTree<std::vector<std::string>*>()),
	m_emails(std::set<std::string>()), m_avs(std::set<std::string>())
	
{}

MemberDatabase::~MemberDatabase()
{
	for (auto it = m_emails.begin(); it != m_emails.end(); it++)
	{
		PersonProfile** pp = m_email_to_profile.search(*it);
		if (pp != nullptr) //found
			delete* pp;
	}

	for (auto it = m_avs.begin(); it != m_avs.end(); it++)
	{
		std::vector<std::string>** emailVec = AV_to_email.search(*it);
		if (emailVec != nullptr)
			delete (*emailVec);
	}
}

bool MemberDatabase::LoadDatabase(string filename)
{
	//Return true if the file was successfully loaded, false otherwise.

	//If two member have the same address, then return false

	//The member data file is a text file with the following format
	/*

	Person 1's name
	Person 1's email address
	Count of a-v pairs for person 1
	att1, v1
	att2, v2
	...

	attN, vN

	Person 2's name
	Person 2's address
	...

	*/

	//Each member record separated by a blank line
	ifstream databaseFile(filename);
	//if (!databaseFile)
		//return false;
	databaseFile.open(filename, ios::in);

	if (databaseFile.is_open())
	{
		std::string name, email, attribute, value, blank;
		int AVCount = 0;

		while (databaseFile.good())
		{
			std::getline(databaseFile, name);
			std::getline(databaseFile, email);

			//if two members hav ethe same email address, return false
			if (m_email_to_profile.search(email) != nullptr)
			{
				return false;
			}

			//get # of a-v pairs for member
			m_emails.insert(email);

			PersonProfile* addMe = new PersonProfile(name, email);
			databaseFile >> AVCount;

			//blank line separating members
			std::getline(databaseFile, blank);

			int i = 0;
			while (i < AVCount)
			{
				std::getline(databaseFile, attribute, ',');
				std::getline(databaseFile, value);

				addMe->AddAttValPair(AttValPair(attribute, value));
				std::vector<std::string>** holdEmails = AV_to_email.search(attribute + value);

				if (holdEmails == nullptr)
				{
					AV_to_email.insert(attribute + value, new std::vector<std::string>);
					holdEmails = AV_to_email.search(attribute + value);
					m_avs.insert(attribute + value);

				}
				(*holdEmails)->push_back(email);
				i++;
			}
			std::getline(databaseFile, blank);
			m_email_to_profile.insert(email, addMe);
			
		}
	}
	return true;
}


std::vector<std::string>MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	//Idenify all members that have the specified a-v pairs and return a vector
	//containing their emails.

	//If no such members, return an empty vector.

	//Challenge: Design a set of data structures that allow us to efficiently
	//find all members that have a specified a-v pair.
	std::vector<std::string> myVec;
	
	
	
	
	return myVec;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	
	return new PersonProfile("", "");
}
