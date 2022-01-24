
//
//
// Module to load sounds from file and playing them from a mixer
//
//

#ifndef _MIXER_H_
#define _MIXER_H_

#include "base.h"
#include "platform.h"
#define STB_VORBIS_HEADER_ONLY
#include "third_party/stb_vorbis.h"

#define MAX_SOUNDS 256
#define MAX_TRACKS 16


typedef enum {
	PLAY_SOUND_FLAG_NONE    = 0x0,
	PLAY_SOUND_FLAG_INVALID = 0x1,
	PLAY_SOUND_FLAG_LOOP    = 0x2,
	PLAY_SOUND_FLAG_PAUSED  = 0x4,
} PlaySoundFalgs;

typedef u8 TrackHandle;

/*
* Mixer_setup
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Setups the mixer to be ready to use, this function must be called
* before any other functions in this API.
*
* To clean the mixer resources, the function Mixer_cleanup must be called.
*
* VARIABLES
* -------------------------------------------------------------------
* sample_rate: The sample_rate that will be used by the mixer.
* num_channels: The number of channels that the mixer will use.
*
*/
void
Mixer_setup(u32 sample_rate, u32 num_channels);


/*
* Mixer_cleanup
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Cleans the mixer resources, this function must be called after
* finalize the usage of the mixer.
*
* WARNING WARNING, Mixer_play_frames cannot be running at the moment
* this function is called.
*
*/
void
Mixer_cleanup();


/*
* Mixer_load_sound
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Loads and decodes a ogg music file.
*
* The song will be ressampled based on the mixer's sample rate and the
* channels will be merged and divided between the mixer's number of channels.
*
* VARIABLES
* -------------------------------------------------------------------
* filename: Filename of the song.
*
* RETURNS
* -------------------------------------------------------------------
* u32: Id of the song, 0 in case of failure.
*
*/
u32
Mixer_load_sound(const char *filename);



/*
* Mixer_clear_tracks
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Removes all the current playing tracks.
*
*/
void
Mixer_clear_tracks();


/*
* Mixer_pause_all_tracks
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Puts all currently playing tracks into pause state.
*
*/
void
Mixer_pause_all_tracks();


/*
* Mixer_resume_all_tracks
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Resumes all currently paused tracks.
*
*/
void
Mixer_resume_all_tracks();


/*
* Mixer_toggle_all_tracks
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Pauses all playing tracks and resumes all paused tracks.
*
*/
void
Mixer_toggle_all_tracks();






/*
* Mixer_play_sound
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Adds a new track on the mixer to play the sound passed.
* If we already arrived to MAX_TRACKS the sound will not play.
*
* There are 2 valid modes:
*   PLAY_SOUND_MODE_LOOP plays the sound on loop. The only way to
*     stop this is with Mixer_clear_tracks.
*   PLAY_SOUND_MODE_NORMAL plays the sound and the track will be removed
*     as soon as the sound terminates.
*
* VARIABLES
* -------------------------------------------------------------------
* sound_id: The id of the sound to play.
* mode: The possible mode PLAY_SOUND_MODE_LOOP/PLAY_SOUND_MODE_NORMAL.
* volume: The volume level. (1 is 100% and 0 is 0%)
* handle: Id to manage a the track from outside, this must point to a valid memory during the track,
*   is alive, you should not pass the same handle if another track is using it. If you don't want to
*   manage the track this value can be NULL
*
*/
void
Mixer_play_sound(u32 sound_id, u8 flags, f32 volume, TrackHandle *handle);


/*
* Mixer_play_frames
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Plays the samples in the buffer passed.
* This function must be called to put the samples on the whathever
* sound player.
*
* Assumes that the buffer receives samples interlaced by the number
* of channels configured on the mixer.
*
* If a track is in normal mode and finishes will be removed here.
*
* VARIABLES
* -------------------------------------------------------------------
* buffer: Buffer where output the samples.
* buffer_size: Size of the buffer.
*
*/
void
Mixer_play_frames(f32* buffer, u32 buffer_size);



