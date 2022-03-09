
#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <stdio.h>
#include <string>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker
{
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {}

	~MatchMaker() {}

	std::vector<EmailCount>IdentifyRankedMatches(std::string email, int threshold) const 
	{
		std::vector<EmailCount> myVec;

		return myVec;
	}

private:
	//TODO:
};

#endif 
