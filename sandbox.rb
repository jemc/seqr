require 'seqr'

client = Seqr::Jack::Client.new

p client
sleep 2
client.close
client.close
p client