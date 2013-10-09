require 'seqr'
include Seqr

at_exit {`killall jackd`}

p Jack::Client.new.name
p Jack::Client.new('dog').name
p Jack::Client.new('dog', Jack::Options::UseExactName).name # Will raise exception