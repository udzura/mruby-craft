##
## CRaft::Server Test
##

assert("CRaft::Server.new") do
  s = CRaft::Server.new
  assert_equal(CRaft::Server, s.class)
end