/*
* Mixer_pause_track
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Pauses the track identified by the handle passed. 
* If the handle doesn't identifies any track the function will return
* false.
*
* If the track is already paused does nothing and returns true.
*
* VARIABLES
* -------------------------------------------------------------------
* handle: the handle (Asserts that isn't null)
*
* RETURNS
* -------------------------------------------------------------------
* bool: If the track was found
*
*/
bool
Mixer_pause_track(TrackHandle *handle);


/*
* Mixer_resume_track
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Resumes the track identified by the handle passed. 
* If the handle doesn't identifies any track the function will return
* false.
*
* If the track is already playing does nothing and also returns true.
*
* VARIABLES
* -------------------------------------------------------------------
* handle: the handle (Asserts that isn't null)
*
* RETURNS
* -------------------------------------------------------------------
* bool: If the track was found
*
*/
bool
Mixer_resume_track(TrackHandle *handle);


/*
* Mixer_remove_track
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Removes the track identified by the handle passed. 
* If the handle doesn't identifies any track the function will return
* false.
*
* VARIABLES
* -------------------------------------------------------------------
* handle: the handle (Asserts that isn't null)
*
* RETURNS
* -------------------------------------------------------------------
* bool: If the track was found
*
*/
bool
Mixer_remove_track(TrackHandle *handle);


/*
* Mixer_set_track_volume
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Sets the volume of the track identified by the handle passed. 
* If the handle doesn't identifies any track the function will return
* false.
*
* VARIABLES
* -------------------------------------------------------------------
* handle: the handle (Asserts that isn't null)
*
* RETURNS
* -------------------------------------------------------------------
* bool: If the track was found
*
*/
bool
Mixer_set_track_volume(TrackHandle *handle, f32 volume);


typedef struct {
	i16 *samples;
	u32 n_samples;
} Sound;

typedef struct {
	u32 sound_id;
	u32 current_sample;
	f32 volume;
} SoundTrack;


static struct {
	Sound sounds[MAX_SOUNDS];
	u32 sound_count;
	SoundTrack tracks[MAX_TRACKS];
	u8 tracks_flags[MAX_TRACKS];   // Mode of each track
	TrackHandle *tracks_handles[MAX_TRACKS]; // Handles to manage the tracks from outside
	u32 sample_rate;
	u32 num_channels;
	Mutex mutex;
} mixer_data = {0};


// Documented above
void
Mixer_setup(u32 sample_rate, u32 num_channels) {
	mixer_data.sample_rate  = sample_rate;
	mixer_data.num_channels = num_channels;
	Mutex_init(&mixer_data.mutex);

	Mixer_clear_tracks();

	// We start the sound count on 1 because the first sound is always invalid
	mixer_data.sound_count = 1;
}


// Documented above
void
Mixer_cleanup() {
	Mixer_clear_tracks(); // Clear tracks uses the mutex so we have to call before the Mutex_deinit
	Mutex_deinit(&mixer_data.mutex);

	// free all allocated sample buffers
	for (u32 i = 1; i < mixer_data.sound_count; ++i) {
		free(mixer_data.sounds[i].samples);
		mixer_data.sounds[i].samples   = NULL;
		mixer_data.sounds[i].n_samples = 0;
	}

	// First sound_count is invalid always, so we set the count to 1
	mixer_data.sound_count = 1;
}




// Documented above
void
Mixer_clear_tracks() {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			mixer_data.tracks_flags[i]   = PLAY_SOUND_FLAG_INVALID;
			mixer_data.tracks_handles[i] = NULL;
		}
	}
	Mutex_unlock(&mixer_data.mutex);
}



// Documented above
void
Mixer_pause_all_tracks() {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_INVALID) {
				continue;
			}
			mixer_data.tracks_flags[i] |= PLAY_SOUND_FLAG_PAUSED;
		}
	}
	Mutex_unlock(&mixer_data.mutex);
}


// Documented above
void
Mixer_resume_all_tracks() {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_INVALID) {
				continue;
			}
			mixer_data.tracks_flags[i] &= (~PLAY_SOUND_FLAG_PAUSED);
		}
	}
	Mutex_unlock(&mixer_data.mutex);
}




