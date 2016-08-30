MRuby::Gem::Specification.new('mruby-craft') do |spec|
  spec.license = 'BSD'
  spec.authors = 'Uchio Kondo'
  spec.version = '0.0.1'

  require 'open3'
  require 'fileutils'

  unless defined? LIBCRAFT_CHECKOUT_URL
    LIBCRAFT_CHECKOUT_URL = "https://github.com/willemt/raft.git"
  end

  def libcraft_dir(b); "#{b.build_dir}/libcraft-master"; end
  def libcraft_libfile(b); libfile("#{libcraft_dir(b)}/libcraft"); end

  task :clean do
    FileUtils.rm_rf libcraft_dir(build)
  end

  def run_command env, command
    STDOUT.sync = true
    puts "EXEC\t[mruby-craft] #{command}"
    Open3.popen2e(env, command) do |stdin, stdout, thread|
      print stdout.read
      fail "#{command} failed" if thread.value != 0
    end
  end

  file libcraft_dir(build) do
    FileUtils.mkdir_p File.dirname(libcraft_dir(build))
    unless File.exist?(libcraft_dir(build))
      run_command ENV, "git clone --depth=1 #{LIBCRAFT_CHECKOUT_URL} #{libcraft_dir(build)}"
    end
  end

  file libcraft_libfile(build) => libcraft_dir(build) do
    Dir.chdir(libcraft_dir(build)) do
      cc_flags = build.cc.flags.flatten.delete_if{|f| f.include?("declaration-after-statement") }
      e = {
        'CC' => "#{build.cc.command} #{cc_flags.join(' ')}",
        'CXX' => "#{build.cxx.command} #{build.cxx.flags.join(' ')}",
        'LD' => "#{build.linker.command} #{build.linker.flags.join(' ')}",
        'AR' => build.archiver.command,
        'prefix' => libcraft_dir(build),
      }

      run_command e, "make static"
    end
  end

  file libfile("#{build.build_dir}/lib/libmruby") => libcraft_libfile(build)

  spec.cc.include_paths << "#{libcraft_dir(build)}/include"
  spec.linker.flags_before_libraries << libcraft_libfile(build)

  spec.cc.flags << "-fprofile-arcs -ftest-coverage"
  spec.linker.flags << "-fprofile-arcs"
end
