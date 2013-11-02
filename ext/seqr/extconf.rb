
require 'mkmf'

ext_name = 'seqr'

dir_config ext_name

unless find_header('jack/jack.h')
  abort "Couldn't find the required jack headers.  Install jack-devel."
end

unless find_library('jack', 'jack_client_open')
  abort "Couldn't find the required jack runtime.  Install libjack."
end

$CPPFLAGS += '--std=c++11'
# p $CPPFLAGS

create_makefile ext_name
