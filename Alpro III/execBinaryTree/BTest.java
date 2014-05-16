import java.io.BufferedReader;
import java.io.FileReader;

public class BTest {

  public static void main( String[] args ) {

		String sCurrentLine = null;
		BufferedReader br;
		BinaryTree T0, T1, T2, T3;
		try {
			br = new BufferedReader(new FileReader("t0"));
			T0 = new BinaryTree();
			while ((sCurrentLine = br.readLine()) != null) {
				T0.insert(Integer.parseInt(sCurrentLine));
			}
			br.close();

			br = new BufferedReader(new FileReader("t1"));
			T1 = new BinaryTree();
			while ((sCurrentLine = br.readLine()) != null) {
				T1.insert(Integer.parseInt(sCurrentLine));
			}
			br.close();

			br = new BufferedReader(new FileReader("t2"));
			T2 = new BinaryTree();
			while ((sCurrentLine = br.readLine()) != null) {
				T2.insert(Integer.parseInt(sCurrentLine));
			}
			br.close();

			br = new BufferedReader(new FileReader("t3"));
			T3 = new BinaryTree();
			while ((sCurrentLine = br.readLine()) != null) {
				T3.insert(Integer.parseInt(sCurrentLine));
			}
			br.close();

			T0.print();
			T1.print();
			T2.print();
			T3.print();

			System.out.println("T0 7? " + T0.exist(7));
			System.out.println("T1 7? " + T1.exist(7));
			System.out.println("T2 7? " + T2.exist(7));
			System.out.println("T3 7? " + T3.exist(7));

			T0.emOrdem();
			System.out.println("---------");
			T0.emOrdemReversa();
			System.out.println("---------");
			T0.printDraw();
			BinaryTree.espelha(T0);
			System.out.println("ESPELHADO");
			T0.printDraw();
			System.out.println(T0.hasRep());

		} catch (Exception e) {
			e.printStackTrace();
		}
  }

}
