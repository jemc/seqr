
///
// C++ class definition

VALUE rb_GainNode = Qnil;
class GainNode : public Node {
  public:
    GainNode();
    
    CPP2RB_P_MEMBER(double, gain);
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(GainNode);
CPP2RB_P_FUNCS(GainNode, gain, CPP2RB_VALUE_TO_DOUBLE);


GainNode::GainNode()
{
  CPP2RB_P_INIT(GainNode, gain, CPP2RB_VALUE_FROM_DOUBLE(1.0));
}

audio_sample_t* GainNode::get_buffer(nframes_t nframes)
{
  if(!this->source) return NULL;
  
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(!in) return NULL;
  
  this->buf.clear();
  
  for(int i=0; i<nframes; i++)
    this->buf.push_back(in[i] * this->gain);
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_GainNode()
{
  rb_GainNode = rb_define_class_under(rb_ThisModule, "GainNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(GainNode);
  CPP2RB_P_FUNCS_REG(GainNode, gain, "gain");
}
