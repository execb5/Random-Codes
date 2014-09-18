class Graph
  attr_accessor :elevators
  def initialize
    elevators = []
  end
end

class Elevator
  attr_accessor :reachable_floors
  def initialize base, step, max
    reachable_floors = []
    while base < max do
      floor << base
      base += step
    end
  end
end

f = File.open "case_test", "r"
puts f.gets
puts f.gets
f.each_line do |line|
  line.split(/\ /).each do |l|
    puts l
  end
end
f.close
