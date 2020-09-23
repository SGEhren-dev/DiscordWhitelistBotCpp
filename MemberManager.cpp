#include "MemberManager.h"

/// <summary>
/// Add a member to the members vector
/// </summary>
/// <param name="m">Member to be added</param>
void MemberManager::addMember(Member& m) {
	this->members.push_back(m);
}

/// <summary>
/// Remove a member from the members vector (By MemberID)
/// </summary>
/// <param name="m">Member to be removed</param>
void MemberManager::removeMember(Member& m) {
	std::vector<Member>::iterator it;

	for (it = members.begin(); it != members.end(); it++) {
		if (it->getMemberID() == m.getMemberID()) {
			members.erase(it);
		}
	}
}

/// <summary>
/// Find a member and return if they exist (By MemberID)
/// </summary>
/// <param name="m">Member to find</param>
/// <returns>True if member, false if not</returns>
bool MemberManager::isMember(Member& m) {
	std::vector<Member>::iterator it;

	for (it = members.begin(); it != members.end(); it++) {
		if (it->getMemberID() == m.getMemberID())
			return true;
	}
	return false;
}

Member& MemberManager::getInstanceOfMember(Member& m) {
	std::vector<Member>::iterator it;

	for (it = members.begin(); it != members.end(); it++) {
		if (it->getMemberID() == m.getMemberID())
			return *it;
	}
	return Member();
}

void MemberManager::updateMemberEntry(Member m) {
	std::vector<Member>::iterator it;

	for (it = members.begin(); it != members.end(); it++) {
		if (it->getMemberID() == m.getMemberID()) {
			members.erase(it);
		}
	}
	members.push_back(m);
}