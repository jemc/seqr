
#include <ruby.h>
#include <jack/jack.h>


/// 
// Module/Class Hierarchy

/* c-extension */      extern "C" void Init_seqr();
VALUE Jack               = Qnil;  void Init_Jack();
  VALUE Jack_Client      = Qnil;  void Init_Jack_Client();
  
  VALUE Jack_Options     = Qnil;  void Init_Jack_Options();
  VALUE Jack_PortFlags   = Qnil;  void Init_Jack_PortFlags();
  VALUE Jack_Status      = Qnil;  void Init_Jack_Status();


///
// Function Declarations

extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _options, VALUE _name);
extern "C" VALUE Jack_Client_m_close(VALUE self);
extern "C" VALUE Jack_Client_m_activate(VALUE self);
extern "C" VALUE Jack_Client_m_deactivate(VALUE self);
extern "C" VALUE Jack_Client_m_name(VALUE self);




///
// Node
class Node
{
  public:
    Node* source_node;
    VALUE rb_source_node;
    
    Node();
};

Node::Node()
{
  this->source_node = NULL;
  this->rb_source_node = Qnil;
}

extern "C" void wrap_Node_mark(Node* p)
{
  rb_gc_mark(p->rb_source_node);
}

extern "C" void wrap_Node_free(Node* p)
{
  delete p;
}

extern "C" Node* wrap_Node_get(VALUE self)
{
  Node* node_ptr;
  Data_Get_Struct(self, Node, node_ptr);
  return node_ptr;
}

extern "C" VALUE wrap_Node_alloc(VALUE klass) {
  Node* p = new Node();
  
  return Data_Wrap_Struct(klass, wrap_Node_mark, wrap_Node_free, p);
}

extern "C" VALUE Node_m_source_node(VALUE self) {
  return wrap_Node_get(self)->rb_source_node;
}

extern "C" VALUE Node_m_source_node_setter(VALUE self, VALUE node) {
  Node* c_self = wrap_Node_get(self);
  
  c_self->rb_source_node = node;
  
  if(node==Qnil) c_self->source_node = NULL;
  else c_self->source_node = wrap_Node_get(node);
  
  return node;
}

void Init_Node()
{
  VALUE Node = rb_eval_string("Seqr::Node");
 
  rb_define_alloc_func(Node, wrap_Node_alloc);
  
  rb_define_method(Node, "source_node",
  RUBY_METHOD_FUNC(Node_m_source_node),        0);
  rb_define_method(Node, "source_node=",
  RUBY_METHOD_FUNC(Node_m_source_node_setter), 1);
}



///
// Module/Class Initialization

extern "C" void Init_seqr()
{
  Init_Jack();
  Init_Node();
}

void Init_Jack()
{
  Jack = rb_eval_string("Seqr::Jack");
  Jack_Client      = rb_define_class_under (Jack, "Client", rb_cObject);
  Init_Jack_Client();
  
  Jack_Options     = rb_define_module_under(Jack, "Options");
  Jack_PortFlags   = rb_define_module_under(Jack, "PortFlags");
  Jack_Status      = rb_define_module_under(Jack, "Status");
  Init_Jack_Options();
  Init_Jack_PortFlags();
  Init_Jack_Status();
}

void Init_Jack_Client()
{
  rb_define_method(Jack_Client, "open",
  RUBY_METHOD_FUNC(Jack_Client_m_open),        2);
  rb_define_method(Jack_Client, "activate",
  RUBY_METHOD_FUNC(Jack_Client_m_activate),    0);
  rb_define_method(Jack_Client, "deactivate",
  RUBY_METHOD_FUNC(Jack_Client_m_deactivate),  0);
  rb_define_method(Jack_Client, "name",
  RUBY_METHOD_FUNC(Jack_Client_m_name),        0);
}

void Init_Jack_Options()
{
  rb_define_const(Jack_Options, "NullOption",    INT2NUM(JackNullOption));
  rb_define_const(Jack_Options, "NoStartServer", INT2NUM(JackNoStartServer));
  rb_define_const(Jack_Options, "UseExactName",  INT2NUM(JackUseExactName));
  rb_define_const(Jack_Options, "ServerName",    INT2NUM(JackServerName));
  rb_define_const(Jack_Options, "LoadName",      INT2NUM(JackLoadName));
  rb_define_const(Jack_Options, "LoadInit",      INT2NUM(JackLoadInit));
  rb_define_const(Jack_Options, "SessionID",     INT2NUM(JackSessionID));
}

void Init_Jack_PortFlags()
{
  rb_define_const(Jack_PortFlags, "IsInput",     INT2NUM(JackPortIsInput));
  rb_define_const(Jack_PortFlags, "IsOutput",    INT2NUM(JackPortIsOutput));
  rb_define_const(Jack_PortFlags, "IsPhysical",  INT2NUM(JackPortIsPhysical));
  rb_define_const(Jack_PortFlags, "CanMonitor",  INT2NUM(JackPortCanMonitor));
  rb_define_const(Jack_PortFlags, "IsTerminal",  INT2NUM(JackPortIsTerminal));
}

void Init_Jack_Status()
{
  rb_define_const(Jack_Status, "Failure",        INT2NUM(JackFailure));
  rb_define_const(Jack_Status, "InvalidOption",  INT2NUM(JackInvalidOption));
  rb_define_const(Jack_Status, "NameNotUnique",  INT2NUM(JackNameNotUnique));
  rb_define_const(Jack_Status, "ServerStarted",  INT2NUM(JackServerStarted));
  rb_define_const(Jack_Status, "ServerFailed",   INT2NUM(JackServerFailed));
  rb_define_const(Jack_Status, "ServerError",    INT2NUM(JackServerError));
  rb_define_const(Jack_Status, "NoSuchClient",   INT2NUM(JackNoSuchClient));
  rb_define_const(Jack_Status, "LoadFailure",    INT2NUM(JackLoadFailure));
  rb_define_const(Jack_Status, "InitFailure",    INT2NUM(JackInitFailure));
  rb_define_const(Jack_Status, "ShmFailure",     INT2NUM(JackShmFailure));
  rb_define_const(Jack_Status, "VersionError",   INT2NUM(JackVersionError));
  rb_define_const(Jack_Status, "BackendError",   INT2NUM(JackBackendError));
  rb_define_const(Jack_Status, "ClientZombie",   INT2NUM(JackClientZombie));
}

///
// Function Implementations

#define Jack_Client_ptr(obj) ((jack_client_t*)NUM2LONG(rb_iv_get(obj, "@ptr")))

extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _name, VALUE _options)
{
  jack_client_t* ptr;
  jack_status_t  status;
  
  ptr = jack_client_open(StringValueCStr(_name), 
                         (jack_options_t)NUM2INT(_options), 
                         &status);
  
  return rb_ary_new3(2, INT2FIX(ptr), INT2FIX(status));
}

extern "C" VALUE Jack_Client_m_close(VALUE self)
{
  return INT2NUM(jack_client_close(Jack_Client_ptr(self)));
}

extern "C" VALUE Jack_Client_m_activate(VALUE self)
{
  return INT2NUM(jack_activate(Jack_Client_ptr(self)));
}

extern "C" VALUE Jack_Client_m_deactivate(VALUE self)
{
  return INT2NUM(jack_deactivate(Jack_Client_ptr(self)));
}

extern "C" VALUE Jack_Client_m_name(VALUE self)
{
  return rb_str_new2(jack_get_client_name(Jack_Client_ptr(self)));
}