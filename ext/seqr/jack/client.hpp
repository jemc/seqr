
VALUE rb_Jack_Client = Qnil;

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

///
// Bind to Ruby object

void Init_Jack_Client()
{
  rb_define_method(rb_Jack_Client, "open",
    RUBY_METHOD_FUNC (Jack_Client_m_open),        2);
  rb_define_method(rb_Jack_Client, "activate",
    RUBY_METHOD_FUNC (Jack_Client_m_activate),    0);
  rb_define_method(rb_Jack_Client, "deactivate",
    RUBY_METHOD_FUNC (Jack_Client_m_deactivate),  0);
  rb_define_method(rb_Jack_Client, "name",
    RUBY_METHOD_FUNC (Jack_Client_m_name),        0);
}

