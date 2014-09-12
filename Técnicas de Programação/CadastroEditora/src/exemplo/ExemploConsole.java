/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package exemplo;

import negocio.LivroDAO;
import negocio.EditoraDAO;
import negocio.DAOEditoraException;
import negocio.AutorDAO;
import java.util.List;
import negocio.*;
import persistencia.*;

/**
 *
 * @author julio
 */
public class ExemploConsole {

    public static void main(String[] args) throws Exception {
        //Utilize o seguinte código somente a primeira vez que executar
        System.out.println("Criando BD...");
        InicializadorBancoDadosDataSource.criarBd();

        //Manipulando autores
        AutorDAO daoAutor = new AutorDAOderby();
        System.out.println("Inserir autores...");
        daoAutor.inserir(new Autor(1, "John", "Doe"));
        daoAutor.inserir(new Autor(2, "Mary", "Doe"));
        daoAutor.inserir(new Autor(3, "Mrs", "Smith"));

        System.out.println("Listando autores...");
        List<Autor> autores = daoAutor.buscarTodos();
        for (Autor autor : autores) {
            System.out.println(autor);
        }
        System.out.println("Listando autores por nome...");
        /*List<Autor>*/ //autores = daoAutor.buscarPorUltimoNome("Doe");
        for (Autor autor : daoAutor.buscarTodos()) {
            System.out.println(autor);
        }

        System.out.println("Buscando autor...");
        System.out.println(daoAutor.buscarPorCodigo(1));
        System.out.println("Alterando autor...");
        Autor a = daoAutor.buscarPorCodigo(1);
        a.setPrimeiroNome("Testava");
        daoAutor.alterar(a);
        System.out.println(daoAutor.buscarPorCodigo(1));

        //Manipulacao de editoras
        EditoraDAO daoEditora = new EditoraDAOderby();
        System.out.println("Inserir editoras...");
        daoEditora.inserir(new Editora(1, "Editora Campus"));
        daoEditora.inserir(new Editora(2, "Editora Pearson"));
        daoEditora.inserir(new Editora(3, "editora McGraw-Hill"));

        System.out.println("\nListando editoras...");
        List<Editora> editoras = daoEditora.buscarTodos();
        for (Editora ed : editoras) {
            System.out.println(ed);
        }

        System.out.println("\nBuscando editora e corrige o nome...");
        Editora ed = daoEditora.buscarPorCodigo(1);

        System.out.println(ed);

        System.out.println("Alterando  nome...");
        ed.setNome("Editora Campos - Elsevier");
        daoEditora.alterar(ed);
        System.out.println("\nno banco, alterado: \n" + daoEditora.buscarPorCodigo(1));

        // inserção de chave duplicada
        try {
            daoEditora.inserir(new Editora(3, "Erro"));
        } catch (DAOEditoraException ex) {
            System.out.println("\nerro: \n" + ex.getMessage());
        }

        // Manipulacao de livros
        LivroDAO daoLivro = new LivroDAOderby();
        System.out.println("Inserindo livros");
        Editora ed1 = daoEditora.buscarPorCodigo(1);
        Autor aut1 = daoAutor.buscarPorCodigo(1);

        daoLivro.inserir(new Livro(1, "Java for dummys", 2013, ed1, aut1));
        daoLivro.inserir(new Livro(2, "Camada de persistencia", 2011, ed1,
                daoAutor.buscarPorCodigo(2)));
        daoLivro.inserir(new Livro(3, "Padrao DAO", 2012,
                daoEditora.buscarPorCodigo(3),
                daoAutor.buscarPorCodigo(2)));
        Livro livro4 = new Livro(4, "Varios autores", 2012,
                daoEditora.buscarPorCodigo(3),
                daoAutor.buscarPorCodigo(1));
        livro4.addAutor(daoAutor.buscarPorCodigo(2));
        livro4.addAutor(daoAutor.buscarPorCodigo(3));
        daoLivro.inserir(livro4);

        System.out.println("\nListando livros...");
        List<Livro> livros = daoLivro.buscarTodos();
        for (Livro l : livros) {
            System.out.println(l);
        }

        System.out.println("\nBuscando livro pelo código...");
        System.out.println("(cod=4) " + daoLivro.buscarPorCodigo(4));
        //System.out.println("(cod=7) " + daoLivro.buscarPorCodigo(7));

        System.out.println("\nBuscando livro pela editora...");
        System.out.println("(ed=1) " + daoLivro.buscarPorEditora(1));
        //System.out.println("(ed=7) " + daoLivro.buscarPorEditora(7));

        Livro livro2 = daoLivro.buscarPorCodigo(2);
        Autor autor2 = daoAutor.buscarPorCodigo(3);
        System.out.println("\nAltera dados do livro...");
        livro2.setTitulo("Duro de Matar 52");
        livro2.setAno(2032);
        livro2.setEditora(daoEditora.buscarPorCodigo(1));
        livro2.addAutor(aut1);

        daoLivro.alterar(livro2);

        System.out.println(daoLivro.buscarPorCodigo(2));
    }
}