// Documented above
void
Mixer_toggle_all_tracks() {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_INVALID) {
				continue;
			}
			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_PAUSED) {
				mixer_data.tracks_flags[i] &= (~PLAY_SOUND_FLAG_PAUSED);
			}
			else {
				mixer_data.tracks_flags[i] |= PLAY_SOUND_FLAG_PAUSED;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
}



// Documented above
bool
Mixer_pause_track(TrackHandle *handle) {
	Assert(handle != NULL, "The handle cannot be NULL");
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_handles[i] == handle) {
				mixer_data.tracks_flags[i] |= PLAY_SOUND_FLAG_PAUSED;
				Mutex_unlock(&mixer_data.mutex);
				return true;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
	return false;
}


// Documented above
bool
Mixer_resume_track(TrackHandle *handle) {
	Assert(handle != NULL, "The handle cannot be NULL");
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_handles[i] == handle) {
				mixer_data.tracks_flags[i] &= (~PLAY_SOUND_FLAG_PAUSED);
				Mutex_unlock(&mixer_data.mutex);
				return true;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
	return false;
}



// Documented above
bool
Mixer_remove_track(TrackHandle *handle) {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_handles[i] == handle) {
				mixer_data.tracks_flags[i]   = PLAY_SOUND_FLAG_INVALID;
				mixer_data.tracks_handles[i] = NULL;
				Mutex_unlock(&mixer_data.mutex);
				return true;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
	return false;
}


// Documented above
bool
Mixer_set_track_volume(TrackHandle *handle, f32 volume) {
	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_handles[i] == handle) {
				mixer_data.tracks[i].volume = volume;
				Mutex_unlock(&mixer_data.mutex);
				return true;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
	return false;
}


static void
Resample_chunk_with_diff_channels(
		i16 *dst_samples_buffer,
		u32 start_pos,
		u32 dst_chunk_len,
		u32 dst_channels,
		u32 dst_sample_rate,
		f32 **src_samples,
		u32 src_channels,
		u32 src_sample_rate) {

	for (u32 sample = 0; sample < dst_chunk_len; ++sample) {

		f32 sample_val_f32 = 0.0f;

		/// Resample the frame to fit with the new sample ratio

		// Calculate the start and the end of the samples that fits on 1 output sample
		u32 start_s = sample * src_sample_rate / dst_sample_rate;
		u32 end_s   = (sample + 1) * src_sample_rate / dst_sample_rate;
		
		// We iterate over all the source channels to merge them
		for (u32 src_chan = 0; src_chan < src_channels; ++src_chan) {
			// Store the first sample (If we are contracting the sound we only will store this)
			f32 val_f32 = src_samples[src_chan][start_s];

			// If we are expanding the sound we calculate the mean of the group of samples
			for (u32 s = start_s+1; s < end_s; ++s) {
				val_f32 += src_samples[src_chan][s];
			}
			if (end_s - start_s > 0) {
				val_f32 /= (f32)(end_s - start_s);
			}
			
			// Merge the channels
			sample_val_f32 += val_f32;

		}

		// Unmerge the channels, now it is like mono
		sample_val_f32 /= (f32)src_channels;

		// Store the value as i16 (We clamp it)
		i32 val = (i32)(sample_val_f32*32767.0f);
		if      (val > 32767)  {val = 32767;}
		else if (val < -32768) {val = -32768;}

		for (u32 channel = 0; channel < dst_channels; ++channel) {
			// Calculate the destination position
			u32 pos   = (start_pos+sample)*dst_channels+channel;

			dst_samples_buffer[pos] = (i16)val;
		}
	}
}

