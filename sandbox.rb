require 'seqr'

client = Seqr::Ext::JackClient.new

p client
sleep 2
client.close
client.close
p client