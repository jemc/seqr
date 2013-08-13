
require 'rake/extensiontask'

gemname = 'jemc_cexample'
task :default => [:g]

# Rebuild c extensions
spec = Gem::Specification.load("#{gemname}.gemspec")
Rake::ExtensionTask.new(gemname, spec)

# Rebuild gem
task :g=>[:compile] do exec "
rm #{gemname}*.gem
gem build #{gemname}.gemspec
gem install #{gemname}*.gem" end
