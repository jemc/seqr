
///
// C++ class definition

VALUE rb_PassThruNode = Qnil;
class PassThruNode : public Node {
  public:
    jack_client_t* jclient;
    VALUE       rb_jclient;
    
    PassThruNode();
};
CPP2RB_W_FUNCS(PassThruNode);


jack_port_t *input_port;
jack_port_t *output_port;

extern "C" int process (jack_nframes_t nframes, void *arg)
{
  jack_default_audio_sample_t *out = (jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
  jack_default_audio_sample_t *in = (jack_default_audio_sample_t *) jack_port_get_buffer (input_port, nframes);

  memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);
  
  return 0;
}

PassThruNode::PassThruNode()
{
  const char **ports;
  jack_client_t* client;
  jack_status_t  status;
  
  this->jclient = jack_client_open("test", JackNullOption, &status);

  jack_set_process_callback(this->jclient, process, 0);
  
  input_port = jack_port_register(this->jclient, "input",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput,  0);
  output_port = jack_port_register(this->jclient, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  
  fprintf (stderr, "%i\n", status);
  
  if (jack_activate (this->jclient)) {
    fprintf (stderr, "cannot activate client");
    exit(1);
  }
   
  if ((ports = jack_get_ports (this->jclient, NULL, NULL, JackPortIsPhysical|JackPortIsOutput)) == NULL) {
    fprintf(stderr, "Cannot find any physical capture ports\n");
    exit(1);
  }
  
  if (jack_connect (this->jclient, ports[0], jack_port_name (input_port))) {
    fprintf (stderr, "cannot connect input ports\n");
  }
  
  free (ports);
  
  if ((ports = jack_get_ports (this->jclient, NULL, NULL, JackPortIsPhysical|JackPortIsInput)) == NULL) {
    fprintf(stderr, "Cannot find any physical playback ports\n");
    exit(1);
  }

  if (jack_connect (this->jclient, jack_port_name (output_port), ports[0])) {
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
}
