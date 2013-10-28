
require 'pry'

at_exit {`killall jackd`}

module Seqr
  
  class Node
    def foo
      "foo!"
    end
  end
  
  module Jack
    
    class Client
      def initialize(name="Jack::Client", options=Jack::Options::NullOption)
        _, status = open name, options
        if (status & Status::Failure) != 0
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


p Jack::Client.new('dog')
sleep 1

# p x = Node.new
# p y = PassThruNode.new

# p x.source=nil
# p y.source=x
# p x.source
# p y.source