/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package exemplo;

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

        //Manipulacao de editoras
        EditoraDAO dao = new EditoraDAODTOderby();
        AdaptadorNegocioPersistenciaEditora repositorio = new AdaptadorNegocioPersistenciaEditora(dao);
        System.out.println("Inserir editoras...");
        repositorio.inserir(new Editora(1, "Editora Campus"));
        repositorio.inserir(new Editora(2, "Editora Pearson"));
        repositorio.inserir(new Editora(3, "editora McGraw-Hill"));

        System.out.println("\nListando editoras...");
        List<Editora> editoras = repositorio.buscarTodos();
        for (Editora ed : editoras) {
            System.out.println(ed);
        }

    }
}
