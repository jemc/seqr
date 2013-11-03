
///
// C++ class definition

VALUE rb_LowPassNode = Qnil;
class LowPassNode : public Node {
  public:
    LowPassNode();
    
    CPP2RB_P_MEMBER(gain, double, 1.0);
    
    audio_sample_t last = 0.0;
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(LowPassNode);
CPP2RB_P_FUNCS(LowPassNode, gain, NUM2DBL);


LowPassNode::LowPassNode()
{
  CPP2RB_P_INIT(gain);
}

audio_sample_t* LowPassNode::get_buffer(nframes_t nframes)
{
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(!in) return NULL;
  
  this->buf.clear();
  
  for(int i=0; i<nframes; i++)
  {
    this->last = in[i] + this->last;
    this->buf.push_back(this->last*0.01);
  }
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_LowPassNode()
{
  rb_LowPassNode = rb_define_class_under(rb_ThisModule, "LowPassNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(LowPassNode);
  CPP2RB_P_FUNCS_REG(LowPassNode, gain, "gain");
}
