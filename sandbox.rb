require 'seqr'
include Seqr

at_exit {`killall jackd`}

# err = Jack::StatusError.new
$err = Jack::StatusError.new "text", 12
p $err
p $err.status
# $err.status = 55; # will fail

# p Jack::Client.new.name
# p Jack::Client.new('dog').name
# p Jack::Client.new('dog', Jack::Options::UseExactName).name # Will raise exception