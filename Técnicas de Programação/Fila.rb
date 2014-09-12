require 'contracts'
include Contracts

class PositiveNum
  def self.valid? num
    num > 0
  end
end

class NegativeNum
  def self.valid? num
    num < 0
  end
end

class Fila
  
  Contract Num => lambda { |x| x.is_a? Array and x.length == 0 }
  def initialize max
    @max = max
    @fila = []
  end

  Contract lambda { @fila.is_a Array} => Bool
  def empty?
    @fila.empty?
  end

  def full?
    
  end

  Contract lambda {|x| x.is_a? Numeric and @fila.nil? } => Any
  def enqueue num
    @fila << num
    @fila.clone
  end

  def dequeue
    @fila.clone
  end

  Contract lambda { @fila.empty? } => Num
  def last
    @fila.last
  end

  Contract lambda { @fila.empty? } => Num
  def first
    @fila.first
  end

  def size
    @fila.length
  end

end

f = Fila.new 3
f.enqueue 1
f.last

#class Doctor
    #["rhinoplasty", "checkup", "interpretive_dance"].each do |action|
      #define_method("perform_#{action}") do |argument|
        #"performing #{action.gsub('_', ' ')} on #{argument}"
      #end
    #end
#end

#doctor = Doctor.new
#puts doctor.perform_rhinoplasty("nose")
#puts doctor.perform_checkup("throat")
#puts doctor.perform_interpretive_dance("in da club")
