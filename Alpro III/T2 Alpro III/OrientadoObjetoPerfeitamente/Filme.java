import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Filme implements GraphContent<Filme> {

	public static final SimpleDateFormat SDF = new SimpleDateFormat("HH:mm");

	private final Date inicio, fim;
	private final String name;

	public Filme(String name, Date inicio, Date fim) {
		if (name == null)
			throw new IllegalArgumentException();
		if (!fim.after(inicio))
			throw new IllegalArgumentException();

		this.name = name;
		this.inicio = inicio;
		this.fim = fim;
	}
	
	public Filme(String name, String inicio, String fim) throws ParseException {
		this(name, SDF.parse(inicio), SDF.parse(fim));
	}
	
	public Date getFim() {
		return fim;
	}

	public Date getInicio() {
		return inicio;
	}

	public String getName() {
		return name;
	}

	@Override
	public boolean isNext(Filme other) {
		return !inicio.before(other.fim) && !isPrevious(other);
	}

	@Override
	public boolean isPrevious(Filme other) {
		return !fim.after(other.inicio) && !isNext(other);
	}

	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append(name).append(" (").append(SDF.format(inicio)).append(" - ")
				.append(SDF.format(fim)).append(")");
		return sb.toString();
	}

}
