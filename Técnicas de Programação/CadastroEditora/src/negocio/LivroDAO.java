package negocio;

import java.util.List;

public interface LivroDAO {
	List<Livro> buscarTodos() throws DAOLivroException;
	Livro buscarPorCodigo(int codigo) throws DAOLivroException;
	List<Livro> buscarPorEditora(int codigo) throws DAOLivroException;
        void inserir(Livro livro) throws DAOLivroException;
	void alterar(Livro livro) throws DAOLivroException;
}
