#include "VoiceEvent.h"

namespace Events {
	
	const std::string VoiceEvent::VOICE_READY= "VoiceReady";
    const std::string VoiceEvent::VOICE_LISTENING= "VoiceListening";
	const std::string VoiceEvent::VOICE_RECOGNIZED="VoiceRecognized";

	VoiceEvent::VoiceEvent(){
		data="";
	}

} /* End of namespace Events */
