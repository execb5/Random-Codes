/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package negocio;

/**
 *
 * @author Julio
 */
public class ValidadorPessoa {
    public static boolean validaNome(String nome) {
        return nome.contains(" ");
    }
}
