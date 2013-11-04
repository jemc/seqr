
///
// C++ class definition

VALUE rb_JackOutputNode = Qnil;
class JackOutputNode : public JackNode {
  public:
    jack_port_t *port;
    
    JackOutputNode();
    ~JackOutputNode();
    
    virtual int process(nframes_t nframes);
    virtual int activate(VALUE rb_jclient);
};
CPP2RB_W_FUNCS(JackOutputNode);


///
// C++ methods

JackOutputNode::JackOutputNode()
{
  NodeNetwork::final_node_add(this);
  this->activate(this->rb_jclient);
}

JackOutputNode::~JackOutputNode()
{
  NodeNetwork::final_node_remove(this);
}

int JackOutputNode::process(nframes_t nframes)
{
  if(!this->jack_is_ready()) return 0;
  if(!this->source) return 0;
  
  audio_sample_t *out = (audio_sample_t*)jack_port_get_buffer(this->port, nframes);
  audio_sample_t *in  = (audio_sample_t*)this->source->get_buffer(nframes);
  
  if(!in) return 0;
  memcpy(out, in, sizeof(audio_sample_t) * nframes);
  
  return 0;
}

int JackOutputNode::activate(VALUE jc)
{
  const char**   ports;
  jack_client_t* client;
  
  client = store_jclient(jc)->jclient;
  if(!this->jack_is_ready()) return 1;
  
  this->port = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
  if(!ports || jack_connect(client, jack_port_name(this->port), ports[0]))
    return 1;
  free(ports);
  
  return 0;
}


///
// Bind to Ruby object

void Init_JackOutputNode()
{
  rb_JackOutputNode = rb_define_class_under(rb_ThisModule, "JackOutputNode", rb_Node);
  
  CPP2RB_W_FUNCS_REG(JackOutputNode);
}
