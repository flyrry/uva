(1..9999).each do |i|
  print i.to_s(2).count("1"), " ", i.to_s.to_i(16).to_s(2).count("1"), "\n"
end
