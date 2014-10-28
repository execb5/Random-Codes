public class Tower {
        private int height;
        private boolean[][] paths;

        public Tower(int n) {
                height = n;
                paths = new boolean[height][height];
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

        public boolean isItPossible(int whereIam, int whereIWannaGo) {
                return false;
        }

        public int getHeight(){
                return this.height;
        }
}
