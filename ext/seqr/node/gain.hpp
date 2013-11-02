
///
// C++ class definition

VALUE rb_GainNode = Qnil;
class GainNode : public Node {
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
  
  this->buf.clear();
  
  for(int i=0; i<nframes; i++)
    this->buf.push_back(in[i]*1.0);
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_GainNode()
{
  rb_GainNode = rb_define_class_under(rb_ThisModule, "GainNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(GainNode);
}
