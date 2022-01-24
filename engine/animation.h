
#ifndef ANIMATION_H
#define ANIMATION_H

enum {
	MAX_KEYFRAMES = 128
};

// Describes a animation
typedef struct {
	u32 n_keyframes;
	f32 total_time;
	u32 sprites[MAX_KEYFRAMES];
	f32 durations[MAX_KEYFRAMES];
} Animation;

// Describes the current animation state
typedef struct {
	const Animation *animation;
	u32 current_keyframe;
	f32 current_keyframe_time;
} AnimationState;


/*
* Load_animation
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Loads an animation from a file, on error will return != 0, also it will log the error.
*
* This function calls internally to Load_animation_from_memory
*
* The format of a animation file is the following:
*
* ```
* 5
* 0 0.1
* 1 0.1
* 2 0.1
* 3 0.1
* 4 0.1
* ```
*
* The first line is the number of keyframes, and the following lines are the sprite id and the 
* duration
*
* VARIABLES
* -------------------------------------------------------------------
*   filename: The name of the animation file
*   anim: The animtion to fill
*
* RETURN
* ------------------------------------------------------------------
*  != 0 on error
*/
int
Load_animation(const char *filename, Animation *anim);



/*
* Load_animation_from_memory
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* The same as Load animation but receives a null terminated string with the data
*
* VARIABLES
* -------------------------------------------------------------------
*   data: The data to parse, (Must be a null terminated string)
*   anim: The animtion to fill
*
* RETURN
* ------------------------------------------------------------------
*  != 0 on error
*/
int
Load_animation_from_memory(const char *data, Animation *anim);



/*
* Make_animation_state
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Makes a animation state from the animation recived, starting at the
* keyframe 0
*
* VARIABLES
* -------------------------------------------------------------------
*   animation: The animation to use
*
* RETURN
* ------------------------------------------------------------------
*  The animation state created
*/
AnimationState
Make_animation_state(const Animation *animation);



/*
* Play_animation
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Plays a animation by a delta time and gets the new sprite id.
* If the animation has arrived to the end starts again.
*
* VARIABLES
* -------------------------------------------------------------------
* anim_state: The animation state which we are playing
* dt: The delta time
*
* RETURN
* ------------------------------------------------------------------
* The current sprite id of the animation
*/
u32
Play_animation(AnimationState *anim_state, f32 dt);












/////////////////////////////////////////////////////////////////////////////////
//
//
//                 IMPLEMENTATION STARTS
//
//
//
////////////////////////////////////////////////////////////////////////////////



static int
Atoin(const char *str, u32 size);
static f32
Atofn(const char *str, u32 size);
static bool
Is_space(char c);
static bool
Char_matches(char c, const char *chars);
static const char *
Eat_spaces(const char *str);

// Documented above
int
Load_animation_from_memory(const char *data, Animation *anim) {

	const char *cursor = data;
	u32 n_keyframes;
	
	int current_line = 1;

	cursor = Eat_spaces(cursor);
	{ // Get the number of keyframes
		const char *n_keyframes_str = cursor;
		u32 n_keyframes_str_len     = 0;
		while (Char_matches(*cursor, "1234567890")) {
			++cursor;
			++n_keyframes_str_len;
		}
		if (n_keyframes_str_len == 0) {
			fprintf(stderr, "Error on line %d, expected the number of keyframes.\n", current_line);
			return -1;
		}
		n_keyframes = Atoin(n_keyframes_str, n_keyframes_str_len);
		if (n_keyframes > MAX_KEYFRAMES) {
			fprintf(stderr, "Error, keyframes are greater than MAX_KEYFRAMES %d vs %d.\n", n_keyframes, MAX_KEYFRAMES);
			return -1;
		}
		if (n_keyframes <= 0) {
			fprintf(stderr, "Error, number of keyframes must be greater than than 0, but they are %d.\n", n_keyframes);
			return -1;
		}

		// Go to the next line
		cursor = Eat_spaces(cursor);
		if (*cursor != '\n') {
			fprintf(stderr, "Error on line %d, expected end of line, but got '%c'.\n", current_line, *cursor);
			return -1;
		}
		++cursor;
		++current_line;
	}

	int keyframe_i = 0;
	for (;keyframe_i < n_keyframes; ++keyframe_i) {

		//
		// Get the sprite id
		//
		cursor = Eat_spaces(cursor);
		const char *sprite_str = cursor;
		u32 sprite_str_len = 0;
		while (Char_matches(*cursor, "1234567890")) {
			++cursor;
			++sprite_str_len;
		}
		if (sprite_str_len == 0) {
			fprintf(stderr, "Error on line %d, expected the sprite id.\n", current_line);
			return -1;
		}
		anim->sprites[keyframe_i] = Atoin(sprite_str, sprite_str_len);

		// We should have here at least 1 space
		if (!Is_space(*cursor)) {
			fprintf(stderr, "Error on line %d, expected a space splitting between the sprite id and the duration, but got '%c'.\n", current_line, *cursor);
			return -1;
		}

		//
		// Get the duration
		//
		cursor = Eat_spaces(cursor);
		const char *duration_str = cursor;
		u32 duration_str_len = 0;
		while (Char_matches(*cursor, "1234567890.-")) {
			++cursor;
			++duration_str_len;
		}
		if (duration_str_len == 0) {
			fprintf(stderr, "Error on line %d, expected the duration.\n", current_line);
			return -1;
		}
		f32 duration = Atofn(duration_str, duration_str_len);
		if (duration <= 0) {
			fprintf(stderr, "Error on line %d, the duration must be greater than 0, but is %f.\n", current_line, duration);
			return -1;
		}
		anim->durations[keyframe_i] = duration;

		// Go to the next line
		cursor = Eat_spaces(cursor);
		if (*cursor != '\n') {
			fprintf(stderr, "Error on line %d, expected end of line, but got '%c'.\n", current_line, *cursor);
			return -1;
		}
		++cursor;
		++current_line;
	}

	anim->n_keyframes = n_keyframes;
	f32 total_time = 0.0f;
	for (u32 i = 0; i < n_keyframes; ++i) {
		total_time += anim->durations[i];
	}
	anim->total_time = total_time;
	return 0;
}


