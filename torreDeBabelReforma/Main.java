import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
        public static void main(String[] args) {
                testFile("testFiles/testFile");
                testFile("testFiles/c100010");
                testFile("testFiles/c100012");
                testFile("testFiles/c100014");
                testFile("testFiles/c100016");
                testFile("testFiles/c100018");
                testFile("testFiles/c100020");
                testFile("testFiles/c100024");
                testFile("testFiles/c20010");
                testFile("testFiles/c20012");
                testFile("testFiles/c20014");
                testFile("testFiles/c2008");
                testFile("testFiles/c40010");
                testFile("testFiles/c40012");
                testFile("testFiles/c40014");
                testFile("testFiles/c40016");
                testFile("testFiles/c60010");
                testFile("testFiles/c60012");
                testFile("testFiles/c60014");
                testFile("testFiles/c60016");
                testFile("testFiles/c60018");
                testFile("testFiles/c80012");
                testFile("testFiles/c80014");
                testFile("testFiles/c80016");
                testFile("testFiles/c80018");
                testFile("testFiles/c80020");
                testFile("testFiles/c80022");
                testFile("testFiles/c80024");
        }

        private static void testFile(String name) {
                try {
                        System.out.println("Testing file: " + name);
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
