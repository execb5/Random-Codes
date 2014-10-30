import java.util.ArrayList;

public class Tower {
        private int height;
        private boolean[][] paths;
        private boolean[] marks;

        public Tower(int n) {
                height = n;
                paths = new boolean[height][height];
                marks = new boolean[height];
        }

        public void insertPath(int floor1, int floor2) {
                paths[floor1][floor2] = true;
        }


        public void printMatrix() {
                for (int i = 0; i < height; i++) {
                        for (int j = 0; j < height; j++)
                                System.out.print(paths[i][j] + " ");
                        System.out.print("\n");
                }
        }

        public boolean isItPossible(int from, int to) {
                if (from == to)
                        return true;
                marks[from] = true;
                boolean possibility = false;
                for (Integer neighbor : getNeighbors(from)) {
                        if (!marks[neighbor])
                                possibility = possibility ||
                                        isItPossible(neighbor, to);
                }
                return possibility;
        }

        private ArrayList<Integer> getNeighbors(int currentNode) {
                ArrayList<Integer> l = new ArrayList<Integer>(height);
                for (int i = 0; i < height; i++) {
                        if (paths[currentNode][i])
                                l.add(i);
                }
                return l;
        }

        public int getHeight(){
                return this.height;
        }
}

