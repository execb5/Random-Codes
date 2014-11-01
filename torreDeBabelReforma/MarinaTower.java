import java.util.ArrayList;
import java.util.HashSet;

public class MarinaTower {
        private ArrayList<HashSet<Integer>> elevators;
        private boolean[] marks;
        private int height;

        public MarinaTower(int n, int numEle) {
                elevators = new ArrayList<HashSet<Integer>>(numEle);
                marks = new boolean[numEle];
                height = n;
        }

        public void addElevator(HashSet<Integer> elevator) {
                elevators.add(elevator);
        }

        public boolean isItPossible(int from, int to) {
                HashSet<Integer> currentElevator = null;
                for (HashSet<Integer> ele : elevators) {
                        if (ele.contains(from))
                                currentElevator = ele;
                }
                if (currentElevator == null)
                        return false;
                if (currentElevator.contains(to))
                        return true;
                return realFunction(currentElevator, to);
        }

        private boolean realFunction(HashSet<Integer> ele, int to) {
                int mark = elevators.indexOf(ele);
                if (marks[mark])
                        return false;
                marks[mark] = true;
                boolean possibility = false;
                for (HashSet<Integer> next : elevators) {
                        HashSet<Integer> intersection = new HashSet<Integer>(ele);
                        intersection.retainAll(next);
                        if (intersection.isEmpty())
                                continue;
                        if (next.contains(to))
                                return true;
                        possibility = possibility || realFunction(next, to);
                }
                return possibility;
        }

        public String toString() {
                return "Number of elevators: " + elevators.size();
        }

        public int getHeight() {
                return this.height;
        }
}