static void
Resample_chunk_with_eq_channels(
		i16 *dst_samples_buffer,
		u32 start_pos,
		u32 dst_chunk_len,
		u32 dst_channels,
		u32 dst_sample_rate,
		f32 **src_samples,
		u32 src_sample_rate) {

	for (u32 sample = 0; sample < dst_chunk_len; ++sample) {

		/// Resample the frame to fit with the new sample ratio

		// Calculate the start and the end of the samples that fits on 1 output sample
		u32 start_s = sample * src_sample_rate / dst_sample_rate;
		u32 end_s   = (sample + 1) * src_sample_rate / dst_sample_rate;

		for (u32 channel = 0; channel < dst_channels; ++channel) {
			// Store the first sample (If we are contracting the sound we only will store this)
			f32 val_f32 = src_samples[channel][start_s];

			// If we are contracting the sound we calculate the mean of the group of samples
			for (u32 s = start_s+1; s < end_s; ++s) {
				val_f32 += src_samples[channel][s];
			}
			if (end_s - start_s > 0) {
				val_f32 /= (f32)(end_s - start_s);
			}

			// Store the value as i16 (We clamp it)
			i32 val = (i32)(val_f32*32767.0f);
			if      (val > 32767)  {val = 32767;}
			else if (val < -32768) {val = -32768;}

			// Calculate the destination position
			u32 pos   = (start_pos+sample)*dst_channels+channel;

			dst_samples_buffer[pos] = (i16)val;
		}
	}
}





// This function is based on stb_vorbis_decode_memory
static int
Decode_vorbis(u8 *mem, u32 mem_len, u32 dst_sample_rate, u32 dst_channels, i16 **samples, u32 *num_samples ) {

	// Load vorbis from mem
	int error;
	stb_vorbis *v = stb_vorbis_open_memory(mem, mem_len, &error, NULL);
	if (v == NULL) {return -1;}
	stb_vorbis_info v_info = stb_vorbis_get_info(v);

	// Samples buffer initialized
	int current_samples_count, total;
	i16 *dst_samples;
	total = dst_channels * 4096;
	current_samples_count = 0;
	dst_samples = Alloc(i16, total);
	if (dst_samples == NULL) {
	   stb_vorbis_close(v);
	   return -1;
	}

	// We get 1 frame on each iteration, 1 frame is a X number of samples that may differ
	// between iterations
	for (;;) {

		// Get 1 frame
		f32 **frame;
		int frame_samples = stb_vorbis_get_frame_float(v, NULL, &frame);

		// Claculate how many destination samples will fit with the current frame size
		int dst_samples_chunk_len = frame_samples * dst_sample_rate / v_info.sample_rate;

		// No more frames
		if (frame_samples == 0) break;

		// Calculate the new total size of the samples buffer and realloc if doesn't fit
		u32 next_samples_count = (current_samples_count + dst_samples_chunk_len);
		if (next_samples_count * dst_channels > total) {
			while(next_samples_count * dst_channels > total) {
				total *= 2;
			}
			dst_samples = Realloc(i16, dst_samples, total);
		}
		
		if (dst_channels != v_info.channels) {
			Resample_chunk_with_diff_channels(
					dst_samples,
					current_samples_count,
					dst_samples_chunk_len,
					dst_channels,
					dst_sample_rate,
					frame,
					v_info.channels,
					v_info.sample_rate);
		} else {
			Resample_chunk_with_eq_channels(
					dst_samples,
					current_samples_count,
					dst_samples_chunk_len,
					dst_channels,
					dst_sample_rate,
					frame,
					v_info.sample_rate);
		}

		current_samples_count = next_samples_count;
	}

	*samples = dst_samples;
	*num_samples = current_samples_count * dst_channels;
	stb_vorbis_close(v);
	return 0;
}



// Documented above
u32
Mixer_load_sound(const char *filename) {
	if (mixer_data.sound_count == MAX_SOUNDS ) { // Maximum number of sounds excessed
		return 0;
	}

	u32 music_data_len;
	u8 *music_data = Get_file_contentsz(filename, &music_data_len);

	if (music_data == NULL) {
		fprintf(stderr, "Cannot load ogg file '%s'.\n", filename);
		return 0;
	}

	i16 *samples;
	u32 num_samples;
	if (Decode_vorbis(
				music_data,
				music_data_len,
				mixer_data.sample_rate,
				mixer_data.num_channels,
				&samples,
				&num_samples) != 0)
	{
		Free_file_contents(music_data);
		fprintf(stderr, "Cannot decode '%s'.\n", filename);
		return 0;
	}

	Free_file_contents(music_data);

	u32 current_sound = mixer_data.sound_count;
	mixer_data.sound_count = current_sound + 1;
	mixer_data.sounds[current_sound].samples = samples;
	mixer_data.sounds[current_sound].n_samples = num_samples;
	return current_sound;
}