// Documented above
int
Load_animation(const char *filename, Animation *anim) {
	char *animation_file_data = (char *)Get_file_contentsz(filename, NULL);
	if (animation_file_data == NULL) {
		fprintf(stderr, "Error reading file '%s'.\n", filename);
		return -1;
	}
	if (Load_animation_from_memory(animation_file_data, anim) != 0) {
		Free_file_contents((u8 *)animation_file_data);
		fprintf(stderr, "Error loading animation '%s'.\n", filename);
		return -1;
	}
	Free_file_contents((u8 *)animation_file_data);
	return 0;
}

// Internal function to convert from string (NOT NULL Terminated) to int
static int
Atoin(const char *str, u32 size) {
	char buffer[128];
	if (size > 128 - 1) {
		size = 128 - 1;
	}
	for (int i = 0; i < size; ++i) {
		buffer[i] = str[i];
	}
	buffer[size] = 0;
	return atoi(buffer);
}

// Internal function to convert from string (NOT NULL Terminated) to float
static f32
Atofn(const char *str, u32 size) {
	char buffer[128];
	if (size > 128 - 1) {
		size = 128 - 1;
	}
	for (int i = 0; i < size; ++i) {
		buffer[i] = str[i];
	}
	buffer[size] = 0;
	return atof(buffer);
}

// Internal function that checks if a character is a space
static bool
Is_space(char c) {
	return (c == ' ' || c == '\t' || c == '\r');
}

// Internal function that checks if a char is on the array of chars passed
static bool
Char_matches(char c, const char *chars) {
	const char *chars_cursor = chars;
	while (*chars_cursor != '\0') {
		if (c == *chars_cursor) {
			return true;
		}
		++chars_cursor;
	}
	return false;
}

// Internal functions that recives a string and slices it until there is no spaces
const char *
Eat_spaces(const char *str) {
	const char *cursor = str;
	while (Is_space(*cursor)) {
		++cursor;
	}
	return cursor;
}


// Documented above
AnimationState
Make_animation_state(const Animation *animation) {
	AnimationState anim_state;
	anim_state.animation = animation;
	anim_state.current_keyframe = 0;
	anim_state.current_keyframe_time = 0.0f;
	return anim_state;
}


// Documented above
u32
Play_animation(AnimationState *anim_state, f32 dt) {
	u32 n_keyframes  = anim_state->animation->n_keyframes;
	Assert(n_keyframes > 0, "n_keyframes must be greater than 0, but is %d", n_keyframes);
	u32 new_keyframe = anim_state->current_keyframe;
	f32 kf_duration  = anim_state->animation->durations[new_keyframe];
	Assert(kf_duration > 0.0f, "The duration must be greater than 0, but is %f", kf_duration);
	f32 new_time     = anim_state->current_keyframe_time + dt;
	while (new_time > kf_duration) {
		new_time = new_time - kf_duration;
		new_keyframe = (new_keyframe + 1)%n_keyframes;
		kf_duration  = anim_state->animation->durations[new_keyframe];
	}
	anim_state->current_keyframe = new_keyframe;
	anim_state->current_keyframe_time = new_time;
	return anim_state->animation->sprites[new_keyframe];
}


u32
Animation_lerp(const Animation *anim, f32 t) {
	f32 dur_t = anim->total_time * t;
	u32 n_keyframes = anim->n_keyframes;

	u32 current_keyframe = 0;
	f32 current_duration = anim->durations[current_keyframe];
	while (dur_t > current_duration) {
		dur_t -= current_duration;
		current_keyframe = (current_keyframe+1)%n_keyframes;
		current_duration = anim->durations[current_keyframe];
	}
	return anim->sprites[current_keyframe];
}


#endif // ANIMATION_H

