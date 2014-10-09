// BinaryTree.java
public class BinaryTree {

  // Referência para a raiz da árvore. É null para o caso de uma
  // árvore vazia.

  private Node root;

  /*
   Node
   A árvore binária usa esta classe interna. Cada nodo contém
   uma informação e referências para as sub-árvores esquerda e
   direita.
  */
  private static class Node {
    Node left;
    Node right;
    int data;

    Node( int newData ) {
      left = right = null;
      data = newData;
    }
  }

  /* Cria uma árvore vazia, ou seja, uma referência nula. */
  public BinaryTree() {
    root = null;
  }

  /* Inserção na árvore. Usa o método auxiliar */
  public void insert( int data ) {
    root = insert1( root, data );
  }

    /* Inserção não-recursiva.  */
    private Node insert1( Node root, int data ) {
      Node novo = new Node( data );

      if ( root == null ) return novo;

      Node node = root;

      while ( true ) {
        if ( data < node.data )
            if ( node.left == null ) { node.left = novo; break; }
            else node = node.left;
        else
            if ( node.right == null ) { node.right = novo; break; }
            else node = node.right;
      }
      return root;
    }

  /*
   Inserção recursiva.
   Dado um nodo, percorre a sub-árvore até achar o local de inserção
   do valor pedido. Retorna uma referência para o novo nodo. Elementos
   repetidos são permitidos.
  */
  private Node insert2( Node node, int data ) {
    if ( node == null )
      return new Node( data );
    if ( data == node.data ) return node;
    if ( data < node.data ) node.left = insert2( node.left, data );
                      else node.right = insert2( node.right, data );
    return node;
  }

  /* Inserção não-recursiva para gerar uma árvore que não seja de
   * pesquisa  */
  private Node insert3( Node root, int data ) {
    Node novo = new Node( data );

    if ( root == null ) return novo;

    Node node = root;

    int ax = 2;

    while ( true ) {
      if ( data == node.data ) return node;
      if ( data % ax < node.data % ax )
        if ( node.left == null ) {
          node.left = novo; break;
        } else node = node.left;
      else
        if ( node.right == null ) {
          node.right = novo; break;
        } else node = node.right;
      ax = 2 + ( ax * 2 + 3 ) % 11;
    }
    return root;
  }


  /* Destroi uma árvore chamando um método interno */
  public void destroy( ) {
    root = destroy( root );
  }

  /* Método interno para destruição */
  private Node destroy( Node node ) {
    if ( node == null ) return null;
    node.left = destroy( node.left );
    node.right = destroy( node.right );
    System.out.println("Deleting " + node.data + "...");
    return null;
  }

	public void print()
	{
		printAux(root);
	}

  private void printAux(Node node)
  {
  	if(node == null)
			return;
		printAux(node.left);
		printAux(node.right);
		System.out.println(node.data);
  }

	public void emOrdem()
	{
		emOrdemAux(root);
	}

  private void emOrdemAux(Node node)
  {
  	if(node == null)
			return;
		emOrdemAux(node.left);
		System.out.println(node.data);
		emOrdemAux(node.right);
  }

	public void emOrdemReversa()
	{
		emOrdemReversaAux(root);
	}

  private void emOrdemReversaAux(Node node)
  {
  	if(node == null)
			return;
		emOrdemReversaAux(node.right);
		System.out.println(node.data);
		emOrdemReversaAux(node.left);
  }

	public boolean exist(int n)
	{
		return existAux(root, n);
	}

	private boolean existAux(Node node, int n)
	{
		while (node != null)
		{
			if (node.data == n)
				return true;
			node = (n < node.data ? node.left : node.right);
		}
		return false;
	}

	public boolean existRec(int n)
	{
		return existAuxRec(root, n);
	}

	private boolean existAuxRec(Node node, int n)
	{
		if (node == null) return false;
		if(node.data == n)
			return true;
		return existAuxRec(node.left, n) || existAuxRec(node.right, n);
	}


	public Node getRoot()
	{
		return root;
	}

	public static void espelha(BinaryTree T)
	{
		espelhaAux(T.getRoot());
	}

	private static void espelhaAux(Node node)
	{
		if (node == null)
			return;
		espelhaAux(node.left);
		espelhaAux(node.right);
		Node aux = node.left;
		node.left = node.right;
		node.right = aux;
	}

	public void printDraw()
	{
		printDrawAux(root, "");
	}

	private void printDrawAux(Node node, String s)
	{
		if(node == null)
			return;
		printDrawAux(node.left, s + "      ");
		System.out.println(s + node.data);
		printDrawAux(node.right, s + "      ");
	}

	public boolean hasRep()
	{
		return hasRepAux(root);
	}

	private boolean hasRepAux(Node node)
	{
                if (node == null)
                        return false;
                boolean a = anotherHasRepAux(node.left, node.data) || anotherHasRepAux(node.right, node.data);
                if (a)
                        return a;
                return hasRepAux(node.left) || hasRepAux(node.right);
	}

        private boolean anotherHasRepAux(Node node, int value)
        {
                if (node == null)
                        return false;
                if (node.data == value)
                        return true;
                return anotherHasRepAux(node.left, value) || anotherHasRepAux(node.right, value);
        }
}
