package negocio;

import java.util.List;

public interface EditoraDAO {
	List<Editora> buscarTodos() throws DAOEditoraException;
	Editora buscarPorCodigo(int codigo) throws DAOEditoraException;
	void inserir(Editora editora) throws DAOEditoraException;
	void alterar(Editora editora) throws DAOEditoraException;
}
