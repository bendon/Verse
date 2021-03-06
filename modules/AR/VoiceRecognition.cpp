/* 
 * File:   MarkerDetection.cpp
 * Author: damiles
 * 
 * Created on 15 de febrero de 2012, 15:22
 */

#include "VoiceRecognition.h"

using namespace std;

namespace AR{

	/* Sleep for specified msec */
	static void
	sleep_msec(int32 ms)
	{
#if (defined(WIN32) )
		Sleep(ms);
#else
		/* ------------------- Unix ------------------ */
		struct timeval tmo;

		tmo.tv_sec = 0;
		tmo.tv_usec = ms * 1000;

		select(0, NULL, NULL, NULL, &tmo);
#endif
}



	/*
	 * Main utterance processing loop:
	 *     for (;;) {
	 * 	   wait for start of next utterance;
	 * 	   decode utterance until silence of at least 1 sec observed;
	 * 	   print utterance result;
	 *     }
	 */
	static void
	*VoiceRecognition_Process(void *arg)
	{
		ad_rec_t *ad;
		int16 adbuf[4096];
		int32 k, ts, rem;
		char const *hyp;
		char const *uttid;
		cont_ad_t *cont;
		char word[256];

		VoiceRecognition *voiceRecognition=(VoiceRecognition*)arg;
		Events::VoiceEvent e;
		e.target=voiceRecognition;
		
		if ((ad = ad_open_dev(cmd_ln_str_r(voiceRecognicionConfig, "-adcdev"),
							  (int)cmd_ln_float32_r(voiceRecognicionConfig, "-samprate"))) == NULL)
			E_FATAL("Failed top open audio device\n");

		/* Initialize continuous listening module */
		if ((cont = cont_ad_init(ad, ad_read)) == NULL)
			E_FATAL("Failed to initialize voice activity detection\n");
		if (ad_start_rec(ad) < 0)
			E_FATAL("Failed to start recording\n");
		if (cont_ad_calib(cont) < 0)
			E_FATAL("Failed to calibrate voice activity detection\n");

		for (;;) {
			/* Indicate listening for next utterance */
			printf("READY....\n");
			e.type=Events::VoiceEvent::VOICE_READY;
			voiceRecognition->dispatchEvent(&e);

			fflush(stdout);
			fflush(stderr);

			/* Wait data for next utterance */
			while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
				sleep_msec(100);

			if (k < 0)
				E_FATAL("Failed to read audio\n");

			/*
			 * Non-zero amount of data received; start recognition of new utterance.
			 * NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
			 */
			if (ps_start_utt(ps, NULL) < 0)
				E_FATAL("Failed to start utterance\n");
			ps_process_raw(ps, adbuf, k, FALSE, FALSE);
			printf("Listening...\n");
			e.type=Events::VoiceEvent::VOICE_LISTENING;
			voiceRecognition->dispatchEvent(&e);

			fflush(stdout);

			/* Note timestamp for this first block of data */
			ts = cont->read_ts;

			/* Decode utterance until end (marked by a "long" silence, >1sec) */
			for (;;) {
				/* Read non-silence audio data, if any, from continuous listening module */
				if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
					E_FATAL("Failed to read audio\n");
				if (k == 0) {
					/*
					 * No speech data available; check current timestamp with most recent
					 * speech to see if more than 1 sec elapsed.  If so, end of utterance.
					 */
					if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
						break;
				}
				else {
					/* New speech data received; note current timestamp */
					ts = cont->read_ts;
				}

				/*
				 * Decode whatever data was read above.
				 */
				rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

				/* If no work to be done, sleep a bit */
				if ((rem == 0) && (k == 0))
					sleep_msec(20);
			}

			/*
			 * Utterance ended; flush any accumulated, unprocessed A/D data and stop
			 * listening until current utterance completely decoded
			 */
			ad_stop_rec(ad);
			while (ad_read(ad, adbuf, 4096) >= 0);
			cont_ad_reset(cont);

			printf("Stopped listening, please wait...\n");
			fflush(stdout);
			/* Finish decoding, obtain and print result */
			ps_end_utt(ps);
			hyp = ps_get_hyp(ps, NULL, &uttid);
			printf("%s: %s\n", uttid, hyp);
			e.type=Events::VoiceEvent::VOICE_RECOGNIZED;
			e.data=hyp;
			voiceRecognition->dispatchEvent(&e);

			fflush(stdout);

			/* Exit if the first word spoken was GOODBYE */
			if (hyp) {
				sscanf(hyp, "%s", word);
				if (strcmp(word, "goodbye") == 0)
					break;
			}

			/* Resume A/D recording for next utterance */
			if (ad_start_rec(ad) < 0)
				E_FATAL("Failed to start recording\n");
		}

		cont_ad_close(cont);
		ad_close(ad);

		return NULL;
	}


	VoiceRecognition* VoiceRecognition::pinstance=0;
	VoiceRecognition* VoiceRecognition::Instance()
	{
		if (pinstance == 0 )
		{
				pinstance = new VoiceRecognition;
		}
		return pinstance;	
	}

	VoiceRecognition::VoiceRecognition(){

	}

	VoiceRecognition::~VoiceRecognition(){
		//Kill thread for voice recognition
		pthread_cancel(vr_tid);
	}

	int VoiceRecognition::init(string dict, string lm, string hmm){
		//Init the voiceRecognicionConfig variable
		voiceRecognicionConfig = cmd_ln_init(NULL, ps_args(), TRUE,
                             "-hmm", hmm.c_str(),
                             "-lm", lm.c_str(),
                             "-dict", dict.c_str(),NULL);
        if (voiceRecognicionConfig == NULL)
                return 0;

		ps = ps_init(voiceRecognicionConfig);
		if (ps == NULL)
			return 0;
		//create thread
		int error=pthread_create(&vr_tid,
				NULL, /* default attributes please */
				VoiceRecognition_Process,
				(void *)this);
	}
}

