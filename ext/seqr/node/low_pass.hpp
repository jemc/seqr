
///
// LowPassNode implements out(n) = in(n) + in(n-1)

VALUE rb_LowPassNode = Qnil;
class LowPassNode : public Node {
  protected:
    std::vector<audio_sample_t> last_in;
    
  public:
    LowPassNode();
    
    CPP2RB_P_MEMBER(bypass, bool, false);
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(LowPassNode);
CPP2RB_P_FUNCS(LowPassNode, bypass, RTEST);


LowPassNode::LowPassNode()
{
  CPP2RB_P_INIT(bypass);
}

audio_sample_t* LowPassNode::get_buffer(nframes_t nframes)
{
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(this->bypass || !in) return in;
  
  audio_sample_t last = 0.0;
  audio_sample_t samp = 0.0;
  
  this->buf.clear();
  for(int i=0; i<nframes; i++)
  { 
    if(i-1 >= 0)
      last = in[i-1];
    else if(this->last_in.size()+i >= 1)
      last = this->last_in[this->last_in.size()+i-1];
    else
      last = 0.0;
    
    samp = in[i] + last;
    AUDIO_SAMPLE_CLIP(samp);
    this->buf.push_back(samp*0.01);
  }
  
  this->last_in.clear();
  for(int i=0; i<nframes; i++)
    this->last_in.push_back(in[i]);
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_LowPassNode()
{
  rb_LowPassNode = rb_define_class_under(rb_ThisModule, "LowPassNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(LowPassNode);
  CPP2RB_P_FUNCS_REG(LowPassNode, bypass, "bypass");
}
