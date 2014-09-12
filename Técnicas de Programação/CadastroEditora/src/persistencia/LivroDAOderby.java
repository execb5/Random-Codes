package persistencia;

import negocio.EditoraDAO;
import negocio.LivroDAO;
import negocio.AutorDAO;
import negocio.DAOLivroException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import negocio.Autor;
import negocio.Editora;
import negocio.Livro;

/**
 *
 * @author bernardo
 */
public class LivroDAOderby implements LivroDAO {

    private EditoraDAO edDAO;
    private AutorDAO autDAO;

    // Esta solução só é possível porque um DAO não mantém estado (variáveis de instância)
    // Ao invés desta solução, poderíamos usar o padrão Singleton (será visto junto com a camada de negócios)
    public LivroDAOderby() {
        edDAO = new EditoraDAOderby();
        autDAO = new AutorDAOderby();
    }

    @Override
    public List<Livro> buscarTodos() throws DAOLivroException {
        List<Livro> livros = new ArrayList<>();
        List<Autor> autores;
        String sqlLivros = "select * from livros";
        String sqlLivrosAutores = "select * from livrosautores where codlivro = ?";
        try (Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try (Statement comandoLivros = conexao.createStatement()) {
                try (ResultSet resultadoLivros = comandoLivros.executeQuery(sqlLivros)) {
                    // Para cada linha da tabela livros
                    while (resultadoLivros.next()) {
                        // Recupera todos os autores
                        try (PreparedStatement comandoLivrosAutores = conexao.prepareStatement(sqlLivrosAutores)) {
                            comandoLivrosAutores.setInt(1, resultadoLivros.getInt("codigo"));
                            try (ResultSet resultadoLivrosAutores = comandoLivrosAutores.executeQuery()) {
                                autores = new ArrayList<>();
                                while (resultadoLivrosAutores.next()) {
                                    int codAutor = resultadoLivrosAutores.getInt("codautor");
                                    autores.add(autDAO.buscarPorCodigo(codAutor));
                                }
                            }
                        }
                        // Instancia o livro
                        Livro livro = new Livro(
                                resultadoLivros.getInt("codigo"),
                                resultadoLivros.getString("titulo"),
                                resultadoLivros.getInt("ano"),
                                edDAO.buscarPorCodigo(resultadoLivros.getInt("codeditora")),
                                autores.get(0)
                        );
                        // Acrescenta os demais autores se houver
                        for (int i = 1; i < autores.size(); i++) {
                            livro.addAutor(autores.get(i));
                        }
                        livros.add(livro);
                    }
                    return livros;
                }
            }
        } catch (Exception e) {
            throw new DAOLivroException("Falha na busca: " + e.getMessage(), e);
        }
    }

    @Override
    public Livro buscarPorCodigo(int codigo) throws DAOLivroException {
        Livro livro = null;
        List<Autor> autores;
        String sqlLivros = "select * from livros where codigo=?";
        String sqlLivrosAutores = "select * from livrosautores where codlivro=?";
        try(Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            // Recupera todos os autores
            try(PreparedStatement comandoLivrosAutores = conexao.prepareStatement(sqlLivrosAutores)){
                comandoLivrosAutores.setInt(1, codigo);
                try(ResultSet resultadoLivrosAutores = comandoLivrosAutores.executeQuery()){
                    autores = new ArrayList<>();
                    while (resultadoLivrosAutores.next()) {
                        int codAutor = resultadoLivrosAutores.getInt("codautor");
                        autores.add(autDAO.buscarPorCodigo(codAutor));
                    }
                }
            }
            // Recupera o livro
            try(PreparedStatement comandoLivros = conexao.prepareStatement(sqlLivros)){
                comandoLivros.setInt(1, codigo);
                try(ResultSet resultadoLivros = comandoLivros.executeQuery()){
                    resultadoLivros.next();
                    livro = new Livro(
                        resultadoLivros.getInt("codigo"),
                        resultadoLivros.getString("titulo"),
                        resultadoLivros.getInt("ano"),
                        edDAO.buscarPorCodigo(resultadoLivros.getInt("codeditora")),
                        autores.get(0)
                    );
                    // Acrescenta os demais autores se houver
                    for (int i = 1; i < autores.size(); i++) {
                        livro.addAutor(autores.get(i));
                    }
                }
            }
            return livro;
        } catch (Exception e) {
            throw new DAOLivroException("Falha na busca: " + e.getMessage(), e);
        }
    }

