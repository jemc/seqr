
///
// C++ class definition

class JackNode : public Node {
  public:
    Jack_Client* jclient;
    VALUE     rb_jclient;
    
    JackNode();
    ~JackNode();
    virtual void cpp2rb_mark();
    
    Jack_Client* store_jclient(VALUE);
};

///
// C++ methods

JackNode::JackNode()
{
  this->jclient = NULL;
  this->rb_jclient = Qnil;
  
  fprintf(stderr, "this should happen!\n");
  
  NodeNetwork::jack_node_add(this);
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
