import java.io.BufferedReader;
import java.io.FileReader;
import java.util.List;

public class GDirTest {

	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader("ex60.txt"));
			GrafoDir<Filme> G = new GrafoDir<Filme>(Integer.parseInt(br
					.readLine()));

			String sCurrentLine = null;
			while ((sCurrentLine = br.readLine()) != null) {
				String[] parts = sCurrentLine.split(" ");
				Filme filme = new Filme(parts[2], parts[0], parts[1]);
				G.inserirNodo(filme);
			}
			br.close();
			System.out.println("Graph read");
			System.out.println("Graph size: " + G.getNodeSize());

			// G.Graphviz();
			long begin = System.currentTimeMillis();
			List<Filme> maxPath = G.getMaxPath();
			long end = System.currentTimeMillis();

			System.out.println("Numero de Filmes: " + maxPath.size());
			for (Filme filme : maxPath) {
				System.out.println(filme);
			}
			System.out.println(end - begin + "ms");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
