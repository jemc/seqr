
///
// C++ class definition

VALUE rb_PassThruNode = Qnil;
class PassThruNode : public JackNode {
  public:
    jack_port_t *input_port;
    jack_port_t *output_port;
    
    PassThruNode();
    ~PassThruNode();
    virtual void cpp2rb_mark();
    
    virtual int process (jack_nframes_t nframes);
    virtual int activate(VALUE rb_jclient);
};
CPP2RB_W_FUNCS(PassThruNode);


///
// C++ methods

PassThruNode::PassThruNode()
{
  NodeNetwork::final_node_add(this);
};

PassThruNode::~PassThruNode()
{
  NodeNetwork::final_node_remove(this);
}

void PassThruNode::cpp2rb_mark() 
{
  Node::cpp2rb_mark();
  rb_gc_mark(this->rb_jclient);
}

int PassThruNode::process(jack_nframes_t nframes)
{
  if(!this->jclient) return 0;
  
  jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (this->output_port, nframes);
  jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (this->input_port, nframes);

  memcpy(out, in, sizeof(jack_default_audio_sample_t) * nframes);
  
  return 0;
}

int PassThruNode::activate(VALUE jc)
{
  const char**   ports;
  jack_client_t* client;
  
  this->rb_jclient = jc;
  this->jclient = Jack_Client_w_get(jc);
  
  client = this->jclient->jclient;
  
  this->input_port  = jack_port_register(client, "input",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput,  0);
  this->output_port = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
  if(!ports || jack_connect(client, ports[0], jack_port_name(this->input_port)))
    return 1;
  free(ports);
  
  ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
  if(!ports || jack_connect(client, jack_port_name(this->output_port), ports[0]))
    return 1;
  free(ports);
  
  return 0;
}

///
// Ruby-accessible C methods

extern "C" VALUE PassThruNode_m_jclient(VALUE self)
{
  return PassThruNode_w_get(self)->rb_jclient;
}


///
// Bind to Ruby object

void Init_PassThruNode()
{
  rb_PassThruNode = rb_define_class_under(rb_ThisModule, "PassThruNode", rb_Node);
  
  rb_define_alloc_func(rb_PassThruNode, PassThruNode_w_alloc);
  
  rb_define_method(rb_PassThruNode, "jclient",
     RUBY_METHOD_FUNC(PassThruNode_m_jclient),        0);
}
