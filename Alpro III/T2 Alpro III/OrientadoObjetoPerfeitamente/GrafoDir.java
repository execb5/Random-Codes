import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/*
 * Grafo Dirigido utilizando Matriz de Adjacências.
 * O grafo é criado com n nodos identificados de 0 a n-1.
 */

public class GrafoDir<T extends GraphContent<T>> {
	
	class Node {

		private final T content;
		private final int index;
		private List<Node> maxPath;

		public Node(int index, T content) {
			this.index = index;
			this.content = content;
			this.maxPath = null;
		}

		public T getContent() {
			return content;
		}

		public int getIndex() {
			return index;
		}
		
		private List<Node> getMaxPath() {
			if (maxPath == null) {
				List<Node> maxChild = new ArrayList<>();
				for (Node node : nodes) {
					if (matAdj[index][node.index]) {
						List<Node> aux = node.getMaxPath();
						if (maxChild.size() < aux.size())
							maxChild = aux;
					}
				}
				this.maxPath = maxChild; 
				this.maxPath.add(0, this);
			}
			
			return new ArrayList<>(maxPath);
		}

	}

	private boolean[][] matAdj;
	private int max;
	private List<Node> nodes;

	public GrafoDir(int n) {
		max = n;
		nodes = new ArrayList<>(max);
		matAdj = new boolean[max][max];
	}

	public List<T> getMaxPath() {
		List<Node> max = new ArrayList<>();
		for (Node node : nodes) {
			if (!isRoot(node))
				continue;

			List<Node> tmp = node.getMaxPath();
			if (tmp.size() > max.size())
				max = tmp;
		}
		
		List<T> result = new ArrayList<>(max.size());
		for (Node node : max) {
			result.add(node.getContent());
		}
 		
		return result;
	}

	public int getNodeSize() {
		return nodes.size();
	}

	public void insereAresta(int orig, int dest) {
		if (orig >= 0 && orig < max)
			if (dest >= 0 && dest < max) {
				matAdj[orig][dest] = true;
				return;
			}
		throw new IllegalArgumentException(
				"Insere aresta: Nodo(s) Invalidos(s)");
	}

	public void inserirNodo(T content) {
		Node n = new Node(nodes.size(), content);

		Iterator<Node> it = nodes.iterator();
		int j = nodes.size();
		for (int i = 0; i < nodes.size(); i++) {
			Node aux = it.next();
			if (n.getContent().isNext(aux.getContent()))
				insereAresta(i, j);
			if (n.getContent().isPrevious(aux.getContent()))
				insereAresta(j, i);
		}
		
		nodes.add(n);
	}
	
	private boolean isRoot(Node n) {
		for (int i = 0; i < max; i++) {
			if (matAdj[i][n.getIndex()])
				return false;
		}
		return true;
	}

}
