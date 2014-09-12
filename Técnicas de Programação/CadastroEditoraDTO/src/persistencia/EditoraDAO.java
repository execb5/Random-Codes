package persistencia;

import java.util.List;

public interface EditoraDAO {
	List<EditoraDTO> buscarTodos() throws DAOEditoraException;
	EditoraDTO buscarPorCodigo(int codigo) throws DAOEditoraException;
	void inserir(EditoraDTO editora) throws DAOEditoraException;
	void alterar(EditoraDTO editora) throws DAOEditoraException;
}
