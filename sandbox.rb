require 'seqr'
include Seqr

p Jack::Options::NullOption
p Jack::Options::NoStartServer
p Jack::Options::UseExactName
p Jack::Options::ServerName
p Jack::Options::LoadName
p Jack::Options::LoadInit
p Jack::Options::SessionID

p Jack::PortFlags::IsInput
p Jack::PortFlags::IsOutput
p Jack::PortFlags::IsPhysical
p Jack::PortFlags::CanMonitor
p Jack::PortFlags::IsTerminal

p Jack::Status::Failure
p Jack::Status::InvalidOption
p Jack::Status::NameNotUnique
p Jack::Status::ServerStarted
p Jack::Status::ServerFailed
p Jack::Status::ServerError
p Jack::Status::NoSuchClient
p Jack::Status::LoadFailure
p Jack::Status::InitFailure
p Jack::Status::ShmFailure
p Jack::Status::VersionError
p Jack::Status::BackendError
p Jack::Status::ClientZombie
