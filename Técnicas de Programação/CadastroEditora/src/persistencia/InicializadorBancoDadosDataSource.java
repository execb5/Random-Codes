/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package persistencia;

import java.sql.Connection;
import java.sql.Statement;
import javax.sql.DataSource;
import org.apache.derby.jdbc.EmbeddedDataSource;

/**
 *
 * @author Júlio
 */
public class InicializadorBancoDadosDataSource {

    public static String DB_NAME = "cadastro";
    public static String USER_NAME = "usuario";
    public static String PASSWORD = "senha";
    private static DataSource dataSource;

    private static DataSource criarDataSource() throws Exception {
        if (dataSource == null) {
            EmbeddedDataSource ds = new EmbeddedDataSource();
            ds.setDatabaseName(DB_NAME);
            ds.setCreateDatabase("create");
            ds.setUser(USER_NAME);
            ds.setPassword(PASSWORD);
            dataSource = ds;
        }
        return dataSource;
    }

    public static void criarBd() throws Exception {
        try (Connection con = criarDataSource().getConnection();
                Statement sta = con.createStatement()) {
            String sqlAutor = "CREATE TABLE AUTORES("
                    + "CODIGO int PRIMARY KEY NOT NULL,"
                    + "PRIMEIRONOME varchar(100) NOT NULL,"
                    + "ULTIMONOME varchar(100) NOT NULL)";
            sta.executeUpdate(sqlAutor);
            String sqlEditora = "CREATE TABLE EDITORAS("
                    + "CODIGO int PRIMARY KEY NOT NULL,"
                    + "NOME varchar(100) NOT NULL)";
            sta.executeUpdate(sqlEditora);
            String sqlLivro = "CREATE TABLE LIVROS("
                    + "CODIGO int PRIMARY KEY NOT NULL,"
                    + "TITULO varchar(100) NOT NULL,"
                    + "ANO int NOT NULL,"
                    + "CODEDITORA int NOT NULL,"
                    + "CONSTRAINT FK_EDITORAS FOREIGN KEY (CODEDITORA) REFERENCES EDITORAS(CODIGO))";
            sta.executeUpdate(sqlLivro);
            String sqlLivroAutor = "CREATE TABLE LIVROSAUTORES("
                    + "CODLIVRO int NOT NULL,"
                    + "CODAUTOR int NOT NULL,"
                    + "CONSTRAINT PK_LIVROSAUTORES PRIMARY KEY (CODLIVRO,CODAUTOR),"
                    + "CONSTRAINT FK_LIVROS FOREIGN KEY (CODLIVRO) REFERENCES LIVROS(CODIGO),"
                    + "CONSTRAINT FK_AUTORES FOREIGN KEY (CODAUTOR) REFERENCES AUTORES(CODIGO))";
            sta.executeUpdate(sqlLivroAutor);
        }
    }

    public static Connection conectarBd() throws Exception {
        return criarDataSource().getConnection();
    }
}
