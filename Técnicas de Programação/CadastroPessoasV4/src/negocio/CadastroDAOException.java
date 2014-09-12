/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package negocio;

/**
 *
 * @author aa
 */
public class CadastroDAOException extends Exception {
	public CadastroDAOException(){
		super();
	}
	public CadastroDAOException(String mensagem) {
		super(mensagem);
	}
	public CadastroDAOException(String mensagem, Throwable causa) {
		super(mensagem, causa);
	}
}

