require 'seqr'
include Seqr

p Jack::Client.new.name
p Jack::Client.new('dog', Jack::Options::NullOption).name
