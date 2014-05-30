import java.util.*;

/*
 * Grafo Dirigido utilizando Matriz de AdjacÃªncias.
 * O grafo Ã© criado com n nodos identificados de 0 a n-1.
 */

public class GrafoDir {

	private int max;
	private boolean [] mark;
	private boolean [] inuse;
	private boolean [][] matAdj;
	
	public void Mark( int n ) { mark[n] = true; }
	public void UnMark( int n ) { mark[n] = false; }
	public boolean isMarked( int n ) { return mark[n] == true; }

	/* CRIACAO com capacidade para n nodos */
	public GrafoDir( int n ) {

		max = 100;
		if ( n > 0 ) max = n;

		mark = new boolean[max];
		inuse = new boolean[max];
		matAdj = new boolean [max][max];
	}

	/* Retorna numero de nodos maximo do grafo */
	public int NumNodos() {
		return max;
	}

	/* Retorna numero de nodos em uso */
	public int CapNodos() {
		int i, res = 0;
		for ( i = 0; i < max; i++ )
			if ( inuse[i] )
				res++;
			return res ;
	}

	/* Retorna lista de nodos sendo usados no grafo: 0, 1, 2,..., n - 1 */
	public List < Integer > Nodos( ) {

		List < Integer > res = new ArrayList < Integer > ();

		int i;
		for ( i = 0; i < max; i++ )
			if ( inuse[i] )
				res.add( i );
		return res ;
	}

	/* Retorna numero total de arestas */
	public int NumArestas() {
		int i, j, res = 0;
		for ( i = 0; i < max; i++ )
			for ( j = 0; j < max; j++ )
				if ( matAdj[i][j] == true )
					res++;
		return res;
	}

	/* Insere Aresta */
	/* A inserÃ§Ã£o de aresta tambÃ©m cria os nodos se for preciso */
	public void InsereAresta( int orig, int dest ) {
		if ( orig >= 0 && orig < max )
			if ( dest >= 0 && dest < max ) {
				inuse[orig] = true;
				inuse[dest] = true;
				matAdj[orig][dest] = true;
				return;
			}
		throw new IllegalArgumentException( "Insere aresta: Nodo(s) Invalidos(s)" );
	}

	/* Remove Aresta */
	public void RemoveAresta( int orig, int dest ) {
		if ( orig >= 0 && orig < max )
			if ( dest >= 0 && dest < max ) {
				matAdj[orig][dest] = false;
				return;
			}
		throw new IllegalArgumentException( "RemoveAresta: Nodo(s) Invalidos(s)" );
	}

	/* Testa se existe aresta */
	public boolean ExisteAresta( int orig, int dest ) {
		if ( orig >= 0 && orig < max )
			if ( dest >= 0 && dest < max )
				return matAdj[orig][dest];
		throw new IllegalArgumentException( "Existe aresta: Nodo(s) Invalidos(s)" );
	}

	/* Desmarca todos os nodos */
	public void DesmarcaNodos() {
		for ( int n : Nodos() )
			UnMark( n );
	}

	/* Marca um nodo */
	public void Marca( int n ) {
		if ( n >= 0 && n < max ) {
			Mark( n );
			return;
		}
		throw new IllegalArgumentException( "Marca nodo: Nodo Invalido" );
	}

	/* Desenho de grafos, ver http://www.graphviz.org/Gallery.php */
	public void Graphviz() {
		System.out.println( "digraph G {" );
		System.out.println( "   rankdir = LR; " );
		System.out.println( "   node [shape = circle]; " );
		int i, j;
		for ( i = 0; i < max; i++ )
			for ( j = 0; j < max; j++ )
				if ( ExisteAresta(i,j) )
					System.out.println( "   " + i + " -> " + j + ";" );
		System.out.println( "}" );
	}

	/* Retorna lista de vizinhos de um nodo */
	public List < Integer > Vizinhos( int elem ) {

		List < Integer > res = new ArrayList < Integer > ();

		if ( elem < 0 || elem >= max )
			throw new IllegalArgumentException( "Nodo Invalido" );
		else {
			int i;
			for ( i = 0; i < max; i++ )
				if ( ExisteAresta(elem,i) ) res.add( i );
		}
		return res ;
	}

	/* ????????????????????? */
	public void Explore( int u ) {

		DesmarcaNodos();
		Marca( u );

		List < Integer > L = new ArrayList < Integer > ();
		L.add( u );

		while ( ! L.isEmpty() ) {

			u = L.remove( 0 );
			System.out.println( u );

			for ( int v : Vizinhos( u ) )
				if ( ! isMarked( v ) ) {
					Mark( v );
					L.add( v );
				}

		}
	}
}
