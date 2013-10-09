require 'seqr'

client = Seqr::Ext::JackClient.new

p client
sleep 2
client.close
p client