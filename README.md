# mruby-craft   [![Build Status](https://travis-ci.org/udzura/mruby-craft.svg?branch=master)](https://travis-ci.org/udzura/mruby-craft)
CRaft class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-craft'
end
```
## example
```ruby
p CRaft.hi
#=> "hi!!"
t = CRaft.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the BSD License:
- see LICENSE file
