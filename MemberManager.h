#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include "Member.h"

class MemberManager {
	std::vector<Member> members;

public:
	void addMember(Member&);					//Add a member to the members vector
	void removeMember(Member&);					//Remove a member from the members vector

	bool isMember(Member&);						//See if the members vector has member

	Member& getInstanceOfMember(Member&);		//Get the instance of a member

	std::vector<Member>& getMemberVector() { return members; }

	void updateMemberEntry(Member);
};

#endif