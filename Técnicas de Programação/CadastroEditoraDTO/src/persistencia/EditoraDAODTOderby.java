package persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author aa
 */
public class EditoraDAODTOderby implements EditoraDAO{

    @Override
    public List<EditoraDTO> buscarTodos() throws DAOEditoraException {
        List<EditoraDTO> editoras = new ArrayList<>();
        String sql = "select * from editoras";
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (Statement comando = conexao.createStatement()) {
                try (ResultSet resultado = comando.executeQuery(sql)) {
                    while (resultado.next()) {
                        EditoraDTO editora = new EditoraDTO();
                        editora.setCodigo(resultado.getInt("codigo"));
                        editora.setNome(resultado.getString("nome"));
                        editoras.add(editora);
                    }
                    return editoras;
                }
            }
        } catch (Exception e) {
            throw new DAOEditoraException("Falha na busca", e);
        }
    }

    @Override
    public EditoraDTO buscarPorCodigo(int codigo) throws DAOEditoraException {
        String sql = "select * from editoras where codigo = ?";
        EditoraDTO ed = null;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setInt(1, codigo);
                try (ResultSet resultado = comando.executeQuery()) {
                    if (resultado.next()) {
                        ed = new EditoraDTO();
                        ed.setCodigo(resultado.getInt("codigo"));
                        ed.setNome(resultado.getString("nome"));
                    }
                    return ed;
                }
            }
        } catch (Exception e) {
            throw new DAOEditoraException("Falha na busca", e);
        }
    }

    @Override
    public void inserir(EditoraDTO ed) throws DAOEditoraException {
        String sql = "insert into editoras(codigo,nome) values(?,?)";
        int resultado = 0;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setInt(1, ed.getCodigo());
                comando.setString(2, ed.getNome());
                resultado = comando.executeUpdate();
            }
        } catch (Exception e) {
            throw new DAOEditoraException("Falha na inserção", e);
        }
        if (resultado == 0) {
            throw new DAOEditoraException("Falha na inserção");
        }
    }

    @Override
    public void alterar(EditoraDTO ed) throws DAOEditoraException {
        String sql = "update editoras set nome=? where codigo=?";
        int resultado = 0;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setString(1, ed.getNome());
                comando.setInt(2, ed.getCodigo());
                resultado = comando.executeUpdate();
            }
        } catch (Exception e) {
            throw new DAOEditoraException("Falha na alteração", e);
        }
        if (resultado == 0) {
            throw new DAOEditoraException("Falha na alteração");
        }
    }
}
