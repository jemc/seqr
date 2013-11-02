
///
// C++ class definition

VALUE rb_JackInputNode = Qnil;
class JackInputNode : public JackNode {
  public:
    jack_port_t *port;
    
    JackInputNode();
    
    virtual audio_sample_t* get_buffer(nframes_t nframes);
    virtual int activate(VALUE rb_jclient);
};
CPP2RB_W_FUNCS(JackInputNode);


///
// C++ methods

JackInputNode::JackInputNode()
{
  this->activate(this->rb_jclient);
}

audio_sample_t* JackInputNode::get_buffer(nframes_t nframes)
{
  if(!this->jack_is_ready()) return NULL;
  
  return (audio_sample_t*)jack_port_get_buffer(this->port, nframes);
}

int JackInputNode::activate(VALUE jc)
{
  const char**   ports;
  jack_client_t* client;
  
  client = store_jclient(jc)->jclient;
  if(!this->jack_is_ready()) return 1;
  
  this->port  = jack_port_register(client, "input",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput,  0);
  
  ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
  if(!ports || jack_connect(client, ports[0], jack_port_name(this->port)))
    return 1;
  free(ports);
  
  return 0;
}


///
// Bind to Ruby object

void Init_JackInputNode()
{
  rb_JackInputNode = rb_define_class_under(rb_ThisModule, "JackInputNode", rb_Node);
  
  rb_define_alloc_func(rb_JackInputNode, JackInputNode_w_alloc);
}
