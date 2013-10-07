
Gem::Specification.new do |s|
  
  s.name          = 'seqr'
  s.version       = '0.0.0'
  s.summary       = 'seqr'
  s.description   = "Experiments with audio sequencing in Ruby / C"
  s.authors       = ["Joe McIlvain"]
  s.email         = 'joe.eli.mac@gmail.com'
  
  s.files         = Dir["lib/**/*.{rb,so}", 
                        "ext/**/*.{rb,c}", 
                        "LICENSE", "*.md"]
  s.require_path  = 'lib'
  
  s.homepage      = 'https://github.com/jemc/seqr/'
  s.licenses      = "MIT"
  
  s.add_development_dependency('rake')
  s.add_development_dependency('rake-compiler')
  
end
