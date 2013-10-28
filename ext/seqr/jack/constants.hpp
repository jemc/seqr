
VALUE rb_Jack_Options   = Qnil;
VALUE rb_Jack_PortFlags = Qnil;
VALUE rb_Jack_Status    = Qnil;

void Init_Jack_Options()
{
  rb_define_const(rb_Jack_Options, "NullOption",    INT2NUM(JackNullOption));
  rb_define_const(rb_Jack_Options, "NoStartServer", INT2NUM(JackNoStartServer));
  rb_define_const(rb_Jack_Options, "UseExactName",  INT2NUM(JackUseExactName));
  rb_define_const(rb_Jack_Options, "ServerName",    INT2NUM(JackServerName));
  rb_define_const(rb_Jack_Options, "LoadName",      INT2NUM(JackLoadName));
  rb_define_const(rb_Jack_Options, "LoadInit",      INT2NUM(JackLoadInit));
  rb_define_const(rb_Jack_Options, "SessionID",     INT2NUM(JackSessionID));
}

void Init_Jack_PortFlags()
{
  rb_define_const(rb_Jack_PortFlags, "IsInput",     INT2NUM(JackPortIsInput));
  rb_define_const(rb_Jack_PortFlags, "IsOutput",    INT2NUM(JackPortIsOutput));
  rb_define_const(rb_Jack_PortFlags, "IsPhysical",  INT2NUM(JackPortIsPhysical));
  rb_define_const(rb_Jack_PortFlags, "CanMonitor",  INT2NUM(JackPortCanMonitor));
  rb_define_const(rb_Jack_PortFlags, "IsTerminal",  INT2NUM(JackPortIsTerminal));
}

void Init_Jack_Status()
{
  rb_define_const(rb_Jack_Status, "Failure",        INT2NUM(JackFailure));
  rb_define_const(rb_Jack_Status, "InvalidOption",  INT2NUM(JackInvalidOption));
  rb_define_const(rb_Jack_Status, "NameNotUnique",  INT2NUM(JackNameNotUnique));
  rb_define_const(rb_Jack_Status, "ServerStarted",  INT2NUM(JackServerStarted));
  rb_define_const(rb_Jack_Status, "ServerFailed",   INT2NUM(JackServerFailed));
  rb_define_const(rb_Jack_Status, "ServerError",    INT2NUM(JackServerError));
  rb_define_const(rb_Jack_Status, "NoSuchClient",   INT2NUM(JackNoSuchClient));
  rb_define_const(rb_Jack_Status, "LoadFailure",    INT2NUM(JackLoadFailure));
  rb_define_const(rb_Jack_Status, "InitFailure",    INT2NUM(JackInitFailure));
  rb_define_const(rb_Jack_Status, "ShmFailure",     INT2NUM(JackShmFailure));
  rb_define_const(rb_Jack_Status, "VersionError",   INT2NUM(JackVersionError));
  rb_define_const(rb_Jack_Status, "BackendError",   INT2NUM(JackBackendError));
  rb_define_const(rb_Jack_Status, "ClientZombie",   INT2NUM(JackClientZombie));
}
