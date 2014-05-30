import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Hashtable;

public class GDirTest {

	public static void main(String[] args) {
		testFile("/home/matthias/Documents/Random-Codes/Alpro III/t2-2014-02/casosTeste/ex001");
		//testFile("/home/matthias/Documents/Random-Codes/Alpro III/t2-2014-02/casosTeste/ex002");
	}

	private static void testFile(String name) {
		try {
			
			
			BufferedReader br = new BufferedReader(new FileReader(name));
			
			String sCurrentLine = br.readLine();
			int conNum = Integer.parseInt(sCurrentLine);
			
			Hashtable<Integer, Integer> dicionario = new Hashtable<>();
			ArrayList<Integer> origin = new ArrayList<>(conNum);
			ArrayList<Integer> destiny = new ArrayList<>(conNum);
			
			

			while ((sCurrentLine = br.readLine()) != null)
			{
				String[] parts = sCurrentLine.split(" ");
				switch (parts[1])
				{
					case ">":
						origin.add(Integer.parseInt(parts[2]));
						destiny.add(Integer.parseInt(parts[0]));
						break;
					case "<":
						origin.add(Integer.parseInt(parts[0]));
						destiny.add(Integer.parseInt(parts[2]));
						break;
					case "=":
						dicionario.put(Integer.parseInt(parts[2]), Integer.parseInt(parts[0]));
						break;
	
					default:
						break;
				}

			}
			br.close();
			
			//Corrects connections and get graph size
			int graphSize = 0;
			for (int i = 0; i < origin.size(); i++)
			{
				if (dicionario.containsKey(origin.get(i)))
					origin.set(i, dicionario.get(origin.get(i)));
				if (dicionario.containsKey(destiny.get(i)))
					destiny.set(i, dicionario.get(destiny.get(i)));
				if (origin.get(i) > graphSize)
					graphSize = origin.get(i);
				if (destiny.get(i) > graphSize)
					graphSize = destiny.get(i);
			}
			
			GrafoDir G = new GrafoDir(graphSize + 1);
			
			for (int i = 0; i < origin.size(); i++)
			{
				G.InsereAresta(origin.get(i), destiny.get(i));
			}

			// G.Graphviz();
			G.Graphviz();
			long begin = System.currentTimeMillis();
			
			long end = System.currentTimeMillis();

			System.out.println(end - begin + "ms\n\n");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}