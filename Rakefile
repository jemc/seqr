
require 'rake/extensiontask'

gem_name = 'jemc_c-example'
task :default => [:compile]

spec = Gem::Specification.load("#{gem_name}.gemspec")
Rake::ExtensionTask.new(gem_name, spec)

