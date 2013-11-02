
///
// C++ class definition

VALUE rb_GainNode = Qnil;
class GainNode : public JackNode {
  private:
    std::vector<audio_sample_t> buf;
  
  public:
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(GainNode);


///
// C++ methods

audio_sample_t* GainNode::get_buffer(nframes_t nframes)
{
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(!in) return NULL;
  
  this->buf.assign(in, in + (nframes * sizeof(audio_sample_t)));
  
  // for(int i=0; i++; i<nframes)
  //   this->buf[i] = in[i]*0.25;
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_GainNode()
{
  rb_GainNode = rb_define_class_under(rb_ThisModule, "GainNode", rb_Node);
  
  rb_define_alloc_func(rb_GainNode, GainNode_w_alloc);
}