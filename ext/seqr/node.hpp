
///
// C++ class definition

VALUE rb_Node = Qnil;
class Node
{
  protected:
    std::vector<audio_sample_t> buf;
  
  public:
    CPP2RB_P_MEMBER(source, Node*, NULL);
    std::unordered_map<std::string,Param*> params;
    
    Node();
    
    virtual void cpp2rb_mark();
    
    virtual audio_sample_t* get_buffer(nframes_t nframes) {};
    virtual int process(nframes_t nframes) {};
    virtual int activate(VALUE rb_jclient) {};
};
CPP2RB_W_FUNCS(Node);
CPP2RB_P_FUNCS(Node, source, Node_w_get);


///
// C++ methods

Node::Node()
{
  // CPP2RB_Param<double>* ptr = CPP2RB_Param(1.0)
  // this->params.push_back(*ptr);
  params["test"]  = (Param*)(new DoubleParam(1.0));
  params["test2"] = (Param*)(new XParam<double> (1.0));
}

// Garbage collection marker
void Node::cpp2rb_mark()
{
  for(auto it=this->params.begin(); it!=this->params.end(); ++it)
    rb_gc_mark(it->second->rb_val);
}


///
// Include children

#include "node/_network.hpp"

#include "node/jack.hpp"

#include "node/jack_input.hpp"
#include "node/jack_output.hpp"
#include "node/gain.hpp"


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
}