// Documented above
void
Mixer_play_sound(u32 sound_id, u8 flags, f32 volume, TrackHandle *handle) {
	Assert(
		sound_id < MAX_SOUNDS,
		"Sound id cannot be greatter or equal than MAX_SOUNDS (%d) but is: %d.", MAX_SOUNDS, sound_id);

	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_INVALID) {
				mixer_data.tracks_flags[i] = flags;
				mixer_data.tracks[i].sound_id       = sound_id;
				mixer_data.tracks[i].current_sample = 0;
				mixer_data.tracks[i].volume         = volume;
				mixer_data.tracks_handles[i] = handle;
				Mutex_unlock(&mixer_data.mutex);
				return;
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);
}


static void
Mixer_play_track_frames_loop(f32* buffer, u32 buffer_size, u32 track_id) {
	SoundTrack *track = &mixer_data.tracks[track_id];
	Sound *sound      = &mixer_data.sounds[track->sound_id];
	u32 current_sample = track->current_sample;
	u32 n_samples      = sound->n_samples;
	i16 *samples       = sound->samples;
	for (u32 i = 0; i < buffer_size; ++i) {
		f32 f32_val = ((f32)samples[current_sample] * 1.0f/32767.0f);
		buffer[i] += f32_val * track->volume;
		current_sample = (current_sample + 1) % n_samples;
	}
	track->current_sample = current_sample;
}


static void
Mixer_play_track_frames(f32* buffer, u32 buffer_size, u32 track_id) {
	SoundTrack *track = &mixer_data.tracks[track_id];
	Sound *sound      = &mixer_data.sounds[track->sound_id];
	u32 current_sample = track->current_sample;
	u32 n_samples      = sound->n_samples;
	i16 *samples       = sound->samples;
	for (u32 i = 0; i < buffer_size && current_sample < n_samples; ++i) {
		f32 f32_val = ((f32)samples[current_sample] * 1.0f/32767.0f);
		buffer[i] += f32_val * track->volume;
		++current_sample;
	}

	// If this happens the sound arrived to his end, we remove the track.
	if (current_sample == n_samples) {
		mixer_data.tracks_flags[track_id] |= PLAY_SOUND_FLAG_INVALID;
		mixer_data.tracks_handles[track_id] = NULL;
	} else {
		track->current_sample = current_sample;
	}
}

// Documented above
void
Mixer_play_frames(f32* buffer, u32 buffer_size) {

	// Fills the buffer with 0.0
	for (u32 i = 0; i < buffer_size; ++i) {
		buffer[i] = 0.0f;
	}

	Mutex_lock(&mixer_data.mutex);
	{
		for (u32 i = 0; i < MAX_TRACKS; ++i) {
			// If is invalid or paused we do nothing
			if (mixer_data.tracks_flags[i] & (PLAY_SOUND_FLAG_INVALID | PLAY_SOUND_FLAG_PAUSED)) {
				continue;
			}

			if (mixer_data.tracks_flags[i] & PLAY_SOUND_FLAG_LOOP) {
				Mixer_play_track_frames_loop(buffer, buffer_size, i);
			}
			else {
				Mixer_play_track_frames(buffer, buffer_size, i);
			}
		}
	}
	Mutex_unlock(&mixer_data.mutex);

	// Clamps the result
	for (u32 i = 0; i < buffer_size; ++i) {
		f32 val = buffer[i];
		if (val < -1.0f)     { buffer[i] = -1.0f; }
		else if (val > 1.0f) { buffer[i] = 1.0f; }
	}
}

#endif // _MIXER_H_

