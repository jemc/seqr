
require 'pry'

at_exit {`killall jackd`}

require 'seqr'
include Seqr


module Seqr
  
  module Jack
    
    class Client
      
      def self.new(*args)
        @instance ||= super
      end
      
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

NodeNetwork.activate Jack::Client.new

o = JackOutputNode.new
o.source = CausalFilterNode.new
o.source.source = JackInputNode.new

filter = o.source

filter.bypass = false
filter.gain = 0.1

while true
  p filter.fb_coeffs = [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
    filter.ff_coeffs = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
  sleep 0.2
  p filter.fb_coeffs = [0.25, 0.75]
    filter.ff_coeffs = [0.25, 0.75]
  sleep 0.2
end