
///
// CausalFilterNode

VALUE rb_CausalFilterNode = Qnil;
class CausalFilterNode : public Node {
  protected:
    std::vector<audio_sample_t> last_in;
    
  public:
    CausalFilterNode();
    
    CPP2RB_P_MEMBER(bypass, bool, false);
    CPP2RB_P_MEMBER(gain, double, 1.0);
    CPP2RB_P_MEMBER(ff_coeffs, std::vector<double>, {1.0});
    CPP2RB_P_MEMBER(fb_coeffs, std::vector<double>, {1.0});
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(CausalFilterNode);
CPP2RB_P_FUNCS(CausalFilterNode, bypass, RTEST);
CPP2RB_P_FUNCS(CausalFilterNode, gain, NUM2DBL);

std::vector<double> rb_ary_to_vec_double(VALUE ary)
{
  std::vector<double> vec;
  
  for(int i=0; i<RARRAY_LEN(ary); i++)
    vec.push_back(NUM2DBL(rb_ary_entry(ary, i)));
  
  return vec;
}

CPP2RB_P_FUNCS(CausalFilterNode, ff_coeffs, rb_ary_to_vec_double);
CPP2RB_P_FUNCS(CausalFilterNode, fb_coeffs, rb_ary_to_vec_double);


CausalFilterNode::CausalFilterNode()
{
  CPP2RB_P_INIT(bypass);
  CPP2RB_P_INIT(gain);
  CPP2RB_P_INIT(ff_coeffs);
  CPP2RB_P_INIT(fb_coeffs);
}

audio_sample_t* CausalFilterNode::get_buffer(nframes_t nframes)
{
  // Get the input buffer pointer
  audio_sample_t* in = this->source->get_buffer(nframes);
  if(this->bypass || !in) return in;
  
  audio_sample_t last;
  audio_sample_t samp;
  
  // Clear the buffer and fill each input sample
  this->buf.clear();
  for(int i=0; i<nframes; i++)
  {
    samp = 0.0;
    
    // Add in feedforward components
    for(int j=0; j<this->ff_coeffs.size(); j++)
    {
      if(i-j >= 0)
        last = in[i-j];
      else if(this->last_in.size()+i >= j)
        last = this->last_in[this->last_in.size()+i-j];
      else
        last = 0.0;
      samp += last * ff_coeffs[j];
    }
    
    // Clip the sample and push it into the buffer
    AUDIO_SAMPLE_CLIP(samp);
    this->buf.push_back(samp*this->gain);
  }
  
  // Remember the last input buffer
  this->last_in.clear();
  for(int i=0; i<nframes; i++)
    this->last_in.push_back(in[i]);
  
  // Return output buffer pointer
  return this->buf.data();
}


///
// Bind to Ruby object

void Init_CausalFilterNode()
{
  rb_CausalFilterNode = rb_define_class_under(rb_ThisModule, "CausalFilterNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(CausalFilterNode);
  CPP2RB_P_FUNCS_REG(CausalFilterNode, bypass, "bypass");
  CPP2RB_P_FUNCS_REG(CausalFilterNode, gain,   "gain");
  CPP2RB_P_FUNCS_REG(CausalFilterNode, ff_coeffs, "ff_coeffs");
  CPP2RB_P_FUNCS_REG(CausalFilterNode, fb_coeffs, "fb_coeffs");
}
