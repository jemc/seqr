
///
// C++ class definition

VALUE rb_GainNode = Qnil;
class GainNode : public Node {
  public:
    CPP2RB_P_MEMBER(gain, double, 1.0);
    
    virtual void cpp2rb_mark();
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
};
CPP2RB_W_FUNCS(GainNode);
CPP2RB_P_FUNCS(GainNode, gain, NUM2DBL);


///
// C++ methods

// Garbage collection marker
void GainNode::cpp2rb_mark()
{
  Node::cpp2rb_mark();
  rb_gc_mark(this->rb_gain);
}

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
// Bind to Ruby object

void Init_GainNode()
{
  rb_GainNode = rb_define_class_under(rb_ThisModule, "GainNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(GainNode);
  CPP2RB_P_FUNCS_REG(GainNode, gain, "gain");
}
