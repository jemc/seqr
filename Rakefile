
require 'rake/extensiontask'

gemname = 'seqr'
task :default => [:sandbox]

# Rebuild c extensions
spec = Gem::Specification.load("#{gemname}.gemspec")
Rake::ExtensionTask.new(gemname, spec)

# Rebuild gem
task :g=>[:compile] do
  print `rm #{gemname}*.gem`
  print `gem build #{gemname}.gemspec`
  print `gem install #{gemname}*.gem`
end

# Run sandbox.rb after building
task :sandbox do
  silent { Rake::Task[:g].invoke }
  puts
  require "./sandbox.rb"
  puts
end

# Silence stdout and stderr
def silent
  begin
    memo_stdout = $stdout
    memo_stderr = $stderr
    $stdout = File.new('/dev/null', 'w')
    $stderr = File.new('/dev/null', 'w')
    yield
  ensure
    $stdout = memo_stdout
    $stdout = memo_stderr
  end
end