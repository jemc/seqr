
///
// C++ class definition

VALUE rb_GainNode = Qnil;
class GainNode : public Node {
  public:
    VALUE rb_gain = Qnil;
    double gain   = 1.0;
    
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
    this->buf.push_back(in[i] * this->gain);
  
  return this->buf.data();
}


///
// Ruby-accessible C methods

extern "C" VALUE GainNode_m_gain(VALUE self)
{
  return GainNode_w_get(self)->rb_gain;
}

extern "C" VALUE GainNode_m_gain_setter(VALUE self, VALUE new_val) {
  GainNode* c_self = GainNode_w_get(self);
  
  c_self->rb_gain = new_val;
  c_self->gain = NUM2DBL(new_val);
  
  return new_val;
}


///
// Bind to Ruby object

void Init_GainNode()
{
  rb_GainNode = rb_define_class_under(rb_ThisModule, "GainNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(GainNode);
  
  rb_define_method(rb_GainNode, "gain",
    RUBY_METHOD_FUNC (GainNode_m_gain),        0);
  rb_define_method(rb_GainNode, "gain=",
    RUBY_METHOD_FUNC (GainNode_m_gain_setter), 1);
}
