
///
// C++ class definition

VALUE rb_Node = Qnil;
class Node
{
  public:
    Node* source;
    VALUE rb_source;
    
    Node();
    void rb_mark() { rb_gc_mark(this->rb_source); }
};


///
// C++ methods

Node::Node()
{
  this->source = NULL;
  this->rb_source = Qnil;
}


///
// Ruby struct wrapping methods


// Macro to define garbage collector marking function
#define CPP2RB_W_MARK(Kls) \
extern "C" void Kls ## _w_mark(Kls* p) { p->rb_mark(); }

// Macro to define deallocator function
#define CPP2RB_W_FREE(Kls) \
extern "C" void Kls ## _w_free(Kls* p) { delete p; }

// Macro to define allocator function
#define CPP2RB_W_ALLOC(Kls) \
extern "C" VALUE Kls ## _w_alloc(VALUE klass) \
{ return Data_Wrap_Struct(klass, Kls ## _w_mark, Kls ## _w_free, new Kls()); }

// Macro to define pointer unwrapping function
#define CPP2RB_W_GET(Kls) \
extern "C" Kls* Kls ## _w_get(VALUE self) \
{ Kls* p; Data_Get_Struct(self, Kls, p); return p; }

// Macro to define all 4 '_w_' functions
#define CPP2RB_W_FUNCS(Kls) \
  CPP2RB_W_MARK(Kls) \
  CPP2RB_W_FREE(Kls) \
  CPP2RB_W_ALLOC(Kls) \
  CPP2RB_W_GET(Kls)


CPP2RB_W_FUNCS(Node)


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

