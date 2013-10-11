require 'seqr'
include Seqr

at_exit {`killall jackd`}

class Jack::Client
  def initialize(name="Jack::Client", options=Jack::Options::NullOption)
    status = open name, options
    if status & Jack::Status::Failure
      raise Jack::StatusError.new("Failed to open the Jack::Client", status)
    end
  end
end

p Jack::Client.new.open("Jack::Client",Jack::Options::NullOption)
p Jack::Client.new.open('dog',Jack::Options::NullOption)
p Jack::Client.new.open('dog',Jack::Options::UseExactName)