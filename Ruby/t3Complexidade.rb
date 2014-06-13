#!/usr/bin/env ruby

class Solver

	attr_accessor :qtySolutions

	def initialize(initial_set, half)
		@set= initial_set
		@half = half
		@solutions = {}
		@qtySolutions = 0
		puts "\nCreating Solver Object with #{@set} as it\'s initial set, and #{@half} as the half\n"
	end

	def solve
		a = [].push @set[0]
		b = @set.clone
		b.slice!(b.index(@set[0]))
		solveAux(0 + @set[0], @set.length, a, b, 1)
	end

	def solveAux(sum, size, partition1, partition2, index)
		return if sum > @half
		if sum == @half
			@qtySolutions += 1
			#puts '---------------'
			#puts partition1.to_s
			#puts partition2.to_s
			#puts '---------------'
		end
		for i in index..(size - 1)
			copy1 = partition1.clone
			copy2 = partition2.clone
			copy1.push @set[i]
			copy2.slice!(@set[i])
			solveAux(sum + @set[i], size, copy1, copy2, index += 1)
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
			puts "How many ways to divide the set?  #{bt.qtySolutions.to_s}."
		else
			puts 'Not found! D:'
		end
	else
		puts 'Not found! D:'
	end
end
