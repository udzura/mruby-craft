##
## CRaft Test
##

assert("CRaft#hello") do
  t = CRaft.new "hello"
  assert_equal("hello", t.hello)
end

assert("CRaft#bye") do
  t = CRaft.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("CRaft.hi") do
  assert_equal("hi!!", CRaft.hi)
end
