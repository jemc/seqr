require 'seqr'
include Seqr

at_exit {`killall jackd`}

p Jack::Client.new.name
p Jack::Client.new('dog').name