
at_exit {`killall jackd`}

module Seqr
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
end

require 'seqr'
include Seqr



p Jack::Client.new
p Jack::Client.new('dog')
sleep 0.5
p Jack::Client.new('dog', Jack::Options::UseExactName)