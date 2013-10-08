require 'seqr'

p Seqr::Ext::JackClient
p Seqr::Ext::JackClient.new.instance_variable_get :@initialized