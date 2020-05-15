#include <SDL_mixer.h>
#include <stdlib.h>
#include <time.h>

#include "sound.h"
#include "error.h"

static Mix_Chunk *sounds [NB_SOUNDS];
static char *sound_files [NB_SOUNDS] =
  {
    "sons/bing.wav",
    "sons/boum.wav",
    "sons/cloc.wav",
    "sons/ouh.wav",
    "sons/plop.wav",
    "sons/pschh.wav",
    "sons/shot.wav",
    "sons/yeeha.wav"
  };

Mix_Music *music [SOUND_PLAYLIST_SIZE];

static int sound_enabled = 1;
static int music_enabled = 1;
static int current_track;

void sound_init (int enable, int music_ok)
{
  if (!enable) {
    sound_enabled = 0;
    return;
  }

  if (!music_ok)
    music_enabled = 0;

  if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0)
    exit_with_error ("Mix_OpenAudio");

  Mix_Volume (-1, MIX_MAX_VOLUME);
  Mix_VolumeMusic (MIX_MAX_VOLUME / 2);

  for (int i = 0; i < NB_SOUNDS; i++) {
    sounds[i] = Mix_LoadWAV (sound_files[i]);
    if (sounds[i] == NULL)
      exit_with_error ("Mix_LoadWAV(%s)", sound_files[i]);
    Mix_VolumeChunk (sounds[i], MIX_MAX_VOLUME);
  }

  for (int i = 0; i < SOUND_PLAYLIST_SIZE; i++) {
    char name [128];

    // First try to load .MP3 file
    sprintf (name, "sons/%s-%d.mp3", "music", i);
    music [i] = Mix_LoadMUS (name);
    if (music [i] == NULL) {
      // Second attempt: fall back to .WAV format
      sprintf (name, "sons/%s-%d.wav", "music", i);
      music [i] = Mix_LoadMUS (name);
      if (music [i] == NULL)
	      exit_with_error ("Mix_LoadMUS (\"%s\")", name);
    }
  }

  srand(time(NULL));
  current_track = rand() % SOUND_PLAYLIST_SIZE;
}

int sound_start_music ()
{
  if (sound_enabled && music_enabled) {
    return Mix_PlayMusic (music [current_track], -1);
  }

  return -1;
}

void sound_keep_music ()
{
  if (sound_enabled && music_enabled) {
    if (Mix_PlayingMusic () == 0) {
      //Play the music
      sound_next_music ();
    }
  }
}

void sound_pause_music ()
{
  if (sound_enabled)
    Mix_PauseMusic ();
}

void sound_resume_music ()
{
  if (sound_enabled)
    Mix_ResumeMusic ();
}

void sound_stop_music ()
{
  if (sound_enabled)
    Mix_HaltMusic ();
}

void sound_fade_channel (int channel, int ms)
{
  if (sound_enabled)
    Mix_FadeOutChannel (channel, ms);
}

void sound_stop_channel (int channel)
{
  if (sound_enabled)
    Mix_HaltChannel (channel);
}

void sound_next_music ()
{
  sound_stop_music ();

  current_track = (current_track + 1) % SOUND_PLAYLIST_SIZE;

  sound_start_music ();
}

int sound_channel_playing (int channel)
{
  return Mix_Playing (channel);
}

int play_sound (unsigned sound)
{
  if (sound >= NB_SOUNDS)
    exit_with_error ("play_sound");

  if (sound_enabled)
    return Mix_PlayChannel (-1, sounds [sound], 0);

  return -1;
}

void sound_clean ()
{
  if (sound_enabled) {
    for (int i = 0; i < NB_SOUNDS; i++)
      Mix_FreeChunk (sounds[i]);
    
    for (int i = 0; i < SOUND_PLAYLIST_SIZE; i++)
      Mix_FreeMusic (music [i]);
  }
}
