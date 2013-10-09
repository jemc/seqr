require 'seqr'

client = Seqr::Jack::Client.new

p client
sleep 2
client.close
p client