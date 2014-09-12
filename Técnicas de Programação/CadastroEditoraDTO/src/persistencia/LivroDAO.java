package persistencia;

import java.util.List;

public interface LivroDAO {
	List<LivroDTO> buscarTodos() throws DAOLivroException;
	LivroDTO buscarPorCodigo(int codigo) throws DAOLivroException;
	List<LivroDTO> buscarPorEditora(int codigo) throws DAOLivroException;
        void inserir(LivroDTO livro) throws DAOLivroException;
	void alterar(LivroDTO livro) throws DAOLivroException;
}
