#include <spa/audio.h>

namespace spa {
namespace audio {

/*
	visitor definitions
*/

visitor::~visitor() {}

/*
	accept definitions
*/

#define ACCEPT_SPA_AUDIO(classname) ACCEPT(classname, spa::audio::visitor)

namespace stereo {
	ACCEPT_SPA_AUDIO(in)
	ACCEPT_SPA_AUDIO(out)
}

ACCEPT_SPA_AUDIO(in)
ACCEPT_SPA_AUDIO(out)

ACCEPT_SPA_AUDIO(samplerate)
ACCEPT_SPA_AUDIO(buffersize)
ACCEPT_SPA_AUDIO(samplecount)

ACCEPT_SPA_AUDIO(osc_ringbuffer_in)

#undef ACCEPT_SPA_AUDIO

} // namespace audio
} // namespace spa

