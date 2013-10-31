
///
// C++ class definition

class JackNode : public Node {
  public:
    Jack_Client* jclient;
    VALUE     rb_jclient;
    
    JackNode();
    ~JackNode();
    virtual void cpp2rb_mark();
    
    bool jack_is_ready() { return (jclient!=NULL); };
    Jack_Client* store_jclient(VALUE);
};

///
// C++ methods

JackNode::JackNode()
{
  NodeNetwork::jack_node_add(this);
  
  this->jclient    = NodeNetwork::jclient;
  this->rb_jclient = NodeNetwork::rb_jclient;
};

JackNode::~JackNode()
{
  NodeNetwork::jack_node_remove(this);
}

void JackNode::cpp2rb_mark()
{
  Node::cpp2rb_mark();
  rb_gc_mark(this->rb_jclient);
}

Jack_Client* JackNode::store_jclient(VALUE jc)
{
  this->rb_jclient = jc;
  this->jclient = Jack_Client_w_get(jc);
  
  return this->jclient;
}

///
// Not bound to a Ruby Object
