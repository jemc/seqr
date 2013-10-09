require 'seqr'
include Seqr

p Jack::Client.new
p Jack::Client.new 'dog', Jack::Options::NullOption
