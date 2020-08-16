#pragma once
#include "SDK.h"
#include <string>

class match_title;
class match_extensions;
class match_events_subscription;
class match_network_msg_controller;
class match_system;

namespace SDK
{
	class match_session 
	{
	public:
		virtual KeyValues* get_session_system_data() = 0; // 0
		virtual KeyValues* get_session_settings() = 0; // 1
		virtual void update_session_settings(KeyValues* settings) = 0; // 2
		virtual void command(KeyValues* command) = 0; // 3
	};

	class IMatchFramework : public IAppSystem 
	{
	public:
		virtual void run_frame() = 0; // 9
		virtual match_extensions* get_match_extensions() = 0; // 10
		virtual match_events_subscription* get_events_subscription() = 0; // 11
		virtual match_title* get_match_title() = 0; // 12
		virtual match_session* get_match_session() = 0; // 13
		virtual match_network_msg_controller* get_msg_controller() = 0; // 15
		virtual match_system* get_match_system() = 0; // 15
		virtual void create_session(KeyValues* settings) = 0; // 16
		virtual void match_session(KeyValues* settings) = 0; // 17
		virtual void accept_invite(int controller) = 0; // 18
		virtual void close_session() = 0; // 19
	};
}
