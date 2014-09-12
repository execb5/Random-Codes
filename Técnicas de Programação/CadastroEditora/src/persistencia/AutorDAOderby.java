/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package persistencia;

import negocio.DAOAutorException;
import negocio.AutorDAO;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import negocio.Autor;

/**
 *
 * @author julio
 */
public class AutorDAOderby implements AutorDAO {

    @Override
    public List<Autor> buscarTodos() throws DAOAutorException {
        List<Autor> autores = new ArrayList<>();
        String sql = "select * from autores";
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (Statement comando = conexao.createStatement()) {
                try (ResultSet resultado = comando.executeQuery(sql)) {
                    while (resultado.next()) {
                        Autor autor = new Autor(
                                resultado.getInt("codigo"),
                                resultado.getString("primeironome"),
                                resultado.getString("ultimonome"));
                        autores.add(autor);
                    }
                    return autores;
                }
            }
        } catch (Exception e) {
            throw new DAOAutorException("Falha na busca", e);
        }
    }

    @Override
    public Autor buscarPorCodigo(int codigo) throws DAOAutorException {
        String sql = "select * from autores where codigo = ?";
        Autor autor = null;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setInt(1, codigo);
                try (ResultSet resultado = comando.executeQuery()) {
                    if (resultado.next()) {
                        autor = new Autor(
                                resultado.getInt("codigo"),
                                resultado.getString("primeironome"),
                                resultado.getString("ultimonome")
                        );
                    }
                    return autor;
                }
            }
        } catch (Exception e) {
            throw new DAOAutorException("Falha na busca", e);
        }
    }

    @Override
    public List<Autor> buscarPorUltimoNome(String nome) throws DAOAutorException {
        String sql = "select * from autores where ultimonome = ?";
        List<Autor> autores = new ArrayList<>();
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setString(1, nome);
                try (ResultSet resultado = comando.executeQuery()) {
                    while (resultado.next()) {
                        Autor autor = new Autor(
                                resultado.getInt("codigo"),
                                resultado.getString("primeironome"),
                                resultado.getString("ultimonome"));
                        autores.add(autor);
                    }
                    return autores;
                }
            }
        } catch (Exception e) {
            throw new DAOAutorException("Falha na busca", e);
        }
    }

    @Override
    public void inserir(Autor autor) throws DAOAutorException {
        String sql = "insert into autores(codigo,primeironome,ultimonome) values(?,?,?)";
        int resultado = 0;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setInt(1, autor.getCodigo());
                comando.setString(2, autor.getPrimeiroNome());
                comando.setString(3, autor.getUltimoNome());
                resultado = comando.executeUpdate();
            }
        } catch (Exception e) {
            throw new DAOAutorException("Falha na inserção", e);
        }
        if (resultado == 0) {
            throw new DAOAutorException("Falha na inserção");
        }
    }

    @Override
    public void alterar(Autor autor) throws DAOAutorException {
        String sql = "update autores set primeironome=?, ultimonome=? where codigo = ?";
        int resultado = 0;
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (PreparedStatement comando = conexao.prepareStatement(sql)) {
                comando.setString(1, autor.getPrimeiroNome());
                comando.setString(2, autor.getUltimoNome());
                comando.setInt(3, autor.getCodigo());
                resultado = comando.executeUpdate();
            }
        } catch (Exception e) {
            throw new DAOAutorException("Falha na alteração", e);
        }
        if (resultado == 0) {
            throw new DAOAutorException("Falha na alteração");
        }
    }
}
