##
## CRaft::Server Test
##

assert("CRaft::Entry.new") do
  s = CRaft::Entry.new
  assert_equal(CRaft::Entry, s.class)
end
