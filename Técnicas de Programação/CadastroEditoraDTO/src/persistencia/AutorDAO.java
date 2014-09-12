package persistencia;

import java.util.List;

public interface AutorDAO {
	List<AutorDTO> buscarTodos() throws DAOAutorException;
        AutorDTO buscarPorCodigo(int codigo) throws DAOAutorException;
	List<AutorDTO> buscarPorUltimoNome(String nome) throws DAOAutorException;
	void inserir(AutorDTO autor) throws DAOAutorException;
	void alterar(AutorDTO autor) throws DAOAutorException;
}