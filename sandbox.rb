require 'seqr'
include Seqr

at_exit {`killall jackd`}

module Jack
  
  class Client
    def initialize(name="Jack::Client", options=Jack::Options::NullOption)
      status = open name, options
      if status & Status::Failure
        raise StatusError.new("Failed to open the Jack::Client", status)
      end
    end
  end
  
  class Error < RuntimeError; end
  
  class StatusError < Error
    attr_reader :status
    
    def initialize(str="", status=nil)
      super(str)
      @status = status
    end
  end
  
end


p Jack::Client.new.open("Jack::Client",Jack::Options::NullOption)
p Jack::Client.new.open('dog',Jack::Options::NullOption)
p Jack::Client.new.open('dog',Jack::Options::UseExactName)