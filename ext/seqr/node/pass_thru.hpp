


jack_port_t *input_port;
jack_port_t *output_port;

///
// C++ class definition

VALUE rb_PassThruNode = Qnil;
class PassThruNode : public Node {
  public:
    Jack_Client* jclient;
    VALUE     rb_jclient;
    
    PassThruNode()
    {
      this->jclient = NULL;
      this->rb_jclient = Qnil;
      
      g_final_nodes.push_back(this);
    };
    
    virtual int process (jack_nframes_t nframes)
    {
      jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
      jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);

      memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
      
      return 0;
    }
};
CPP2RB_W_FUNCS(PassThruNode);


///
// Ruby-accessible C methods

extern "C" VALUE PassThruNode_m_jclient(VALUE self)
{
  return PassThruNode_w_get(self)->rb_jclient;
}

extern "C" VALUE PassThruNode_m_activate(VALUE self, VALUE jc)
{
  PassThruNode* c_self;
  const char **ports;
  jack_client_t* client;
  jack_status_t  status;
  
  if(jc==Qnil) return Qnil;
  
  c_self = PassThruNode_w_get(self);
  c_self->rb_jclient = jc;
  c_self->jclient = Jack_Client_w_get(jc);
  
  client = c_self->jclient->jclient;
  
  jack_set_process_callback(client, main_process, 0);
  if(client == NULL) return Qnil;
  
  input_port = jack_port_register(client, "input",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput,  0);
  output_port = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  if (jack_activate (client)) {
    fprintf (stderr, "cannot activate client");
    exit(1);
  }
   
  if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL) {
    fprintf(stderr, "Cannot find any physical capture ports\n");
    exit(1);
  }
  
  if (jack_connect (client, ports[0], jack_port_name (input_port))) {
    fprintf (stderr, "cannot connect input ports\n");
  }
  
  free (ports);
  
  if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsInput)) == NULL) {
    fprintf(stderr, "Cannot find any physical playback ports\n");
    exit(1);
  }

  if (jack_connect (client, jack_port_name (output_port), ports[0])) {
    fprintf (stderr, "cannot connect output ports\n");
  }
  
  free (ports);
}



///
// Bind to Ruby object

void Init_PassThruNode()
{
  rb_PassThruNode = rb_define_class_under(rb_ThisModule, "PassThruNode", rb_Node);
  
  rb_define_alloc_func(rb_PassThruNode, PassThruNode_w_alloc);
  
  rb_define_method(rb_PassThruNode, "jclient",
    RUBY_METHOD_FUNC (PassThruNode_m_jclient),        0);
  rb_define_method(rb_PassThruNode, "activate",
    RUBY_METHOD_FUNC (PassThruNode_m_activate),       1);
}
