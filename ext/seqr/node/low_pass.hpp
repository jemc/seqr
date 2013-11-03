
///
// C++ class definition

VALUE rb_LowPass = Qnil;
class LowPass : public Node {
  public:
    LowPass();
    
    CPP2RB_P_MEMBER(gain, double, 1.0);
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(LowPass);
CPP2RB_P_FUNCS(LowPass, gain, NUM2DBL);


LowPass::LowPass()
{
  CPP2RB_P_INIT(gain);
}

audio_sample_t* LowPass::get_buffer(nframes_t nframes)
{
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(!in) return NULL;
  
  this->buf.clear();
  
  for(int i=0; i<nframes; i++)
    this->buf.push_back(in[i] * this->gain);
  
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_LowPass()
{
  rb_LowPass = rb_define_class_under(rb_ThisModule, "LowPass", rb_Node);
  
  CPP2RB_W_FUNCS_REG(LowPass);
  CPP2RB_P_FUNCS_REG(LowPass, gain, "gain");
}
