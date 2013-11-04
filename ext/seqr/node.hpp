
///
// C++ class definition

VALUE rb_Node = Qnil;
class Node : public Cpp2Rb
{
  protected:
    std::vector<audio_sample_t> buf;
  
  public:
    Node();
    
    CPP2RB_P_MEMBER(Node*, source);
    
    virtual audio_sample_t* get_buffer(nframes_t nframes) {};
    virtual int process (nframes_t nframes) {};
    virtual int activate(VALUE rb_jclient)  {};
};
CPP2RB_W_FUNCS(Node);
CPP2RB_P_FUNCS(Node, source, Node_w_get);


Node::Node()
{
  CPP2RB_P_INIT_BACKEND(Node, source, Qnil, NULL);
}


///
// Include children

#include "node/_network.hpp"

#include "node/jack.hpp"

#include "node/jack_input.hpp"
#include "node/jack_output.hpp"
#include "node/gain.hpp"
#include "node/causal_filter.hpp"


///
// Bind to Ruby object

void Init_Node()
{
  rb_Node = rb_define_class_under(rb_ThisModule, "Node", rb_cObject);
  
  CPP2RB_W_FUNCS_REG(Node);
  CPP2RB_P_FUNCS_REG(Node, source, "source");
  
  ///
  // Init children
  
  Init_NodeNetwork();
  Init_JackInputNode();
  Init_JackOutputNode();
  Init_GainNode();
  Init_CausalFilterNode();
}

