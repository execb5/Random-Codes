import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/*
 * Grafo Dirigido utilizando Matriz de Adjacências.
 * O grafo é criado com n nodos identificados de 0 a n-1.
 */

public class GrafoDir {

	private int max;
	private List<Node> nodes;
	private boolean[][] matAdj;

	/* CRIACAO com n nodos */
	public GrafoDir(int n) {
		max = n;
		nodes = new ArrayList<>(max);
		matAdj = new boolean[max][max];
	}

	public void inserirNodo(Node n) {
		if (!n.getFim().after(n.getInicio()))
			throw new IllegalArgumentException();

		Iterator<Node> it = nodes.iterator();
		int j = nodes.size();
		for (int i = 0; i < nodes.size(); i++) {
			Node aux = it.next();
			if (!aux.getFim().after(n.getInicio()))
				InsereAresta(i, j);
			if (!aux.getInicio().before(n.getFim()))
				InsereAresta(j, i);
		}
		nodes.add(n);
	}

	/* Insere Aresta */
	public void InsereAresta(int orig, int dest) {
		if (orig >= 0 && orig < max)
			if (dest >= 0 && dest < max) {
				matAdj[orig][dest] = true;
				return;
			}
		throw new IllegalArgumentException(
				"Insere aresta: Nodo(s) Invalidos(s)");
	}

	public List<Node> numeroMaxFilmes() {
		List<Node> n = new ArrayList<>();
		for (Node node : nodes) {
			if (!IsRoot(node))
				continue;

			List<Node> tmp = numeroMaxFilmes(node);
			if (tmp.size() > n.size())
				n = tmp;
		}
		return n;
	}

	private boolean IsRoot(Node n) {
		for (int i = 0; i < max; i++) {
			if (matAdj[i][n.getIndex()])
				return false;
		}
		return true;
	}

	private List<Node> numeroMaxFilmes(Node n) {
		List<Node> maior = new ArrayList<>();
		if (n.getFilmes() == null) {
			for (Node node : nodes) {
				if (matAdj[n.getIndex()][node.getIndex()]) {
					List<Node> aux = numeroMaxFilmes(node);
					if (maior.size() < aux.size())
						maior = aux;
				}
			}
			n.setFilmes(new ArrayList<Node>(maior));
		} else {
			maior = n.getFilmes();
		}
		maior.add(0, n);
		return maior;
	}

}