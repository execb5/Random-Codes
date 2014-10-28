import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
        public static void main(String[] args) {
                testFile("testFiles/testFile");
        }

        private static void testFile(String name) {
                try {
                        BufferedReader br = new BufferedReader(new
                                        FileReader(name));
                        String[] parts = br.readLine().split(" ");
                        Tower t = new Tower(Integer.parseInt(parts[0]));
                        parts = br.readLine().split(" ");
                        int whereIam = Integer.parseInt(parts[0]);
                        int whereIWannaGo = Integer.parseInt(parts[1]);
                        String currentLine = null;
                        while ((currentLine = br.readLine()) != null) {
                                parts = currentLine.split(" ");
                                int baseFloor = Integer.parseInt(parts[0]);
                                int eStep = Integer.parseInt(parts[1]);
                                int nextFloor = baseFloor + eStep;
                                while (nextFloor < t.getHeight()) {
                                        t.insertPath(baseFloor, nextFloor);
                                        baseFloor = nextFloor;
                                        nextFloor = nextFloor + eStep;
                                }
                        }
                        System.out.print("File read: " + name);
                        long begin = System.currentTimeMillis();
                        boolean answer = t.isItPossible(whereIam,
                                        whereIWannaGo);
                        long end = System.currentTimeMillis();
                        System.out.println("Is it possible to go from " +
                                        whereIam + " to " + whereIWannaGo  + 
                                        "? " + answer);
                        System.out.println(end - begin + "ms\n\n");
                } catch(Exception e) {
                        e.printStackTrace();
                }
        }
}
