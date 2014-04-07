import java.util.ArrayList;
import java.util.Date;
import java.util.List;

class Node {

	private int index;
	private Date inicio, fim;
	private String name;
	private List<Node> filmes;

	public Node(int index, String name, Date inicio, Date fim) {
		setIndex(index);
		setName(name);
		setInicio(inicio);
		setFim(fim);
		filmes = null;
	}

	public List<Node> getFilmes() {
		if (filmes == null)
			return null;
		return new ArrayList<>(filmes);
	}

	public void setFilmes(List<Node> maior) {
		this.filmes = maior;
	}

	public Date getFim() {
		return fim;
	}

	public int getIndex() {
		return index;
	}

	public Date getInicio() {
		return inicio;
	}

	public String getName() {
		return name;
	}

	public void setFim(Date fim) {
		this.fim = fim;
	}

	public void setIndex(int index) {
		this.index = index;
	}

	public void setInicio(Date inicio) {
		this.inicio = inicio;
	}

	public void setName(String name) {
		if (name == null)
			throw new IllegalArgumentException();
		else
			this.name = name;
	}

}