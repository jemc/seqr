
Gem::Specification.new do |s|
  
  s.name          = 'jemc_c-example'
  s.version       = '0.0.0'
  s.summary       = 'jemc_c-example'
  s.description   = "Practice writing/dealing with c extensions for ruby."\
                    " May also be used as skeleton for future c extensions."
  s.authors       = ["Joe McIlvain"]
  s.email         = 'joe.eli.mac@gmail.com'
  
  s.files         = Dir["{lib,ext}/**/*.{rb,c}", "LICENSE", "*.md"]
  s.require_path  = 'lib'
  
  s.homepage      = 'https://github.com/jemc/ruby-c-ext/'
  s.licenses      = "MIT"
  
  s.add_development_dependency('rake')
  s.add_development_dependency('rake-compiler')
  
end
