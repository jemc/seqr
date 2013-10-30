
///
// C++ class definition

VALUE rb_NodeNetwork = Qnil;
class NodeNetwork
{
  private:
    static std::vector<Node*> final_nodes;
    static std::vector<Node*>  jack_nodes;
    
  public:
    static Jack_Client* jclient;
    static VALUE     rb_jclient;
    
    NodeNetwork();
    virtual void cpp2rb_mark();
    
    static void final_node_add(Node* n)
    { final_nodes.push_back(n); };
    static void final_node_remove(Node * n)
    { final_nodes.erase(std::remove(final_nodes.begin(), final_nodes.end(), n), 
                        final_nodes.end()); };
    
    static void jack_node_add(Node* n)
    { jack_nodes.push_back(n); if(jclient) n->activate(rb_jclient); };
    static void jack_node_remove(Node * n)
    { jack_nodes.erase(std::remove(jack_nodes.begin(), jack_nodes.end(), n), 
                        jack_nodes.end()); };
    
    static int main_process(jack_nframes_t nframes, void* arg);
    static int activate();
};
CPP2RB_W_FUNCS(NodeNetwork);

// Static members redeclared
std::vector<Node*> NodeNetwork::final_nodes;
std::vector<Node*> NodeNetwork::jack_nodes;
Jack_Client*       NodeNetwork::jclient;
VALUE              NodeNetwork::rb_jclient;

// Audio processing callback, called by Jack
int NodeNetwork::main_process(jack_nframes_t nframes, void* arg)
{
  int result;
  
  for(int ii=0; ii < final_nodes.size(); ii++)
  {
    result=(final_nodes[ii]->process(nframes));
    if(result) return result;
  }
  return 0;
}

// Activate Jack and all nodes that relate to Jack
int NodeNetwork::activate()
{
  if (jclient->jclient == NULL) {
    fprintf (stderr, "null client");
    exit(1);
  }
  
  jack_set_process_callback(jclient->jclient, main_process, 0);
  
  if (jack_activate(jclient->jclient)) {
    fprintf (stderr, "cannot activate client");
    exit(1);
  }
  
  for(int ii=0; ii < jack_nodes.size(); ii++)
    jack_nodes[ii]->activate(rb_jclient);
}

///
// Ruby-accessible C methods

extern "C" VALUE NodeNetwork_s_jclient(VALUE self)
{
  return NodeNetwork_w_get(self)->rb_jclient;
}

extern "C" VALUE NodeNetwork_s_activate(VALUE self, VALUE jc)
{
  jack_client_t* client;
  
  if(jc==Qnil) return Qnil;
  
  NodeNetwork::rb_jclient = jc;
  NodeNetwork::jclient = Jack_Client_w_get(jc);
  
  NodeNetwork::activate();
}


///
// Bind to Ruby object

void Init_NodeNetwork()
{
  rb_NodeNetwork = rb_define_module_under(rb_ThisModule, "NodeNetwork");
  
  rb_define_singleton_method(rb_NodeNetwork, "jclient",
               RUBY_METHOD_FUNC(NodeNetwork_s_jclient),        0);
  rb_define_singleton_method(rb_NodeNetwork, "activate",
               RUBY_METHOD_FUNC(NodeNetwork_s_activate),       1);
}
