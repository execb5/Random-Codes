/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import dados.CadastroMem;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JTextArea;
import negocio.CadastroDAO;
import negocio.CadastroDAOException;
import negocio.Pessoa;
import negocio.ValidadorPessoa;

/**
 *
 * @author Julio
 */
public class JanelaControlador {
    private JTextArea saidaTexto;
    private CadastroDAO dao;

    public JanelaControlador(JTextArea areaTexto) throws Exception {
        saidaTexto = areaTexto;
        dao = new CadastroMem();
        for (String s : this.buscarTodos()){
            saidaTexto.append(s+"\n");
        }
    }

    public boolean adicionarPessoa(String nome, boolean masculino) throws CadastroDAOException {
        if (ValidadorPessoa.validaNome(nome)) {
            Pessoa p = new Pessoa(nome, masculino);
            boolean adicionou = dao.adicionar(p);
            if(adicionou) {
                saidaTexto.append(p.toString() + "\r\n");
            }
            return adicionou;
        } else {
            return false;
        }
    }

    public List<String> buscarHomens() throws CadastroDAOException {
        List<String> retorno = new ArrayList<>();
        for (Pessoa p : dao.getHomens()) {
            retorno.add(p.toString());
        }
        return retorno;
    }

    public List<String> buscarMulheres() throws CadastroDAOException {
        List<String> retorno = new ArrayList<>();
        for (Pessoa p : dao.getMulheres()) {
            retorno.add(p.toString());
        }
        return retorno;
    }

    public List<String> buscarTodos() throws CadastroDAOException {
        List<String> retorno = new ArrayList<>();
        for (Pessoa p : dao.getTodos()) {
            retorno.add(p.toString());
        }
        return retorno;
    }
}