    @Override
    public List<Livro> buscarPorEditora(int codigo) throws DAOLivroException {
        List<Livro> livros = new ArrayList<>();
        List<Autor> autores;
        String sqlLivros = "select * from livros where codeditora = ?";
        String sqlLivrosAutores = "select * from livrosautores where codlivro = ?";
        try(Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try(PreparedStatement comandoLivros = conexao.prepareStatement(sqlLivros); PreparedStatement comandoLivrosAutores = conexao.prepareStatement(sqlLivrosAutores)){
                comandoLivros.setInt(1, codigo);
                try(ResultSet resultadoLivros = comandoLivros.executeQuery()){
                    // Para cada linha da tabela livros
                    while (resultadoLivros.next()) {
                        // Recupera todos os autores
                        comandoLivrosAutores.setInt(1, resultadoLivros.getInt("codigo"));
                        try(ResultSet resultadoLivrosAutores = comandoLivrosAutores.executeQuery()){
                            autores = new ArrayList<>();
                            while (resultadoLivrosAutores.next()) {
                                int codAutor = resultadoLivrosAutores.getInt("codautor");
                                autores.add(autDAO.buscarPorCodigo(codAutor));
                            }
                        }
                        // Instancia o livro
                        Livro livro = new Livro(
                            resultadoLivros.getInt("codigo"),
                            resultadoLivros.getString("titulo"),
                            resultadoLivros.getInt("ano"),
                            edDAO.buscarPorCodigo(resultadoLivros.getInt("codeditora")),
                            autores.get(0)
                        );
                        // Acrescenta os demais autores se houver
                        for (int i = 1; i < autores.size(); i++) {
                            livro.addAutor(autores.get(i));
                        }
                        livros.add(livro);
                    }
                }
            }
            return livros;
        } catch (Exception e) {
            throw new DAOLivroException("Falha na busca: " + e.getMessage(), e);
        }
    }

    @Override
    // ATENCAO: esta operação necessita de controle de transação (atualiza 2 tabelas)
    // A alteração desta rotina fica como exercício !!!
    // Antes de poder inserir o Livro no banco é necessário verificar se
    // tanto a editora como os autores referenciados já estão persistidos.
    // Caso contrário a inserção falha ...
    // Ou então prever como pré-condição em um contrato e eliminar
    // esta necessidade.
    public void inserir(Livro livro) throws DAOLivroException {
        String sqlLiv = "insert into livros(codigo,titulo,ano,codeditora) values(?,?,?,?)";
        String sqlLivAut = "insert into livrosautores(codlivro,codautor) values(?,?)";
        int resultado = 0;
        try {
            // Recupera a editora
            int codEditora = livro.getEditora().getCodigo();
            Editora editora = edDAO.buscarPorCodigo(codEditora);

            // Recupera os autores
            for (Autor a : livro.getAutores()) {
                Autor umAutor = autDAO.buscarPorCodigo(a.getCodigo());
            }

            // Executa a inserção do livro propriamente dita
            try(Connection conexao = InicializadorBancoDadosDataSource.conectarBd()){
                // Insere o Livro na tabela Livros
                try(PreparedStatement comandoLivros = conexao.prepareStatement(sqlLiv)){
                    comandoLivros.setInt(1, livro.getCodigo());
                    comandoLivros.setString(2, livro.getTitulo());
                    comandoLivros.setInt(3, livro.getAno());
                    comandoLivros.setInt(4, editora.getCodigo());
                    resultado = comandoLivros.executeUpdate();
                }
                // Atualiza a tabela LivrosAutores
                try(PreparedStatement comandoLivrosAutores = conexao.prepareStatement(sqlLivAut)){
                    for (Autor a : livro.getAutores()) {
                        comandoLivrosAutores.setInt(1, livro.getCodigo());
                        comandoLivrosAutores.setInt(2, a.getCodigo());
                        resultado += comandoLivrosAutores.executeUpdate();
                    }
                }
            }
        } catch (Exception e) {
            throw new DAOLivroException("Falha na inserção", e);
        }
        // Verifica se foi feita a inserção de 1 livro e de "size" referencias
        // para autores na tabela livrosautores
        if(resultado < livro.getAutores().size()+1) {
            throw new DAOLivroException("Falha na inserção");
        }
    }

    @Override
    public void alterar(Livro livro) throws DAOLivroException {
        String sql = "update livros set titulo=?, ano=?, codeditora=? where codigo = ?";
        String sqlApagar = "delete from livrosautores where codlivro=?";
        String sqlLivAut = "insert into livrosautores(codlivro,codautor) values(?,?)";
        int resultado = 0;
        try(Connection conexao = InicializadorBancoDadosDataSource.conectarBd()) {
            try(PreparedStatement comando = conexao.prepareStatement(sql)){
                comando.setString(1, livro.getTitulo());
                comando.setInt(2, livro.getAno());
                comando.setInt(3, livro.getEditora().getCodigo());
                comando.setInt(4, livro.getCodigo());
                resultado = comando.executeUpdate();
            }
            try(PreparedStatement cmdApagar = conexao.prepareStatement(sqlApagar)){
                cmdApagar.setInt(1, livro.getCodigo());
                cmdApagar.executeUpdate();
            }
            // Atualiza a tabela LivrosAutores
            try(PreparedStatement cmdLivrosAutores = conexao.prepareStatement(sqlLivAut)){
                for (Autor a : livro.getAutores()) {
                    cmdLivrosAutores.setInt(1, livro.getCodigo());
                    cmdLivrosAutores.setInt(2, a.getCodigo());
                    resultado += cmdLivrosAutores.executeUpdate();
                }
            }
        } catch (Exception e) {
            throw new DAOLivroException("Falha na alteração: " + e.getMessage(), e);
        }
        if (resultado == 0) {
            throw new DAOLivroException("Falha na alteração");
        }
    }

}
