#!/usr/bin/env ruby

class Solver

	def initialize(initial_set, half)
		@set= initial_set
		@half = half
		@solutions = {}
		puts "\nCreating Solver Object with #{@set} as it\'s initial set, and #{@half} as the half\n"
	end

	def solve
		solveAux(0, @set.length, [], @set.clone, 0)
	end

	def solveAux(sum, size, partition1, partition2, index)
		return if sum > @half
		if sum == @half
			unless @solutions.has_value? partition1
				puts '---------------'
				puts partition1.to_s
				puts partition2.to_s
				puts '---------------'
				@solutions.merge!(partition1 => partition2)
			end
		end
		for i in index..(size - 1)
			copy1 = partition1.clone
			copy2 = partition2.clone
			val = @set[i]
			copy1.push val
			copy2.delete val
			solveAux(sum + val, size, copy1, copy2, index += 1)
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
			bt = Solver.new(set, half)
			bt.solve
		else
			puts 'Not found! D:'
		end
	else
		puts 'Not found! D:'
	end
end
