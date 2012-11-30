#ifndef Events_VoiceEvent_h
#define Events_VoiceEvent_h

#include "Event.h"


namespace Events {

class VoiceEvent : public Event {
public:
	VoiceEvent();
    std::string data;
    static const std::string VOICE_READY;
    static const std::string VOICE_LISTENING;
	static const std::string VOICE_RECOGNIZED;
};

} /* End of namespace Events */

#endif // Events_VoiceEvent_h
