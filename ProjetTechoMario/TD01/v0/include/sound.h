
#ifndef SOUND_IS_DEF
#define SOUND_IS_DEF

#define SOUND_PLAYLIST_SIZE 4

void sound_init (int enable, int music_ok);
void sound_clean ();

int sound_start_music ();
void sound_keep_music ();
void sound_stop_music ();
void sound_pause_music ();
void sound_resume_music ();
void sound_next_music ();
void sound_fade_channel (int channel, int ms);
void sound_stop_channel (int channel);
int sound_channel_playing (int channel);

enum {
  SOUND_BING,
  SOUND_BOUM,
  SOUND_CLOC,
  SOUND_OUH,
  SOUND_PLOP,
  SOUND_PSCHH,
  SOUND_SHOT,
  SOUND_YEEHA,
  NB_SOUNDS
};

int play_sound (unsigned sound);


#endif
