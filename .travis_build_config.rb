MRuby::Build.new do |conf|
  if ENV['CC'] == 'clang'
    toolchain :clang
  else
    toolchain :gcc
  end

  conf.gembox 'default'
  conf.gem '../mruby-craft'
  conf.enable_test
end
