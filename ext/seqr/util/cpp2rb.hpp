
///
// Ruby wrapping functions for C++ classes

// Macro to define garbage collector marking function
#define CPP2RB_W_MARK(Kls) \
extern "C" void Kls ## _w_mark(Kls* p) { p->cpp2rb_mark(); }

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

// Call this macro to register the defined functions as part of the class
#define CPP2RB_W_FUNCS_REG(Kls) \
  rb_define_alloc_func(rb_ ## Kls, Kls ## _w_alloc);
