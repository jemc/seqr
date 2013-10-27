
///
// C++ class definition

VALUE rb_Node = Qnil;
class Node
{
  public:
    Node* source;
    VALUE source_rb;
    
    Node();
};


///
// C++ methods

Node::Node()
{
  this->source = NULL;
  this->source_rb = Qnil;
}


///
// Ruby struct wrapping methods

extern "C" void Node_w_mark(Node* p)
{
  rb_gc_mark(p->source_rb);
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

extern "C" VALUE Node_m_source(VALUE self)
{
  return Node_w_get(self)->source_rb;
}

extern "C" VALUE Node_m_source_setter(VALUE self, VALUE node) {
  Node* c_self = Node_w_get(self);
  
  c_self->source_rb = node;
  
  if(node==Qnil) c_self->source = NULL;
  else c_self->source = Node_w_get(node);
  
  return node;
}


///
// Include child classes

#include "node/pass_thru.hpp"


///
// Bind to Ruby object

void Init_Node()
{
  rb_Node = rb_define_class_under(rb_Module, "Node", rb_cObject);
  
  rb_define_alloc_func(rb_Node, Node_w_alloc);
  
  rb_define_method(rb_Node, "source",
    RUBY_METHOD_FUNC (Node_m_source),        0);
  rb_define_method(rb_Node, "source=",
    RUBY_METHOD_FUNC (Node_m_source_setter), 1);
  
  ///
  // Init child classes
  
  Init_PassThruNode();
}

