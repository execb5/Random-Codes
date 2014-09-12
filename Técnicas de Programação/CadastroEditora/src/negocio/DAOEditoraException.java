package negocio;

public class DAOEditoraException extends Exception {
	public DAOEditoraException(){
		super();
	}
	public DAOEditoraException(String mensagem) {
		super(mensagem);
	}
	public DAOEditoraException(String mensagem, Throwable causa) {
		super(mensagem, causa);
	}
}
