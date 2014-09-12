package persistencia;

public class DAOAutorException extends Exception {
	public DAOAutorException(){
		super();
	}
	public DAOAutorException(String mensagem) {
		super(mensagem);
	}
	public DAOAutorException(String mensagem, Throwable causa) {
		super(mensagem, causa);
	}
}
