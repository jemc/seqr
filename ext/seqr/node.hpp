
///
// C++ class definition

VALUE rb_Node = Qnil;
class Node
{
  public:
    Node* source;
    VALUE rb_source;
    
    Node();
    void cpp2rb_mark() { rb_gc_mark(this->rb_source); }
};
CPP2RB_W_FUNCS(Node)


///
// C++ methods

Node::Node()
{
  this->source = NULL;
  this->rb_source = Qnil;
}


///
// Ruby-accessible C methods

extern "C" VALUE Node_m_source(VALUE self)
{
  return Node_w_get(self)->rb_source;
}

extern "C" VALUE Node_m_source_setter(VALUE self, VALUE node) {
  Node* c_self = Node_w_get(self);
  
  c_self->rb_source = node;
  
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
  rb_Node = rb_define_class_under(rb_ThisModule, "Node", rb_cObject);
  
  rb_define_alloc_func(rb_Node, Node_w_alloc);
  
  rb_define_method(rb_Node, "source",
    RUBY_METHOD_FUNC (Node_m_source),        0);
  rb_define_method(rb_Node, "source=",
    RUBY_METHOD_FUNC (Node_m_source_setter), 1);
  
  ///
  // Init child classes
  
  Init_PassThruNode();
}

