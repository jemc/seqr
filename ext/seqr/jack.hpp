
VALUE rb_Jack = Qnil;

///
// Include objects in module

#include "jack/constants.hpp"
#include "jack/client.hpp"

typedef jack_default_audio_sample_t audio_sample_t;
typedef jack_nframes_t              nframes_t;

#define AUDIO_SAMPLE_MAX 100.0
#define AUDIO_SAMPLE_MIN -100.0
#define AUDIO_SAMPLE_CLIP(Samp) \
  if     (Samp<AUDIO_SAMPLE_MIN) {Samp=AUDIO_SAMPLE_MIN;} \
  else if(Samp>AUDIO_SAMPLE_MAX) {Samp=AUDIO_SAMPLE_MAX;}

///
// Bind to Ruby module

void Init_Jack()
{
  rb_Jack = rb_define_module_under(rb_ThisModule, "Jack");
  
  Init_Jack_Constants();
  Init_Jack_Client();
}
