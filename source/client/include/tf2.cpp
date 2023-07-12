#include "tf2.h"
#include "util.h"
#include "json.h"

bool tf2::is_a_cheater_unoptimized(int friendsid)
{
	if (friendsid <= 0)
		return false;

	static bool once = false;
	if (!once)
	{// make sure this is sorted
		std::sort(util::m_downloaded_cheater_list.begin(), util::m_downloaded_cheater_list.end());
		once = true;
	}

	return std::binary_search(util::m_downloaded_cheater_list.begin(), util::m_downloaded_cheater_list.end(), 0x0110000100000000ULL + friendsid);
}