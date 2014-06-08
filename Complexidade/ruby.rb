#!/usr/bin/env ruby

class BackTracker

	def initialize(initial_set, half)
		@setTwo = initial_set
		@half = half
		@setOne = []
		puts "\nCreating BackTracker Object with #{@setTwo} as it\'s initial set, and #{@half} as the half\n"
	end

	def solve
		solveAux(0, @half, @setOne.clone, @setTwo.clone)
	end

	def solveAux(sum, half, set1, set2)
		return if sum > half
		if sum == half
			sum2 = 0
			set2.each {|i| sum += i}
			puts "\nSet1: #{set1.to_s}\nSet2: #{set2.to_s}\n"
			return
		end
		set2.each do |i|
			a = set1.clone
			b = set2.clone
			a.push i
			b.delete i
			solveAux(sum + i, half, a, b)
		end
	end

	private :solveAux

end

if __FILE__ == $0
	set = ARGV.map {|i| i.to_i}
	sum = 0
	set.each {|i| sum += i}
	if sum % 2 == 0
		half = sum / 2
		if set.max <= half
			bt = BackTracker.new(set, half)
			bt.solve
		else
			puts 'Not found! D:'
		end
	else
		puts 'Not found! D:'
	end
end
