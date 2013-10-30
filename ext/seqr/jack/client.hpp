
///
// C++ class definition

VALUE rb_Jack_Client = Qnil;
class Jack_Client
{
  public:
    jack_client_t* jclient;
    
    Jack_Client() {};
    virtual void cpp2rb_mark() {};
    
    const char** get_port_names(
      const char*   name_pattern, // Regular expression or NULL
      const char*   type_pattern, // Regular expression or NULL
      unsigned long flags)        // JackPortFlags
    {
      return jack_get_ports(this->jclient, name_pattern, type_pattern, flags);
    }
};
CPP2RB_W_FUNCS(Jack_Client);


///
// Ruby-accessible C methods

extern "C" VALUE Jack_Client_m_open(VALUE self, VALUE _name, VALUE _options)
{
  Jack_Client* p;
  jack_status_t  status;
  
  p = Jack_Client_w_get(self);
  
  p->jclient = jack_client_open(StringValueCStr(_name), 
                         (jack_options_t)NUM2INT(_options), 
                         &status);
  
  return rb_ary_new3(2, INT2FIX(p->jclient), INT2FIX(status));
}

extern "C" VALUE Jack_Client_m_close(VALUE self)
{
  return INT2NUM(jack_client_close(Jack_Client_w_get(self)->jclient));
}

extern "C" VALUE Jack_Client_m_activate(VALUE self)
{
  return INT2NUM(jack_activate(Jack_Client_w_get(self)->jclient));
}

extern "C" VALUE Jack_Client_m_deactivate(VALUE self)
{
  return INT2NUM(jack_deactivate(Jack_Client_w_get(self)->jclient));
}

extern "C" VALUE Jack_Client_m_name(VALUE self)
{
  return rb_str_new2(jack_get_client_name(Jack_Client_w_get(self)->jclient));
}


///
// Bind to Ruby object

void Init_Jack_Client()
{
  rb_Jack_Client = rb_define_class_under(rb_Jack, "Client", rb_cObject);
  
  rb_define_alloc_func(rb_Jack_Client, Jack_Client_w_alloc);
  
  rb_define_method(rb_Jack_Client, "open",
    RUBY_METHOD_FUNC (Jack_Client_m_open),        2);
  rb_define_method(rb_Jack_Client, "activate",
    RUBY_METHOD_FUNC (Jack_Client_m_activate),    0);
  rb_define_method(rb_Jack_Client, "deactivate",
    RUBY_METHOD_FUNC (Jack_Client_m_deactivate),  0);
  rb_define_method(rb_Jack_Client, "name",
    RUBY_METHOD_FUNC (Jack_Client_m_name),        0);
}

