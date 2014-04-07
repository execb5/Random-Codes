import java.io.BufferedReader;
import java.io.FileReader;
import java.text.SimpleDateFormat;
import java.util.List;

public class GDirTest {

	public static void main(String[] args) {
		testFile("ex20.txt");
		testFile("ex40.txt");
		testFile("ex60.txt");
		testFile("ex80.txt");
		testFile("ex100.txt");
		testFile("ex120.txt");
		testFile("ex140.txt");
		testFile("ex160.txt");
		testFile("ex180.txt");
		testFile("ex200.txt");
	}

	private static void testFile(String name) {
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm");
		try {
			BufferedReader br = new BufferedReader(new FileReader(name));
			GrafoDir G = new GrafoDir(Integer.parseInt(br.readLine()));

			String sCurrentLine = null;
			int index = 0;
			while ((sCurrentLine = br.readLine()) != null) {
				String[] parts = sCurrentLine.split(" ");
				G.inserirNodo(new Node(index++, parts[2], sdf.parse(parts[0]),
						sdf.parse(parts[1])));
			}
			br.close();
			System.out.println("Graph read: " + name);

			// G.Graphviz();
			long begin = System.currentTimeMillis();
			List<Node> n = G.numeroMaxFilmes();
			long end = System.currentTimeMillis();

			System.out.println("Numero de Filmes: " + n.size());
			for (Node aux : n) {
				System.out.println(aux.getName());
			}
			System.out.println(end - begin + "ms\n\n");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}