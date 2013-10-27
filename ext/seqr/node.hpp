
///
// Node C++ class definition

class Node
{
  public:
    Node* source_node;
    VALUE source_node_rb;
    
    Node();
};


///
// Node C++ methods

Node::Node()
{
  this->source_node = NULL;
  this->source_node_rb = Qnil;
}


///
// Ruby struct wrapping methods

extern "C" void Node_w_mark(Node* p)
{
  rb_gc_mark(p->source_node_rb);
}

extern "C" void Node_w_free(Node* p)
{
  delete p;
}

extern "C" Node* Node_w_get(VALUE self)
{
  Node* node_ptr;
  Data_Get_Struct(self, Node, node_ptr);
  return node_ptr;
}

extern "C" VALUE Node_w_alloc(VALUE klass)
{
  return Data_Wrap_Struct(klass, Node_w_mark, Node_w_free, new Node());
}


///
// Ruby-accessible C methods

extern "C" VALUE Node_m_source_node(VALUE self)
{
  return Node_w_get(self)->source_node_rb;
}

extern "C" VALUE Node_m_source_node_setter(VALUE self, VALUE node) {
  Node* c_self = Node_w_get(self);
  
  c_self->source_node_rb = node;
  
  if(node==Qnil) c_self->source_node = NULL;
  else c_self->source_node = Node_w_get(node);
  
  return node;
}


///
// Bind to Ruby object

void Init_Node()
{
  VALUE Node = rb_eval_string("Seqr::Node");
 
  rb_define_alloc_func(Node, Node_w_alloc);
  
  rb_define_method(Node, "source_node",
  RUBY_METHOD_FUNC(Node_m_source_node),        0);
  rb_define_method(Node, "source_node=",
  RUBY_METHOD_FUNC(Node_m_source_node_setter), 1);
}
