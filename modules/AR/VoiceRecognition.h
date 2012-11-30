/* 
 * File:   VoiceRecognition.h
 * Author: damiles
 *
 * Created on 12 November de 2012, 07:19
 */

#ifndef VOICERECOGNITION_H
#define	VOICERECOGNITION_H

#include <Core/EventDispatcher.h>
#include <Events/VoiceEvent.h>


//CMU Sphinx helper includes
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <setjmp.h>

#if defined(WIN32)
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

//CMU Sphinx includes
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>
#include <pocketsphinx.h>

//For threads
#include <pthread.h>
using namespace std;
namespace AR{
	//Function for thread process
	static void *VoiceRecognition_Process(void *arg);
	static void sleep_msec(int32 ms);

	//Varialbes for Voice Recognition
	static ps_decoder_t *ps;
	static cmd_ln_t *voiceRecognicionConfig;
	//Thread variable tid (voice recognition thread id)		
	static pthread_t vr_tid;

	class VoiceRecognition: public Core::EventDispatcher {
	public:
		static VoiceRecognition* Instance();
		int init(string dict, string lm, string hmm);
		~VoiceRecognition();

	protected:
		VoiceRecognition();
		static VoiceRecognition* pinstance;

	private:
		
		
	};

}
#endif	/* VOICERECOGNITION_H */

